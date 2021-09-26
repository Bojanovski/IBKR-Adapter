
#include "IBKRClient.h"

#include <chrono>
#include <assert.h>

using namespace std::chrono_literals;

std::string tickTypeToStr(TickType tt)
{
    switch (tt)
    {
    case TickType::BID_SIZE:
        return "BID_SIZE";
        break;
    case TickType::BID:
        return "BID";
        break;
    case TickType::ASK:
        return "ASK";
        break;
    case TickType::ASK_SIZE:
        return "ASK_SIZE";
        break;
    case TickType::LAST:
        return "LAST";
        break;
    case TickType::LAST_SIZE:
        return "LAST_SIZE";
        break;
    case TickType::HIGH:
        return "HIGH";
        break;
    case TickType::LOW:
        return "LOW";
        break;
    case TickType::VOLUME:
        return "VOLUME";
        break;
    case TickType::CLOSE:
        return "CLOSE";
        break;
    case TickType::BID_OPTION_COMPUTATION:
        return "BID_OPTION_COMPUTATION";
        break;
    case TickType::ASK_OPTION_COMPUTATION:
        return "ASK_OPTION_COMPUTATION";
        break;
    case TickType::LAST_OPTION_COMPUTATION:
        return "LAST_OPTION_COMPUTATION";
        break;
    case TickType::MODEL_OPTION:
        return "MODEL_OPTION";
        break;
    case TickType::OPEN:
        return "OPEN";
        break;
    case TickType::LOW_13_WEEK:
        return "LOW_13_WEEK";
        break;
    case TickType::HIGH_13_WEEK:
        return "HIGH_13_WEEK";
        break;
    case TickType::LOW_26_WEEK:
        return "LOW_26_WEEK";
        break;
    case TickType::HIGH_26_WEEK:
        return "HIGH_26_WEEK";
        break;
    case TickType::LOW_52_WEEK:
        return "LOW_52_WEEK";
        break;
    case TickType::HIGH_52_WEEK:
        return "HIGH_52_WEEK";
        break;
    case TickType::AVG_VOLUME:
        return "AVG_VOLUME";
        break;
    case TickType::OPEN_INTEREST:
        return "OPEN_INTEREST";
        break;
    case TickType::OPTION_HISTORICAL_VOL:
        return "OPTION_HISTORICAL_VOL";
        break;
    case TickType::OPTION_IMPLIED_VOL:
        return "OPTION_IMPLIED_VOL";
        break;
    case TickType::OPTION_BID_EXCH:
        return "OPTION_BID_EXCH";
        break;
    case TickType::OPTION_ASK_EXCH:
        return "OPTION_ASK_EXCH";
        break;
    case TickType::OPTION_CALL_OPEN_INTEREST:
        return "OPTION_CALL_OPEN_INTEREST";
        break;
    case TickType::OPTION_PUT_OPEN_INTEREST:
        return "OPTION_PUT_OPEN_INTEREST";
        break;
    case TickType::OPTION_CALL_VOLUME:
        return "OPTION_CALL_VOLUME";
        break;
    case TickType::OPTION_PUT_VOLUME:
        return "OPTION_PUT_VOLUME";
        break;
    case TickType::INDEX_FUTURE_PREMIUM:
        return "INDEX_FUTURE_PREMIUM";
        break;
    case TickType::BID_EXCH:
        return "BID_EXCH";
        break;
    case TickType::ASK_EXCH:
        return "ASK_EXCH";
        break;
    case TickType::AUCTION_VOLUME:
        return "AUCTION_VOLUME";
        break;
    case TickType::AUCTION_PRICE:
        return "AUCTION_PRICE";
        break;
    case TickType::AUCTION_IMBALANCE:
        return "AUCTION_IMBALANCE";
        break;
    case TickType::MARK_PRICE:
        return "MARK_PRICE";
        break;
    case TickType::BID_EFP_COMPUTATION:
        return "BID_EFP_COMPUTATION";
        break;
    case TickType::ASK_EFP_COMPUTATION:
        return "ASK_EFP_COMPUTATION";
        break;
    case TickType::LAST_EFP_COMPUTATION:
        return "LAST_EFP_COMPUTATION";
        break;
    case TickType::OPEN_EFP_COMPUTATION:
        return "OPEN_EFP_COMPUTATION";
        break;
    case TickType::HIGH_EFP_COMPUTATION:
        return "HIGH_EFP_COMPUTATION";
        break;
    case TickType::LOW_EFP_COMPUTATION:
        return "LOW_EFP_COMPUTATION";
        break;
    case TickType::CLOSE_EFP_COMPUTATION:
        return "CLOSE_EFP_COMPUTATION";
        break;
    case TickType::LAST_TIMESTAMP:
        return "LAST_TIMESTAMP";
        break;
    case TickType::SHORTABLE:
        return "SHORTABLE";
        break;
    case TickType::FUNDAMENTAL_RATIOS:
        return "FUNDAMENTAL_RATIOS";
        break;
    case TickType::RT_VOLUME:
        return "RT_VOLUME";
        break;
    case TickType::HALTED:
        return "HALTED";
        break;
    case TickType::BID_YIELD:
        return "BID_YIELD";
        break;
    case TickType::ASK_YIELD:
        return "ASK_YIELD";
        break;
    case TickType::LAST_YIELD:
        return "LAST_YIELD";
        break;
    case TickType::CUST_OPTION_COMPUTATION:
        return "CUST_OPTION_COMPUTATION";
        break;
    case TickType::TRADE_COUNT:
        return "TRADE_COUNT";
        break;
    case TickType::TRADE_RATE:
        return "TRADE_RATE";
        break;
    case TickType::VOLUME_RATE:
        return "VOLUME_RATE";
        break;
    case TickType::LAST_RTH_TRADE:
        return "LAST_RTH_TRADE";
        break;
    case TickType::RT_HISTORICAL_VOL:
        return "RT_HISTORICAL_VOL";
        break;
    case TickType::IB_DIVIDENDS:
        return "IB_DIVIDENDS";
        break;
    case TickType::BOND_FACTOR_MULTIPLIER:
        return "BOND_FACTOR_MULTIPLIER";
        break;
    case TickType::REGULATORY_IMBALANCE:
        return "REGULATORY_IMBALANCE";
        break;
    case TickType::NEWS_TICK:
        return "NEWS_TICK";
        break;
    case TickType::SHORT_TERM_VOLUME_3_MIN:
        return "SHORT_TERM_VOLUME_3_MIN";
        break;
    case TickType::SHORT_TERM_VOLUME_5_MIN:
        return "SHORT_TERM_VOLUME_5_MIN";
        break;
    case TickType::SHORT_TERM_VOLUME_10_MIN:
        return "SHORT_TERM_VOLUME_10_MIN";
        break;
    case TickType::DELAYED_BID:
        return "DELAYED_BID";
        break;
    case TickType::DELAYED_ASK:
        return "DELAYED_ASK";
        break;
    case TickType::DELAYED_LAST:
        return "DELAYED_LAST";
        break;
    case TickType::DELAYED_BID_SIZE:
        return "DELAYED_BID_SIZE";
        break;
    case TickType::DELAYED_ASK_SIZE:
        return "DELAYED_ASK_SIZE";
        break;
    case TickType::DELAYED_LAST_SIZE:
        return "DELAYED_LAST_SIZE";
        break;
    case TickType::DELAYED_HIGH:
        return "DELAYED_HIGH";
        break;
    case TickType::DELAYED_LOW:
        return "DELAYED_LOW";
        break;
    case TickType::DELAYED_VOLUME:
        return "DELAYED_VOLUME";
        break;
    case TickType::DELAYED_CLOSE:
        return "DELAYED_CLOSE";
        break;
    case TickType::DELAYED_OPEN:
        return "DELAYED_OPEN";
        break;
    case TickType::RT_TRD_VOLUME:
        return "RT_TRD_VOLUME";
        break;
    case TickType::CREDITMAN_MARK_PRICE:
        return "CREDITMAN_MARK_PRICE";
        break;
    case TickType::CREDITMAN_SLOW_MARK_PRICE:
        return "CREDITMAN_SLOW_MARK_PRICE";
        break;
    case TickType::DELAYED_BID_OPTION_COMPUTATION:
        return "DELAYED_BID_OPTION_COMPUTATION";
        break;
    case TickType::DELAYED_ASK_OPTION_COMPUTATION:
        return "DELAYED_ASK_OPTION_COMPUTATION";
        break;
    case TickType::DELAYED_LAST_OPTION_COMPUTATION:
        return "DELAYED_LAST_OPTION_COMPUTATION";
        break;
    case TickType::DELAYED_MODEL_OPTION_COMPUTATION:
        return "DELAYED_MODEL_OPTION_COMPUTATION";
        break;
    case TickType::LAST_EXCH:
        return "LAST_EXCH";
        break;
    case TickType::LAST_REG_TIME:
        return "LAST_REG_TIME";
        break;
    case TickType::FUTURES_OPEN_INTEREST:
        return "FUTURES_OPEN_INTEREST";
        break;
    case TickType::AVG_OPT_VOLUME:
        return "AVG_OPT_VOLUME";
        break;
    case TickType::DELAYED_LAST_TIMESTAMP:
        return "DELAYED_LAST_TIMESTAMP";
        break;
    case TickType::SHORTABLE_SHARES:
        return "SHORTABLE_SHARES";
        break;
    case TickType::NOT_SET:
        return "NOT_SET";
        break;
    default:
        return std::to_string((int)tt);
        break;
    }
}

