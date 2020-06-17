
#include "IBKRClient.h"

#include <chrono>

using namespace std::chrono_literals;

void fromContractInfoToContract(Contract& contractOut, const ContractInfo& contractInfoIn)
{
    contractOut.conId = contractInfoIn.Id;
    contractOut.symbol = contractInfoIn.Symbol;
    contractOut.currency = contractInfoIn.Currency;
    contractOut.exchange = contractInfoIn.Exchange;
}

void fromContractDetailsToContractInfo(ContractInfo& contractInfoOut, const ContractDetails& contractDetailsIn)
{
    contractInfoOut.Id = contractDetailsIn.contract.conId;
    contractInfoOut.Symbol = contractDetailsIn.contract.symbol;
    contractInfoOut.Currency = contractDetailsIn.contract.currency;
    contractInfoOut.Exchange = contractDetailsIn.contract.exchange;
}

IBKRClient::IBKRClient(unsigned long signalWaitTimeout)
    : EWrapper()
    , mOSSignal(signalWaitTimeout)
    , mSignalWaitTimeout(signalWaitTimeout)
    , mClientSocketPtr(std::make_unique<EClientSocket>((EWrapper*)this, &mOSSignal))
    , mExtraAuth(false)
    , mListenForMessages(false)
    , mMessgeListeningThread()
    , mLogFunctionPtr(nullptr)
    , mLogObjectPtr(nullptr)
    , mOrderId(-1)
    , mRequestId(0)
{

}

IBKRClient::~IBKRClient()
{
    mListenForMessages = false;
    mMessgeListeningThread.join();
}

//
// Exported functions implementation
//

void CREATE_ADAPTER_FUNC(IGenericConnectionAdapter** implementation)
{
    IBKRClient* client = new IBKRClient();
    *implementation = client;
}

void DESTROY_ADAPTER_FUNC(IGenericConnectionAdapter** implementation)
{
    if (*implementation)
    {
        delete* implementation;
        *implementation = nullptr;
    }
}

void GET_INFO_FUNC(ConnectionAdapterLibraryInfo* info)
{
    strcpy_s(info->Name,        sizeof(info->Name),         "IBKR");
    strcpy_s(info->Version,     sizeof(info->Version),      "v1.0");
    strcpy_s(info->Description, sizeof(info->Description),  "A connection adapter for the IBKR (Interactive Brokers) API (application programming interface).");
}

//
// IGenericConnectionAdapter implementation
//

void IBKRClient::SetLogFunction(LogFunction* logFunctionPtr, void* logObjectPtr)
{
    mLogFunctionPtr = logFunctionPtr;
    mLogObjectPtr = logObjectPtr;
}

bool IBKRClient::Connect()
{
    bool res = mClientSocketPtr->eConnect("127.0.0.1", 7497, 0, mExtraAuth);
    if (res)
    {
        // Fire up the reader
        mReaderPtr = std::make_unique<EReader>(mClientSocketPtr.get(), &mOSSignal);
        mReaderPtr->start();
    }

    return res;
}

bool IBKRClient::IsConnected()
{
    return mClientSocketPtr->isConnected();
}

void IBKRClient::Disconnect()
{
    mClientSocketPtr->eDisconnect();
}

void IBKRClient::GetSupportedFeatures(SupportedFeatures* supportedFeatures)
{
    supportedFeatures->PlaceLimitOrders = true;
    supportedFeatures->PlaceMarketOrders = false;
}

void IBKRClient::StartListeningForMessages()
{
    if (mListenForMessages) return; //already listening
    if (mMessgeListeningThread.joinable()) mMessgeListeningThread.join();
    mListenForMessages = true;
    // Start the listener thread
    mMessgeListeningThread = std::thread([this]() { MessageListeningLoop(); });
}

void IBKRClient::StopListeningForMessages()
{
    mListenForMessages = false;
    if (mMessgeListeningThread.joinable()) mMessgeListeningThread.join();
}

void IBKRClient::GetStockContracts(const StockContractQuery& query, ContractQueryResult* result)
{
    Contract contract;
    contract.symbol = query.Symbol;
    contract.secType = "STK";
    contract.currency = query.Currency;
    contract.exchange = query.Exchange;
    mClientSocketPtr->reqContractDetails(mRequestId, contract);

    // Wait until the data is received
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    mRequestIdToContractRequestResponse[mRequestId].Reset();
    bool waitResultSuccess = mContractRequestConditionVariable.wait_for(lk, mSignalWaitTimeout * 1ms, [this] {return this->mRequestIdToContractRequestResponse[this->mRequestId].mIsDone; });

   if (waitResultSuccess)
   {
       // Get the contracts information
       result->RequestId = mRequestId;
       result->ContractInfoArray = mRequestIdToContractRequestResponse[mRequestId].mReceivedContractInfos;
       result->Status = ResultStatus::Success;
   }
   else
   {
       result->RequestId = -1;
       result->ContractInfoArray.clear();
       result->Status = ResultStatus::WaitTimeout;
   }

    // Clear the data to preserve memory
    mRequestIdToContractRequestResponse[mRequestId].Reset();

    // Increase the request id for future requests
    ++mRequestId;

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again
    lk.unlock();
    mContractRequestConditionVariable.notify_one();
}