int IBKRClient::mClientCount = 0;

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
    , mContractRequestId(0)
    , mMarketDataRequestId(0)
    , mIsTryingToConnect(false)
{

}

IBKRClient::~IBKRClient()
{
    Disconnect();

    // Make sure all of the threads are done
    if (mAsyncConnectionThread.joinable()) mAsyncConnectionThread.join();
    if (mMessgeListeningThread.joinable()) mMessgeListeningThread.join();
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
    assert(*implementation); // must not be null
    IBKRClient* ibkrClientImpl = dynamic_cast<IBKRClient*>(*implementation);
    assert(ibkrClientImpl); // must inherit from IBKRClient

    delete ibkrClientImpl;
    *implementation = nullptr;
}

void GET_INFO_FUNC(ConnectionAdapterLibraryInfo* info)
{
    strcpy_s(info->Name,        sizeof(info->Name),         "IBKR");
    strcpy_s(info->Version,     sizeof(info->Version),      "v1.0");
    strcpy_s(info->Description, sizeof(info->Description),  "A connection adapter for the IBKR (Interactive Brokers) API (application programming interface).");

    info->SupportedFeatures.PlaceLimitOrders = true;
    info->SupportedFeatures.PlaceMarketOrders = false;

    info->Parameters.Count = 2; // we need IP and port
}

void GET_PARAM_INFO_FUNC(ConnectionAdapterParameterInfo* info)
{
    strcpy_s(info[0].Name,              sizeof(info[0].Name), "IP");
    strcpy_s(info[0].Default.ValueStr,  sizeof(info[0].Name), "127.0.0.1");
    info[0].Type = ConnectionAdapterParameter::ValueType::String;

    strcpy_s(info[1].Name,              sizeof(info[1].Name), "Port");
    info[1].Default.ValueInt = 7497;
    info[1].Type = ConnectionAdapterParameter::ValueType::Integer;
}

//
// IGenericConnectionAdapter implementation
//

void IBKRClient::SetLogFunction(LogFunction* logFunctionPtr, void* logObjectPtr)
{
    mLogFunctionPtr = logFunctionPtr;
    mLogObjectPtr = logObjectPtr;
}

void IBKRClient::Connect(const ConnectInfo& connectInfo)
{
    // Set the trying to connect flag
    mIsTryingToConnect = true;

    // Save the connection data
    void* callbackObject = connectInfo.CallbackObject;
    ConnectCallbackFunction* callbackFunctionPtr = connectInfo.CallbackFunctionPtr;
    int clientId = mClientCount++;
    ConnectionAdapterParameter::Value paramIP = connectInfo.ParameterValues[0];
    ConnectionAdapterParameter::Value paramPort = connectInfo.ParameterValues[1];

    // Start the thread
    if (mAsyncConnectionThread.joinable()) mAsyncConnectionThread.join();
    mAsyncConnectionThread = std::thread([this, callbackObject, callbackFunctionPtr, clientId, paramIP, paramPort]() {

        // Create the result object
        ConnectResult result;
        result.CallbackObject = callbackObject;

        // Lock the mutex
        std::unique_lock<std::mutex> lk(mConnectionMutex);
        bool res = this->mClientSocketPtr->eConnect(paramIP.ValueStr, paramPort.ValueInt, clientId, mExtraAuth);
        if (res)
        {
            result.Status = ResultStatus::Success;

            // Fire up the reader
            this->mReaderPtr = std::make_unique<EReader>(this->mClientSocketPtr.get(), &mOSSignal);
            this->mReaderPtr->start();
    
            // Start listening for messages
            StartListeningForMessages();
        }
        else
        {
            result.Status = ResultStatus::Failure;
        }

        // The callback could be intefacing with the class and therfore locking
        // mutexes such as mConnectionMutex, so we unlock it here to prevent a deadlock.
        lk.unlock();
        mIsTryingToConnect = false;
        callbackFunctionPtr(result);
        });
}

ConnectionStatus IBKRClient::GetConnectionStatus()
{
    ConnectionStatus retVal;
    if (mIsTryingToConnect)
    {
        // The state from mClientSocketPtr does not accurately represent
        // if the user is trying to connect because the connect function
        // which sets this state to 'CS_CONNECTING' is called in a different thread
        // then the thread from which the IBKRClient::Connect was called.
        retVal = ConnectionStatus::Connecting;
    }
    else if (mConnectionMutex.try_lock())
    {
        // If the flag for trying to connect is not true, that must
        // mean that the connection is either successfully established
        // or that it failed.
        EClient::ConnState state = mClientSocketPtr->connState();
        switch (state)
        {
        case EClient::ConnState::CS_CONNECTED:
            retVal = ConnectionStatus::Connected;
            break;
        case EClient::ConnState::CS_CONNECTING:
        case EClient::ConnState::CS_DISCONNECTED:
        case EClient::ConnState::CS_REDIRECT:
        default:
            retVal = ConnectionStatus::Disconnected;
            break;
        }
        mConnectionMutex.unlock();
    }
    else
    {
        // The mutex is locked but the connetion is not 
        // being attempted. We must be in a destructor in 
        // another thread.
        retVal = ConnectionStatus::Disconnected;
    }
    return retVal;
}

void IBKRClient::Disconnect()
{
    std::unique_lock<std::mutex> lk(mConnectionMutex);
    mClientSocketPtr->eDisconnect();
    StopListeningForMessages();
    mReaderPtr.reset();
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
}

void IBKRClient::FromContractInfoToContract(Contract& contractOut, const ContractInfo& contractInfoIn)
{
    contractOut.conId = ContractInfo_To_ContractId[contractInfoIn];
    contractOut.symbol = contractInfoIn.Symbol;
    contractOut.currency = contractInfoIn.Currency;
    contractOut.exchange = contractInfoIn.Exchange;

    bool isValidExpDate = true;
    for (int i = 0; i < EXPIRY_DATE_SIZE; ++i)
    {
        char c = contractInfoIn.ExpiryDate[i];
        if (c < 48 || c > 57)
        {
            isValidExpDate = false;
            break;
        }
    }

    // The security's type:
    // STK - stock (or ETF)
    // OPT - option
    // FUT - future
    // IND - index
    // FOP - futures option
    // CASH - forex pair
    // BAG - combo
    // WAR - warrant
    // BOND- bond
    // CMDTY- commodity
    // NEWS- news
    // FUND- mutual fund
    switch (contractInfoIn.Type)
    {
    case SecurityType::Stock:
        contractOut.secType = "STK";
        break;

    case SecurityType::Future:
        contractOut.secType = "FUT";
        if (isValidExpDate)
        {
            contractOut.lastTradeDateOrContractMonth = std::string(contractInfoIn.ExpiryDate, EXPIRY_DATE_SIZE);
        }
        else
        {
            contractOut.lastTradeDateOrContractMonth = "";
        }
        break;

    case SecurityType::Option:
        contractOut.secType = "OPT";
        break;

    case SecurityType::Forex:
        contractOut.secType = "CASH";
        break;
    }
}

void IBKRClient::FromContractDetailsToContractInfo(ContractInfo& contractInfoOut, const ContractDetails& contractDetailsIn)
{
    strcpy_s(contractInfoOut.Symbol, contractDetailsIn.contract.symbol.c_str());
    strcpy_s(contractInfoOut.Exchange, contractDetailsIn.contract.exchange.c_str());
    strcpy_s(contractInfoOut.Currency, contractDetailsIn.contract.currency.c_str());

    if (contractDetailsIn.contract.secType.compare("STK") == 0)
    {
        contractInfoOut.Type = SecurityType::Stock;
    }
    if (contractDetailsIn.contract.secType.compare("FUT") == 0)
    {
        contractInfoOut.Type = SecurityType::Future;
        memcpy(contractInfoOut.ExpiryDate, contractDetailsIn.contract.lastTradeDateOrContractMonth.data(), 8);
    }
    if (contractDetailsIn.contract.secType.compare("OPT") == 0)
    {
        contractInfoOut.Type = SecurityType::Option;
    }
    if (contractDetailsIn.contract.secType.compare("CASH") == 0)
    {
        contractInfoOut.Type = SecurityType::Forex;
    }
}

void IBKRClient::FromBarToHistoricalBarEntry(HistoricalBarEntry& historicalBarEntry, const Bar& bar)
{
    std::string yearStr = bar.time.size() >= 4 ? bar.time.substr(0, 4) : "";
    std::string monthStr = bar.time.size() >= 6 ? bar.time.substr(4, 2) : "";
    std::string dayStr = bar.time.size() >= 8 ? bar.time.substr(6, 2) : "";
    std::string hourStr = bar.time.size() >= 12 ? bar.time.substr(10, 2) : "";
    std::string minuteStr = bar.time.size() >= 15 ? bar.time.substr(13, 2) : "";
    std::string secondStr = bar.time.size() >= 18 ? bar.time.substr(16, 2) : "";

    struct tm timeStruct = {0};
    timeStruct.tm_year = yearStr.empty() ? 0 : (std::atoi(yearStr.c_str()) - 1900);
    timeStruct.tm_mon = monthStr.empty() ? 0 : (std::atoi(monthStr.c_str()) - 1);
    timeStruct.tm_mday = dayStr.empty() ? 1 : std::atoi(dayStr.c_str());
    timeStruct.tm_hour = hourStr.empty() ? 0 : std::atoi(hourStr.c_str());
    timeStruct.tm_min = minuteStr.empty() ? 0 : std::atoi(minuteStr.c_str());
    timeStruct.tm_sec = secondStr.empty() ? 0 : std::atoi(secondStr.c_str());
    time_t time = mktime(&timeStruct);

    historicalBarEntry.Time = time;
    historicalBarEntry.Open = bar.open;
    historicalBarEntry.High = bar.high;
    historicalBarEntry.Low = bar.low;
    historicalBarEntry.Close = bar.close;
    historicalBarEntry.Volume = bar.volume;
}

void IBKRClient::GetContractCount(const ContractInfo& query, ContractQueryResult* result)
{
    Contract contract;
    FromContractInfoToContract(contract, query);
    mClientSocketPtr->reqContractDetails(mContractRequestId, contract);

    // Wait until the data is received
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    mRequestId_To_ContractRequestResponse[mContractRequestId].Reset();
    bool waitResultSuccess = mContractRequestConditionVariable.wait_for(lk, mSignalWaitTimeout * 1ms, [this] {return this->mRequestId_To_ContractRequestResponse[this->mContractRequestId].mIsDone; });

   if (waitResultSuccess)
   {
       // Get the contracts information
       result->RequestId = mContractRequestId;
       result->ContractCount = (int)mRequestId_To_ContractRequestResponse[mContractRequestId].mReceivedContractInfos.size();
       result->Status = ResultStatus::Success;
   }
   else
   {
       result->RequestId = -1;
       result->ContractCount = 0;
       result->Status = ResultStatus::WaitTimeout;
   }

    // Increase the request id for future requests
    ++mContractRequestId;

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again
    lk.unlock();
    mContractRequestConditionVariable.notify_one();
}

void IBKRClient::GetContracts(const ContractQueryResult& requestResult, ContractInfo* resultArray)
{
    if (requestResult.Status == ResultStatus::Success)
    {
        auto& contractInfos = mRequestId_To_ContractRequestResponse[requestResult.RequestId].mReceivedContractInfos;
        for (int i = 0; i < contractInfos.size(); ++i)
        {
            resultArray[i] = contractInfos[i];
        }
    }

    // Clear the data to preserve memory
    mRequestId_To_ContractRequestResponse[requestResult.RequestId].Reset();
}