void IBKRClient::PlaceLimitOrder(const LimitOrderInfo& orderInfo, PlaceOrderResult* result)
{
    // Set the order info
    Order order;
    switch (orderInfo.Action)
    {
    case ActionType::Buy:
        order.action = "BUY";
        break;
    case ActionType::Sell:
        order.action = "SELL";
        break;
    }
    order.orderType = "LMT";
    order.totalQuantity = orderInfo.Quantity;
    order.lmtPrice = orderInfo.Price;

    // Set the contract info
    Contract contract;
    fromContractInfoToContract(contract, *orderInfo.ConInfoPtr);

    // Wait until the order id gets updated
    std::unique_lock<std::mutex> lk(mOrderIdMutex);
    bool waitResultSuccess = mOrderIdConditionVariable.wait_for(lk, mSignalWaitTimeout * 1ms, [this] {return mOrderId != -1; });

    if (waitResultSuccess)
    {
        // Get the new order id value and invalidate it
        OrderId orderId = mOrderId;
        mOrderId = -1;

        // Place the order and immediately request a new order id
        mClientSocketPtr->placeOrder(orderId, contract, order);
        mClientSocketPtr->reqIds(-1);
        result->Id = orderId;
        result->Status = ResultStatus::Success;
    }
    else
    {
        result->Id = -1;
        result->Status = ResultStatus::WaitTimeout;
    }

    // Unlock and signal
    lk.unlock();
    mOrderIdConditionVariable.notify_one();
}


//
// EWrapper implementation
//

void IBKRClient::tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib)
{
}

void IBKRClient::tickSize(TickerId tickerId, TickType field, int size)
{
}

void IBKRClient::tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{
}

void IBKRClient::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
}

void IBKRClient::tickString(TickerId tickerId, TickType tickType, const std::string& value)
{
}

void IBKRClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate)
{
}

void IBKRClient::orderStatus(OrderId orderId, const std::string& status, double filled, double remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, std::string("Got order: " + std::to_string(orderId) + " status: " + status).c_str());
}

void IBKRClient::openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, std::string("Got open order: " + std::to_string(orderId)).c_str());
}

void IBKRClient::openOrderEnd()
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, std::string("Got open order feed end").c_str());
}

void IBKRClient::winError(const std::string& str, int lastError)
{
}

void IBKRClient::connectionClosed()
{
}

void IBKRClient::updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName)
{
}

void IBKRClient::updatePortfolio(const Contract& contract, double position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName)
{
}

void IBKRClient::updateAccountTime(const std::string& timeStamp)
{
}

void IBKRClient::accountDownloadEnd(const std::string& accountName)
{
}

void IBKRClient::nextValidId(OrderId orderId)
{
    std::unique_lock<std::mutex> lk(mOrderIdMutex);
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, ("Got new valid Id: " + std::to_string(orderId)).c_str());
    mOrderId = orderId;
    lk.unlock();
    mOrderIdConditionVariable.notify_one();
}

void IBKRClient::contractDetails(int reqId, const ContractDetails& contractDetails)
{
    // Append the contract
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    mRequestIdToContractRequestResponse[reqId].mReceivedContractInfos.push_back(ContractInfo());
    ContractInfo &conInfo = mRequestIdToContractRequestResponse[reqId].mReceivedContractInfos.back();
    fromContractDetailsToContractInfo(conInfo, contractDetails);
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, ("Got " + conInfo.ToShortString() + " from request: " + std::to_string(reqId)).c_str());
}

void IBKRClient::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
}

void IBKRClient::contractDetailsEnd(int reqId)
{
    // Mark the request as done and send the signal
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    int count = (int)mRequestIdToContractRequestResponse[reqId].mReceivedContractInfos.size();
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, ("Got " + std::to_string(count) + " total contracts from request: " + std::to_string(reqId)).c_str());
    mRequestIdToContractRequestResponse[reqId].mIsDone = true;
    // First unlock and then notify is a more efficient way
    lk.unlock();
    mContractRequestConditionVariable.notify_one();
}

void IBKRClient::execDetails(int reqId, const Contract& contract, const Execution& execution)
{
}

void IBKRClient::execDetailsEnd(int reqId)
{
}

void IBKRClient::error(int id, int errorCode, const std::string& errorString)
{
    LogType logType;
    switch (id)
    {
        // Callbacks to IBApi::EWrapper::error with errorId as -1 do not represent true 'errors'
        // but only notifications that a connection has been made successfully to the IB market data farms.
    case -1:
        logType = LogType::Info;
        break;
    default:
        logType = LogType::Error;
        break;
    }

    switch (errorCode)
    {
    case 502: // socket cannot be opened

        break;
    }

    mLogFunctionPtr(mLogObjectPtr, logType, errorString.c_str());
}

void IBKRClient::updateMktDepth(TickerId id, int position, int operation, int side, double price, int size)
{
}

void IBKRClient::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, int size, bool isSmartDepth)
{
}

void IBKRClient::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch)
{
}

void IBKRClient::managedAccounts(const std::string& accountsList)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Info, ("Account List: " + accountsList).c_str());
}

void IBKRClient::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
}

void IBKRClient::historicalData(TickerId reqId, const Bar& bar)
{
}

void IBKRClient::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr)
{
}

void IBKRClient::scannerParameters(const std::string& xml)
{
}

void IBKRClient::scannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr)
{
}

void IBKRClient::scannerDataEnd(int reqId)
{
}

void IBKRClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count)
{
}

void IBKRClient::currentTime(long time)
{
}

void IBKRClient::fundamentalData(TickerId reqId, const std::string& data)
{
}

void IBKRClient::deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract)
{
}

void IBKRClient::tickSnapshotEnd(int reqId)
{
}

void IBKRClient::marketDataType(TickerId reqId, int marketDataType)
{
}

void IBKRClient::commissionReport(const CommissionReport& commissionReport)
{
}

void IBKRClient::position(const std::string& account, const Contract& contract, double position, double avgCost)
{
}

void IBKRClient::positionEnd()
{
}

void IBKRClient::accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency)
{
}

void IBKRClient::accountSummaryEnd(int reqId)
{
}

void IBKRClient::verifyMessageAPI(const std::string& apiData)
{
}

void IBKRClient::verifyCompleted(bool isSuccessful, const std::string& errorText)
{
}

void IBKRClient::displayGroupList(int reqId, const std::string& groups)
{
}

void IBKRClient::displayGroupUpdated(int reqId, const std::string& contractInfo)
{
}

void IBKRClient::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange)
{
}

void IBKRClient::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText)
{
}

void IBKRClient::connectAck()
{
    if (!mExtraAuth && mClientSocketPtr->asyncEConnect())
        mClientSocketPtr->startApi();
}

void IBKRClient::positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double avgCost)
{
}

void IBKRClient::positionMultiEnd(int reqId)
{
}

void IBKRClient::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency)
{
}

void IBKRClient::accountUpdateMultiEnd(int reqId)
{
}

void IBKRClient::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes)
{
}

void IBKRClient::securityDefinitionOptionalParameterEnd(int reqId)
{
}

void IBKRClient::softDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers)
{
}

void IBKRClient::familyCodes(const std::vector<FamilyCode>& familyCodes)
{
}

void IBKRClient::symbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions)
{
}

void IBKRClient::mktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions)
{
}

void IBKRClient::tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData)
{
}

void IBKRClient::smartComponents(int reqId, const SmartComponentsMap& theMap)
{
}

void IBKRClient::tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions)
{
}

void IBKRClient::newsProviders(const std::vector<NewsProvider>& newsProviders)
{
}

void IBKRClient::newsArticle(int requestId, int articleType, const std::string& articleText)
{
}

void IBKRClient::historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline)
{
}

void IBKRClient::historicalNewsEnd(int requestId, bool hasMore)
{
}

void IBKRClient::headTimestamp(int reqId, const std::string& headTimestamp)
{
}

void IBKRClient::histogramData(int reqId, const HistogramDataVector& data)
{
}

void IBKRClient::historicalDataUpdate(TickerId reqId, const Bar& bar)
{
}

void IBKRClient::rerouteMktDataReq(int reqId, int conid, const std::string& exchange)
{
}

void IBKRClient::rerouteMktDepthReq(int reqId, int conid, const std::string& exchange)
{
}

void IBKRClient::marketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements)
{
}

void IBKRClient::pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL)
{
}

void IBKRClient::pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value)
{
}

void IBKRClient::historicalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done)
{
}

void IBKRClient::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done)
{
}

void IBKRClient::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done)
{
}

void IBKRClient::tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions)
{
}

void IBKRClient::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttribBidAsk& tickAttribBidAsk)
{
}

void IBKRClient::tickByTickMidPoint(int reqId, time_t time, double midPoint)
{
}

void IBKRClient::orderBound(long long orderId, int apiClientId, int apiOrderId)
{
}

void IBKRClient::completedOrder(const Contract& contract, const Order& order, const OrderState& orderState)
{
}

void IBKRClient::completedOrdersEnd()
{
}

void IBKRClient::MessageListeningLoop()
{
    while (mListenForMessages)
    {
        // Wait for the request
        mOSSignal.waitForSignal();
        // Process it
        if (mReaderPtr) mReaderPtr->processMsgs();
    }
}

void IBKRClient::ContractRequestResponse::Reset()
{
    mIsDone = false;
    mReceivedContractInfos.clear();
}