void IBKRClient::RequestBaseMarketData(const BaseMarketDataInfo& marketDataInfo, DataRequestResult* result)
{
    std::string logMsg = std::string((std::string)"Market data request submitted for: " +
        marketDataInfo.ConInfoPtr->ToShortString()) +
        " Request Id: " + std::to_string(mMarketDataRequestId);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Set the contract info
    Contract contract;
    FromContractInfoToContract(contract, *marketDataInfo.ConInfoPtr);

    // by default only real - time(1) market data is enabled sending 1 (real - time) disables frozen, delayed and delayed-frozen market data
    // sending 2 (frozen)enables frozen market data
    // sending 3 (delayed)enables delayed and disables delayed - frozen market data
    // sending 4 (delayed - frozen) enables delayed and delayed - frozen market data
    MarketDataType mktType = MarketDataType::DELAYED_FROZEN;
    mClientSocketPtr->reqMarketDataType((int)mktType);
    
    // Request the data
    mClientSocketPtr->reqMktData(mMarketDataRequestId, contract, "", false, false, TagValueListSPtr());

    // Fill the return structure
    result->RequestId = mMarketDataRequestId;
    result->Type = DataRequestType::MarketData;

    // Save the receive function and object
    mRequestId_To_ReceivePriceSizeFunc[mMarketDataRequestId] = marketDataInfo.ReceivePriceSizeDataFunctionPtr;
    mRequestId_To_ReceiveVolumeFunc[mMarketDataRequestId] = marketDataInfo.ReceiveVolumeDataFunctionPtr;
    mRequestId_To_ReceivePriceFunc[mMarketDataRequestId] = marketDataInfo.ReceivePriceDataFunctionPtr;
    mRequestId_To_ReceiveObject[mMarketDataRequestId] = marketDataInfo.ReceiveBaseMarketDataObjectPtr;

    // Increase the request id for future requests
    ++mMarketDataRequestId;
}

void IBKRClient::RequestTimeAndSalesData(const TimeAndSalesDataInfo& dataInfo, DataRequestResult* result)
{
    std::string logMsg = std::string((std::string)"Time and Sales data request submitted for: " +
        dataInfo.ConInfoPtr->ToShortString()) +
        " Request Id: " + std::to_string(mMarketDataRequestId);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Set the contract info
    Contract contract;
    FromContractInfoToContract(contract, *dataInfo.ConInfoPtr);

    // Request the data
    mClientSocketPtr->reqTickByTickData(mMarketDataRequestId, contract, "Last", 0, false);

    // Fill the return structure
    result->RequestId = mMarketDataRequestId;
    result->Type = DataRequestType::TimeAndSales;

    //// Save the receive function and object
    mRequestId_To_ReceiveTimeAndSalesFunc[mMarketDataRequestId] = dataInfo.ReceiveTimeAndSalesDataFunctionPtr;
    mRequestId_To_ReceiveObject[mMarketDataRequestId] = dataInfo.ReceiveTimeAndSalesDataObjectPtr;

    // Increase the request id for future requests
    ++mMarketDataRequestId;
}

void IBKRClient::RequestLimitOrderBookData(const LimitOrderBookDataInfo& dataInfo, DataRequestResult* result)
{
    std::string logMsg = std::string((std::string)"Limit Order Book data request submitted for: " +
        dataInfo.ConInfoPtr->ToShortString()) +
        " Request Id: " + std::to_string(mMarketDataRequestId);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Set the contract info
    Contract contract;
    FromContractInfoToContract(contract, *dataInfo.ConInfoPtr);

    // Request the data
    mClientSocketPtr->reqMktDepth(mMarketDataRequestId, contract, dataInfo.Depth, true, TagValueListSPtr());

    // Fill the return structure
    result->RequestId = mMarketDataRequestId;
    result->Type = DataRequestType::LimitOrderBook;

    //// Save the receive function and object
    mRequestId_To_ReceiveLOBOperationFunc[mMarketDataRequestId] = dataInfo.LOBDataOperationFunctionPtr;
    mRequestId_To_ReceiveLOBFunc[mMarketDataRequestId] = dataInfo.LOBDataFunctionPtr;
    mRequestId_To_ReceiveObject[mMarketDataRequestId] = dataInfo.LOBDataObjectPtr;

    // Initialize the structure
    mRequestId_To_LOB[mMarketDataRequestId] = std::make_unique<LimitOrderBook>(dataInfo.Depth);

    // Increase the request id for future requests
    ++mMarketDataRequestId;
}

void IBKRClient::GetMarketMakerName(const DataRequestResult& requestResult, int MMId, char* nameDest, int *nameSize)
{
    LimitOrderBook* lobPtr = mRequestId_To_LOB[requestResult.RequestId].get();
    std::string name = lobPtr->MMId_To_Name[MMId];
    *nameSize = (int)name.size();
    assert(*nameSize <= MAX_MARKET_MAKER_NAME);
    memcpy(nameDest, name.c_str(), *nameSize);
}

void IBKRClient::RequestHistoricalData(const HistoricalDataInfo& dataInfo, DataRequestResult* result)
{
    std::string logMsg = std::string((std::string)"Historical data request submitted for: " +
        dataInfo.ConInfoPtr->ToShortString()) +
        " Request Id: " + std::to_string(mMarketDataRequestId);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Set the contract info
    Contract contract;
    FromContractInfoToContract(contract, *dataInfo.ConInfoPtr);

    std::string endTimeDate = ""; // <- current present moment

    //  Valid Duration String units
    //  Unit	Description
    //-------------------------------------------------------------------------------------------
    //  S	    Seconds
    //  D	    Day
    //  W	    Week
    //  M	    Month
    //  Y	    Year
    std::string duration;
    switch (dataInfo.Duration.Type)
    {
    case HistoricalDataInfo::TimeUnit::Second:
        duration = std::to_string(dataInfo.Duration.Value) + " S";
        break;

    case HistoricalDataInfo::TimeUnit::Day:
        duration = std::to_string(dataInfo.Duration.Value) + " D";
        break;

    case HistoricalDataInfo::TimeUnit::Week:
        duration = std::to_string(dataInfo.Duration.Value) + " W";
        break;

    case HistoricalDataInfo::TimeUnit::Month:
        duration = std::to_string(dataInfo.Duration.Value) + " M";
        break;

    case HistoricalDataInfo::TimeUnit::Year:
        duration = std::to_string(dataInfo.Duration.Value) + " Y";
        break;

    default:
        logMsg = "Unsupported duration time unit type";
        mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
        return;
    }

    //  Valid Bar Sizes
    //  Size
    //-------------------------------------------------------------------------------------------
    //  1 secs	5 secs	10 secs	15 secs	30 secs
    //  1 min	2 mins	3 mins	5 mins	10 mins	15 mins	20 mins	30 mins
    //  1 hour	2 hours	3 hours	4 hours	8 hours
    //  1 day
    //  1 week
    //  1 month
    std::string barSize;
    switch (dataInfo.Bar.Type)
    {
    case HistoricalDataInfo::TimeUnit::Second:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 sec";
        }
        else if (dataInfo.Bar.Value == 5 ||
            dataInfo.Bar.Value == 10 ||
            dataInfo.Bar.Value == 15 ||
            dataInfo.Bar.Value == 30)
        {
            barSize = std::to_string(dataInfo.Bar.Value) + " secs";
        }
        else
        {
            logMsg = "Valid number of seconds in a single bar can only be 1, 5, 10, 15 or 30. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    case HistoricalDataInfo::TimeUnit::Minute:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 min";
        }
        else if (dataInfo.Bar.Value == 2 ||
            dataInfo.Bar.Value == 3 ||
            dataInfo.Bar.Value == 5 ||
            dataInfo.Bar.Value == 10 ||
            dataInfo.Bar.Value == 15 ||
            dataInfo.Bar.Value == 20 ||
            dataInfo.Bar.Value == 30)
        {
            barSize = std::to_string(dataInfo.Bar.Value) + " mins";
        }
        else
        {
            logMsg = "Valid number of minutes in a single bar can only be 1, 2, 3, 5, 10, 15, 20 or 30. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    case HistoricalDataInfo::TimeUnit::Hour:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 hour";
        }
        else if (dataInfo.Bar.Value == 2 ||
            dataInfo.Bar.Value == 3 ||
            dataInfo.Bar.Value == 4 ||
            dataInfo.Bar.Value == 8)
        {
            barSize = std::to_string(dataInfo.Bar.Value) + " hours";
        }
        else
        {
            logMsg = "Valid number of hours in a single bar can only be 1, 2, 3, 4 or 8. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    case HistoricalDataInfo::TimeUnit::Day:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 day";
        }
        else
        {
            logMsg = "Valid number of days in a single bar can only be 1. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    case HistoricalDataInfo::TimeUnit::Week:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 week";
        }
        else
        {
            logMsg = "Valid number of weeks in a single bar can only be 1. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    case HistoricalDataInfo::TimeUnit::Month:
        if (dataInfo.Bar.Value == 1)
        {
            barSize = "1 month";
        }
        else
        {
            logMsg = "Valid number of months in a single bar can only be 1. The value entered is: " +
                std::to_string(dataInfo.Bar.Value);
            mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
            return;
        }
        break;

    default:
        logMsg = "Unsupported bar time unit type";
        mLogFunctionPtr(mLogObjectPtr, LogType::Error, logMsg.c_str());
        return;
    }

    //Historical Data Types
    //  Type	                        Open	High	Low	Close	Volume
    //-------------------------------------------------------------------------------------------
    //  TRADES	                        First traded price	Highest traded price	Lowest traded price	Last traded price	Total traded volume
    //  MIDPOINT	                    Starting midpoint price	Highest midpoint price	Lowest midpoint price	Last midpoint price	N / A
    //  BID	                            Starting bid price	Highest bid price	Lowest bid price	Last bid price	N / A
    //  ASK	                            Starting ask price	Highest ask price	Lowest ask price	Last ask price	N / A
    //  BID_ASK	                        Time average bid	Max Ask	Min Bid	Time average ask	N / A
    //  ADJUSTED_LAST	                Dividend - adjusted first traded price	Dividend - adjusted high trade	Dividend - adjusted low trade	Dividend - adjusted last trade	Total traded volume
    //  HISTORICAL_VOLATILITY	        Starting volatility	Highest volatility	Lowest volatility	Last volatility	N / A
    //  OPTION_IMPLIED_VOLATILITY	    Starting implied volatility	Highest implied volatility	Lowest implied volatility	Last implied volatility	N / A
    //  REBATE_RATE	                    Starting rebate rate	Highest rebate rate	Lowest rebate rate	Last rebate rate	N / A
    //  FEE_RATE	                    Starting fee rate	Highest fee rate	Lowest fee rate	Last fee rate	N / A
    //  YIELD_BID	                    Starting bid yield	Highest bid yield	Lowest bid yield	Last bid yield	N / A
    //  YIELD_ASK	                    Starting ask yield	Highest ask yield	Lowest ask yield	Last ask yield	N / A
    //  YIELD_BID_ASK	                Time average bid yield	Highest ask yield	Lowest bid yield	Time average ask yield	N / A
    //  YIELD_LAST	                    Starting last yield	Highest last yield	Lowest last yield	Last last yield     N / A
    std::string whatToShow = "TRADES";
    if (dataInfo.ConInfoPtr->Type == SecurityType::Forex)
    {
        // Forex doesn't support the trades show type
        whatToShow = "MIDPOINT";
    }

    // Whether (1) or not (0) to retrieve data generated only within Regular Trading Hours (RTH)
    int useRTH = 1;

    // Request the data
    mClientSocketPtr->reqHistoricalData(mMarketDataRequestId, contract, endTimeDate, duration, barSize, whatToShow, useRTH, 1, true, TagValueListSPtr());

    // Fill the return structure
    result->RequestId = mMarketDataRequestId;
    result->Type = DataRequestType::Historical;

    //// Save the receive function and object
    mRequestId_To_ReceiveHistoricalDataFunc[mMarketDataRequestId] = dataInfo.HistoricalDataOperationFunctionPtr;
    mRequestId_To_ReceiveObject[mMarketDataRequestId] = dataInfo.HistoricalDataObjectPtr;

    // Increase the request id for future requests
    ++mMarketDataRequestId;
}

void IBKRClient::CancelMarketData(const DataRequestResult& requestResult)
{
    std::string logMsg;

    switch (requestResult.Type)
    {
    case DataRequestType::MarketData:
        logMsg = std::string((std::string)"Market data cancelled. Request Id: " + std::to_string(requestResult.RequestId));
        mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
        mClientSocketPtr->cancelMktData(requestResult.RequestId);
        break;

    case DataRequestType::TimeAndSales:
        logMsg = std::string((std::string)"Time&Sales data cancelled. Request Id: " + std::to_string(requestResult.RequestId));
        mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
        mClientSocketPtr->cancelTickByTickData(requestResult.RequestId);
        break;

    case DataRequestType::LimitOrderBook:
        logMsg = std::string((std::string)"Limit Order Book data cancelled. Request Id: " + std::to_string(requestResult.RequestId));
        mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
        mClientSocketPtr->cancelMktDepth(requestResult.RequestId, true);
        break;

    case DataRequestType::Historical:
        logMsg = std::string((std::string)"Historical data cancelled. Request Id: " + std::to_string(requestResult.RequestId));
        mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
        mClientSocketPtr->cancelHistoricalData(requestResult.RequestId);
        break;
    }

    // Erase all records to save memory
    //mRequestId_To_ReceiveObject.erase(requestResult.RequestId);
    //mRequestId_To_ReceivePriceSizeFunc.erase(requestResult.RequestId);
    //mRequestId_To_ReceiveVolumeFunc.erase(requestResult.RequestId);
    //mRequestId_To_ReceivePriceFunc.erase(requestResult.RequestId);
    //mRequestIdDataType_To_PriceSize.erase(requestResult.RequestId);
    //mRequestId_To_Volume.erase(requestResult.RequestId);
    //mRequestIdPriceType_To_Price.erase(requestResult.RequestId);
    //mRequestId_To_ReceiveTimeAndSalesFunc.erase(requestResult.RequestId);
    //mRequestId_To_LOB.erase(requestResult.RequestId);
    //mRequestId_To_ReceiveLOBOperationFunc.erase(requestResult.RequestId);
    //mRequestId_To_ReceiveLOBFunc.erase(requestResult.RequestId);
}

void IBKRClient::ManageOrder(const OrderInfo& orderInfo, PlaceOrderResult* result)
{
    // Set the order info
    Order order;
    switch (orderInfo.Type)
    {
    case OrderType::Limit:
        order.orderType = "LMT";
        break;
    case OrderType::Market:
        order.orderType = "MKT";
        break;
    }
    switch (orderInfo.Action)
    {
    case ActionType::Buy:
        order.action = "BUY";
        break;
    case ActionType::Sell:
        order.action = "SELL";
        break;
    }
    order.totalQuantity = orderInfo.Quantity;
    order.lmtPrice = orderInfo.LimitOrderInfo.Price;
    order.orderId = orderInfo.Id;

    // These flags generated "not supported" errors if left true
    order.eTradeOnly = false;
    order.firmQuoteOnly = false;

    // Set the contract info
    Contract contract;
    FromContractInfoToContract(contract, *orderInfo.ConInfoPtr);

    bool isUsed = mOrderIdsInUse.find(order.orderId) != mOrderIdsInUse.end();
    bool isCanceled = mCanceledOrderIds.find(order.orderId) != mCanceledOrderIds.end();
    if (isUsed && !isCanceled) // use the old order Id, we are modifiying the order
    {
        // Update the order
        mClientSocketPtr->placeOrder(order.orderId, contract, order);
        result->Id = order.orderId;
        result->Status = ResultStatus::Success;
        result->Type = OrderResultType::ModifiedOrder;
    }
    else // we need a new order Id
    {
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
            result->Type = OrderResultType::NewOrder;
            mOrderIdsInUse.insert(orderId);
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
}

void IBKRClient::CancelOrder(const PlaceOrderResult& orderResult)
{
    if (mOrderIdsInUse.find(orderResult.Id) != mOrderIdsInUse.end()) // use the old order Id, we are modifiying the order
    {
        // Update the order
        mClientSocketPtr->cancelOrder(orderResult.Id);
        mCanceledOrderIds.insert(orderResult.Id);
    }
}


//
// EWrapper implementation
//

void IBKRClient::tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib)
{
    std::string logMsg = std::string(
        (std::string)"Tick Price. Ticker Id: " + std::to_string(tickerId) +
        (std::string)", Field: " + tickTypeToStr(field) +
        (std::string)", Price: " + std::to_string(price) +
        (std::string)", CanAutoExecute: " + std::to_string(attrib.canAutoExecute) +
        (std::string)", PastLimit: " + std::to_string(attrib.pastLimit) +
        (std::string)", PreOpen: " + std::to_string(attrib.preOpen));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Decide what to do based on the field type
    void* receiveObj = mRequestId_To_ReceiveObject[tickerId];
    ReceiveMarketDataType marketDataType;
    ReceivePriceDataType priceDataType;
    // For tick types see: http://interactivebrokers.github.io/tws-api/tick_types.html
    switch (field)
    {
    case TickType::ASK:
    case TickType::ASK_SIZE:
    case TickType::DELAYED_ASK:
    case TickType::DELAYED_ASK_SIZE:
        marketDataType = ReceiveMarketDataType::Ask;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first = price;
        break;

    case TickType::BID:
    case TickType::BID_SIZE:
    case TickType::DELAYED_BID:
    case TickType::DELAYED_BID_SIZE:
        marketDataType = ReceiveMarketDataType::Bid;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first = price;
        break;

    case TickType::LAST:
    case TickType::LAST_SIZE:
    case TickType::DELAYED_LAST:
    case TickType::DELAYED_LAST_SIZE:
        marketDataType = ReceiveMarketDataType::Last;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first = price;
        break;

    case TickType::HIGH:
    case TickType::DELAYED_HIGH:
        priceDataType = ReceivePriceDataType::High;
        mRequestIdPriceType_To_Price[tickerId][priceDataType] = price;
        if (mRequestId_To_ReceivePriceFunc[tickerId])
            mRequestId_To_ReceivePriceFunc[tickerId](receiveObj, tickerId, priceDataType, price);
        break;

    case TickType::LOW:
    case TickType::DELAYED_LOW:
        priceDataType = ReceivePriceDataType::Low;
        mRequestIdPriceType_To_Price[tickerId][priceDataType] = price;
        if (mRequestId_To_ReceivePriceFunc[tickerId])
            mRequestId_To_ReceivePriceFunc[tickerId](receiveObj, tickerId, priceDataType, price);
        break;

    case TickType::OPEN:
    case TickType::DELAYED_OPEN:
        priceDataType = ReceivePriceDataType::Open;
        mRequestIdPriceType_To_Price[tickerId][priceDataType] = price;
        if (mRequestId_To_ReceivePriceFunc[tickerId])
            mRequestId_To_ReceivePriceFunc[tickerId](receiveObj, tickerId, priceDataType, price);
        break;

    case TickType::CLOSE:
    case TickType::DELAYED_CLOSE:
        priceDataType = ReceivePriceDataType::Close;
        mRequestIdPriceType_To_Price[tickerId][priceDataType] = price;
        if (mRequestId_To_ReceivePriceFunc[tickerId])
            mRequestId_To_ReceivePriceFunc[tickerId](receiveObj, tickerId, priceDataType, price);
        break;

    default:
        marketDataType = ReceiveMarketDataType::Unknown;
        break;
    }
}

void IBKRClient::tickSize(TickerId tickerId, TickType field, int size)
{
    std::string logMsg = std::string(
        (std::string)"Tick Size. Ticker Id: " + std::to_string(tickerId) +
        (std::string)", Field: " + tickTypeToStr(field) +
        (std::string)", Size: " + std::to_string(size));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    // Decide what to do based on the field type
    void* receiveObj = mRequestId_To_ReceiveObject[tickerId];
    ReceiveMarketDataType marketDataType;
    double price;
    // For tick types see: http://interactivebrokers.github.io/tws-api/tick_types.html
    switch (field)
    {
    case TickType::ASK:
    case TickType::ASK_SIZE:
    case TickType::DELAYED_ASK:
    case TickType::DELAYED_ASK_SIZE:
        marketDataType = ReceiveMarketDataType::Ask;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].second = size;
        price = mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first;
        if (mRequestId_To_ReceivePriceSizeFunc[tickerId])
            mRequestId_To_ReceivePriceSizeFunc[tickerId](receiveObj, tickerId, marketDataType, price, size);
        break;

    case TickType::BID:
    case TickType::BID_SIZE:
    case TickType::DELAYED_BID:
    case TickType::DELAYED_BID_SIZE:
        marketDataType = ReceiveMarketDataType::Bid;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].second = size;
        price = mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first;
        if (mRequestId_To_ReceivePriceSizeFunc[tickerId])
            mRequestId_To_ReceivePriceSizeFunc[tickerId](receiveObj, tickerId, marketDataType, price, size);
        break;

    case TickType::LAST:
    case TickType::LAST_SIZE:
    case TickType::DELAYED_LAST:
    case TickType::DELAYED_LAST_SIZE:
        marketDataType = ReceiveMarketDataType::Last;
        mRequestIdDataType_To_PriceSize[tickerId][marketDataType].second = size;
        price = mRequestIdDataType_To_PriceSize[tickerId][marketDataType].first;
        if (mRequestId_To_ReceivePriceSizeFunc[tickerId])
            mRequestId_To_ReceivePriceSizeFunc[tickerId](receiveObj, tickerId, marketDataType, price, size);
        break;

    case TickType::VOLUME:
    case TickType::DELAYED_VOLUME:
        mRequestId_To_Volume[tickerId] = size;
        if (mRequestId_To_ReceiveVolumeFunc[tickerId])
            mRequestId_To_ReceiveVolumeFunc[tickerId](receiveObj, tickerId, size);
        break;

    default:
        marketDataType = ReceiveMarketDataType::Unknown;
        break;
    }
}

void IBKRClient::tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{
}

void IBKRClient::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
    std::string logMsg = std::string(
        (std::string)"Tick Generic. Ticker Id: " + std::to_string(tickerId) +
        (std::string)", Type: " + tickTypeToStr(tickType) +
        (std::string)", Value: " + std::to_string(value));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
}

void IBKRClient::tickString(TickerId tickerId, TickType tickType, const std::string& value)
{
    std::string valueStr = value;
    if (tickType == TickType::LAST_TIMESTAMP ||
        tickType == TickType::LAST_REG_TIME ||
        tickType == TickType::DELAYED_LAST_TIMESTAMP)
    {
        long long timeVal = std::stoll(value);
        valueStr = FromUNIXTimeToString(timeVal);
    }

    std::string logMsg = std::string(
        (std::string)"Tick String. Ticker Id: " + std::to_string(tickerId) +
        (std::string)", Type: " + tickTypeToStr(tickType) +
        (std::string)", Value: " + valueStr);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
}

void IBKRClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate)
{
}

void IBKRClient::orderStatus(OrderId orderId, const std::string& status, double filled, double remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, std::string("Got order: " + std::to_string(orderId) + ", Status: " + status).c_str());
}

void IBKRClient::openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, std::string("Got open order: " + std::to_string(orderId)).c_str());
}

void IBKRClient::openOrderEnd()
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, std::string("Got open order feed end").c_str());
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
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, ("Got new valid Id: " + std::to_string(orderId)).c_str());
    mOrderId = orderId;
    lk.unlock();
    mOrderIdConditionVariable.notify_one();
}

void IBKRClient::contractDetails(int reqId, const ContractDetails& contractDetails)
{
    // Append the contract
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    mRequestId_To_ContractRequestResponse[reqId].mReceivedContractInfos.push_back(ContractInfo());
    ContractInfo &conInfo = mRequestId_To_ContractRequestResponse[reqId].mReceivedContractInfos.back();
    FromContractDetailsToContractInfo(conInfo, contractDetails);

    // Save the contract id
    ContractInfo_To_ContractId[conInfo] = contractDetails.contract.conId;

    // Log
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, ("Got " + conInfo.ToShortString() + " from request: " + std::to_string(reqId)).c_str());
}

void IBKRClient::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
}

void IBKRClient::contractDetailsEnd(int reqId)
{
    // Mark the request as done and send the signal
    std::unique_lock<std::mutex> lk(mContractRequestMutex);
    int count = (int)mRequestId_To_ContractRequestResponse[reqId].mReceivedContractInfos.size();
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, ("Got " + std::to_string(count) + " total contracts from request: " + std::to_string(reqId)).c_str());
    mRequestId_To_ContractRequestResponse[reqId].mIsDone = true;
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
        logType = LogType::Debug;
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

std::string LOB_OperationToStr(int operation)
{
    // Operation codes: insert(0), update(1) or remove(2)
    std::string retStr;
    if (operation == 0)         retStr = "Insert";
    else if (operation == 1)    retStr = "Update";
    else /*(operation == 2)*/   retStr = "Remove";
    return retStr;
}

std::string LOB_SideToStr(int side)
{
    // Side codes: 0 for ask, 1 for bid
    std::string retStr;
    if (side == 0)         retStr = "Ask";
    else if (side == 1)    retStr = "Bid";
    return retStr;
}

void IBKRClient::updateMktDepth(TickerId id, int position, int operation, int side, double price, int size)
{
    std::string logMsg = std::string(
        (std::string)"UpdateMarketDepth. ReqId: " + std::to_string(id) +
        (std::string)", Position: " + std::to_string(position) +
        (std::string)", Operation: " + LOB_OperationToStr(operation) +
        (std::string)", Side: " + LOB_SideToStr(side) +
        (std::string)", Price: " + std::to_string(price) +
        (std::string)", Size: " + std::to_string(size));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    LimitOrderBook* lobPtr = mRequestId_To_LOB[id].get();
    const LimitOrderBook::Side::Entry* entry = lobPtr->PerformOperation(position, "UNKWN", operation, side, price, size);

    void* obj = mRequestId_To_ReceiveObject[id];
    if (mRequestId_To_ReceiveLOBOperationFunc[id])
    {
        mRequestId_To_ReceiveLOBOperationFunc[id](obj, id, position, entry->MMId, operation, side, price, size);
    }
    if (mRequestId_To_ReceiveLOBFunc[id])
    {
        mRequestId_To_ReceiveLOBFunc[id](obj, id, lobPtr->Depth, lobPtr->Ask.Entries.data(), lobPtr->Bid.Entries.data());
    }
}

void IBKRClient::updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation, int side, double price, int size, bool isSmartDepth)
{
    std::string logMsg = std::string(
        (std::string)"UpdateMarketDepth. ReqId: " + std::to_string(id) +
        (std::string)", Position: " + std::to_string(position) +
        (std::string)", Operation: " + LOB_OperationToStr(operation) +
        (std::string)", Side: " + LOB_SideToStr(side) +
        (std::string)", Price: " + std::to_string(price) +
        (std::string)", Size: " + std::to_string(size) +
        (std::string)", isSmartDepth: " + (isSmartDepth ? "True" : "False"));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    LimitOrderBook* lobPtr = mRequestId_To_LOB[id].get();
    const LimitOrderBook::Side::Entry* entry = lobPtr->PerformOperation(position, marketMaker, operation, side, price, size);

    void* obj = mRequestId_To_ReceiveObject[id];
    if (mRequestId_To_ReceiveLOBOperationFunc[id])
    {
        mRequestId_To_ReceiveLOBOperationFunc[id](obj, id, position, entry->MMId, operation, side, price, size);
    }
    if (mRequestId_To_ReceiveLOBFunc[id])
    {
        mRequestId_To_ReceiveLOBFunc[id](obj, id, lobPtr->Depth, lobPtr->Ask.Entries.data(), lobPtr->Bid.Entries.data());
    }
}

void IBKRClient::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch)
{
}

void IBKRClient::managedAccounts(const std::string& accountsList)
{
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, ("Account List: " + accountsList).c_str());
}

void IBKRClient::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
}

void IBKRClient::historicalData(TickerId reqId, const Bar& bar)
{
    std::string logMsg = std::string(
        (std::string)"HistoricalData. ReqId: " + std::to_string(reqId) +
        (std::string)", Time: " + bar.time +
        (std::string)", Open: " + std::to_string(bar.open) +
        (std::string)", High: " + std::to_string(bar.high) +
        (std::string)", Low: " + std::to_string(bar.low) +
        (std::string)", Close: " + std::to_string(bar.close) +
        (std::string)", Volume: " + std::to_string(bar.volume) +
        (std::string)", Count: " + std::to_string(bar.count) +
        (std::string)", WAP: " + std::to_string(bar.count));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    void* obj = mRequestId_To_ReceiveObject[reqId];
    if (mRequestId_To_ReceiveHistoricalDataFunc[reqId])
    {
        HistoricalBarEntry newBar;
        FromBarToHistoricalBarEntry(newBar, bar);
        mRequestId_To_ReceiveHistoricalDataFunc[reqId](obj, reqId, false, &newBar);
    }
}

void IBKRClient::historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr)
{
    std::string logMsg = std::string(
        (std::string)"HistoricalDataEnd. ReqId: " + std::to_string(reqId) +
        (std::string)", Start Time: " + startDateStr +
        (std::string)", End Time: " + endDateStr);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());


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
    // More info on types and what do they do:
    // http://interactivebrokers.github.io/tws-api/market_data_type.html
    MarketDataType type = (MarketDataType)marketDataType;
    std::string typeStr;
    switch (type)
    {
    case MarketDataType::REALTIME:
        typeStr = "REALTIME";
        break;
    case MarketDataType::FROZEN:
        typeStr = "FROZEN";
        break;
    case MarketDataType::DELAYED:
        typeStr = "DELAYED";
        break;
    case MarketDataType::DELAYED_FROZEN:
        typeStr = "DELAYED_FROZEN";
        break;
    default:
        typeStr = "UNKNOWN";
        break;
    }

    std::string logMsg = std::string(
        (std::string)"Market Data Type. Ticker Id: " + std::to_string(reqId) +
        (std::string)", Type: " + typeStr);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
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
    std::string logMsg = std::string(
        (std::string)"Tick Req Params. Ticker Id: " + std::to_string(tickerId) +
        (std::string)", Min Tick: " + std::to_string(minTick) +
        (std::string)", BBO Exchange: " + bboExchange +
        (std::string)", Snapshot Permissions: " + std::to_string(snapshotPermissions));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
    //m_bboExchange = bboExchange;
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
    std::string logMsg = std::string(
        (std::string)"HistoricalDataUpdate. ReqId: " + std::to_string(reqId) +
        (std::string)", Time: " + bar.time +
        (std::string)", Open: " + std::to_string(bar.open) +
        (std::string)", High: " + std::to_string(bar.high) +
        (std::string)", Low: " + std::to_string(bar.low) +
        (std::string)", Close: " + std::to_string(bar.close) +
        (std::string)", Volume: " + std::to_string(bar.volume) +
        (std::string)", Count: " + std::to_string(bar.count) +
        (std::string)", WAP: " + std::to_string(bar.count));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    void* obj = mRequestId_To_ReceiveObject[reqId];
    if (mRequestId_To_ReceiveHistoricalDataFunc[reqId])
    {
        HistoricalBarEntry newBar;
        FromBarToHistoricalBarEntry(newBar, bar);
        mRequestId_To_ReceiveHistoricalDataFunc[reqId](obj, reqId, true, &newBar);
    }
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
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: Historical" +
        (std::string)", NumberOfTicks: " + std::to_string(ticks.size()) +
        (std::string)", Done: " + (done ? "True" : "False"));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
}

void IBKRClient::historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done)
{
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: BidAskHistorical" +
        (std::string)", NumberOfTicks: " + std::to_string(ticks.size()) +
        (std::string)", Done: " + (done ? "True" : "False"));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
}

void IBKRClient::historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done)
{
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: LastHistorical" +
        (std::string)", NumberOfTicks: " + std::to_string(ticks.size()) +
        (std::string)", Done: " + (done ? "True" : "False"));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
}

void IBKRClient::tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions)
{
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: " + (tickType == 1 ? "Last" : "AllLast") +
        (std::string)", Time: " + FromUNIXTimeToString(time) +
        (std::string)", Price: " + std::to_string(price) +
        (std::string)", Size: " + std::to_string(size) +
        (std::string)", PastLimit: " + std::to_string(tickAttribLast.pastLimit) +
        (std::string)", Unreported: " + std::to_string(tickAttribLast.unreported) +
        (std::string)", Exchange: " + exchange +
        (std::string)", SpecialConditions: " + specialConditions);
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    void* obj = mRequestId_To_ReceiveObject[reqId];
    ReceiveTimeAndSalesType type = ReceiveTimeAndSalesType::Unknown;
    if (price <= mRequestIdDataType_To_PriceSize[reqId][ReceiveMarketDataType::Bid].first)
    {
        type = ReceiveTimeAndSalesType::Sell;
    }
    else if (price >= mRequestIdDataType_To_PriceSize[reqId][ReceiveMarketDataType::Ask].first)
    {
        type = ReceiveTimeAndSalesType::Buy;
    }
    mRequestId_To_ReceiveTimeAndSalesFunc[reqId](obj, reqId, time, type, price, size);
}

void IBKRClient::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttribBidAsk& tickAttribBidAsk)
{
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: BidAsk" +
        (std::string)", Time: " + FromUNIXTimeToString(time) +
        (std::string)", BidPrice: " + std::to_string(bidPrice) +
        (std::string)", AskPrice: " + std::to_string(askPrice) +
        (std::string)", BidSize: " + std::to_string(bidSize) +
        (std::string)", AskSize: " + std::to_string(askSize) +
        (std::string)", BidPastLow: " + std::to_string(tickAttribBidAsk.bidPastLow) +
        (std::string)", AskPastHigh: " + std::to_string(tickAttribBidAsk.askPastHigh));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());

    mRequestIdDataType_To_PriceSize[reqId][ReceiveMarketDataType::Bid] = { bidPrice , bidSize };
    mRequestIdDataType_To_PriceSize[reqId][ReceiveMarketDataType::Ask] = { askPrice , askSize };
}

void IBKRClient::tickByTickMidPoint(int reqId, time_t time, double midPoint)
{
    std::string logMsg = std::string(
        (std::string)"Tick-By-Tick. ReqId: " + std::to_string(reqId) +
        (std::string)", TickType: MidPoint" +
        (std::string)", Time: " + FromUNIXTimeToString(time) +
        (std::string)", MidPoint: " + std::to_string(midPoint));
    mLogFunctionPtr(mLogObjectPtr, LogType::Debug, logMsg.c_str());
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

std::string IBKRClient::FromUNIXTimeToString(time_t time)
{
    struct tm timeStruct;
    gmtime_s(&timeStruct, &time);
    std::string valueStr =
        std::to_string(timeStruct.tm_year + 1900) + "-" +
        std::to_string(timeStruct.tm_mon + 1) + "-" +
        std::to_string(timeStruct.tm_mday) + "_" +
        std::to_string(timeStruct.tm_hour) + ":" +
        std::to_string(timeStruct.tm_min) + ":" +
        std::to_string(timeStruct.tm_sec);

    return valueStr;
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

IBKRClient::LimitOrderBook::LimitOrderBook(int supportedDepth)
    : Depth(supportedDepth)
{
    Ask.Entries.resize(supportedDepth);
    Bid.Entries.resize(supportedDepth);
}

const IBKRClient::LimitOrderBook::Side::Entry* IBKRClient::LimitOrderBook::PerformOperation(int position, const std::string& marketMaker, int operation, int side, double price, int size)
{
    LimitOrderBook::Side* sidePtr = (side == 0 ? &Ask : &Bid);
    int MMId = MMName_To_Id[marketMaker];
    if (MMId == 0)
    {
        MMName_To_Id[marketMaker] = MMId = MMCount;
        MMId_To_Name[MMId] = marketMaker;
        MMCount += 1;
    }

    LimitOrderBook::Side::Entry* entry = &sidePtr->Entries[position];
    switch (operation)
    {
    case 0: // insert
    case 1: // update
        entry->Price = price;
        entry->Size = size;
        entry->MMId = MMId;
        break;

    case 2: // remove
        entry->Price = price;
        entry->Size = 0;
        entry->MMId = -1;
        break;
    }
    return entry;
}
