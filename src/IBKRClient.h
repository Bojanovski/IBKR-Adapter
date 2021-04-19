#pragma once

#include "ib_api_v9.76/EWrapper.h"
#include "ib_api_v9.76/EReaderOSSignal.h"
#include "ib_api_v9.76/EClientSocket.h"
#include "ib_api_v9.76/EReader.h"
#include "ib_api_v9.76/Order.h"

#include <IGenericConnectionAdapter.h>

#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <map>
#include <unordered_map>

#ifdef WIN32
#define LIBRARY_EXPORT __declspec(dllexport)
#else
#define LIBRARY_EXPORT
#endif

extern "C" { // Needs to expose these functions without c++ name mangling
	LIBRARY_EXPORT void CREATE_ADAPTER_FUNC(IGenericConnectionAdapter**);
	LIBRARY_EXPORT void DESTROY_ADAPTER_FUNC(IGenericConnectionAdapter**);
	LIBRARY_EXPORT void GET_INFO_FUNC(ConnectionAdapterLibraryInfo*);
	LIBRARY_EXPORT void GET_PARAM_INFO_FUNC(ConnectionAdapterParameterInfo*);
}

class IBKRClient : public IGenericConnectionAdapter, public EWrapper
{
public:
	IBKRClient(unsigned long signalWaitTimeout = 2000);
	virtual ~IBKRClient();

	// IGenericConnectionAdapter implementations
	virtual void SetLogFunction(LogFunction* logFunctionPtr, void* logObjectPtr) override;
	virtual void Connect(const ConnectInfo& connectInfo) override;
	virtual ConnectionStatus GetConnectionStatus() override;
	virtual void Disconnect() override;
	virtual void GetContractCount(const ContractInfo& query, ContractQueryResult* result) override;
	virtual void GetContracts(const ContractQueryResult& requestResult, ContractInfo* resultArray) override;
	virtual void RequestMarketData(const BaseMarketDataInfo& dataInfo, DataRequestResult* result) override;
	virtual void RequestTimeAndSalesData(const TimeAndSalesDataInfo& dataInfo, DataRequestResult* result) override;
	virtual void RequestLimitOrderBookData(const LimitOrderBookDataInfo& dataInfo, DataRequestResult* result) override;
	virtual void GetMarketMakerName(const DataRequestResult& requestResult, int MMId, char *nameDest, int *nameSize) override;
	virtual void CancelMarketData(const DataRequestResult& requestResult) override;
	virtual void PlaceLimitOrder(const LimitOrderInfo& orderInfo, PlaceOrderResult* result) override;

	// EWrapper implementations
	virtual void tickPrice(TickerId tickerId, TickType field, double price, const TickAttrib& attrib) override;
	virtual void tickSize(TickerId tickerId, TickType field, int size) override;
	virtual void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
		double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) override;
	virtual void tickGeneric(TickerId tickerId, TickType tickType, double value) override;
	virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value) override;
	virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
		double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) override;
	virtual void orderStatus(OrderId orderId, const std::string& status, double filled,
		double remaining, double avgFillPrice, int permId, int parentId,
		double lastFillPrice, int clientId, const std::string& whyHeld, double mktCapPrice) override;
	virtual void openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&) override;
	virtual void openOrderEnd() override;
	virtual void winError(const std::string& str, int lastError) override;
	virtual void connectionClosed() override;
	virtual void updateAccountValue(const std::string& key, const std::string& val,
		const std::string& currency, const std::string& accountName) override;
	virtual void updatePortfolio(const Contract& contract, double position,
		double marketPrice, double marketValue, double averageCost,
		double unrealizedPNL, double realizedPNL, const std::string& accountName) override;
	virtual void updateAccountTime(const std::string& timeStamp) override;
	virtual void accountDownloadEnd(const std::string& accountName) override;
	virtual void nextValidId(OrderId orderId) override;
	virtual void contractDetails(int reqId, const ContractDetails& contractDetails) override;
	virtual void bondContractDetails(int reqId, const ContractDetails& contractDetails) override;
	virtual void contractDetailsEnd(int reqId) override;
	virtual void execDetails(int reqId, const Contract& contract, const Execution& execution) override;
	virtual void execDetailsEnd(int reqId) override;
	virtual void error(int id, int errorCode, const std::string& errorString) override;
	virtual void updateMktDepth(TickerId id, int position, int operation, int side,
		double price, int size) override;
	virtual void updateMktDepthL2(TickerId id, int position, const std::string& marketMaker, int operation,
		int side, double price, int size, bool isSmartDepth) override;
	virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) override;
	virtual void managedAccounts(const std::string& accountsList) override;
	virtual void receiveFA(faDataType pFaDataType, const std::string& cxml) override;
	virtual void historicalData(TickerId reqId, const Bar& bar) override;
	virtual void historicalDataEnd(int reqId, const std::string& startDateStr, const std::string& endDateStr) override;
	virtual void scannerParameters(const std::string& xml) override;
	virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
		const std::string& distance, const std::string& benchmark, const std::string& projection,
		const std::string& legsStr) override;
	virtual void scannerDataEnd(int reqId) override;
	virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
		long volume, double wap, int count) override;
	virtual void currentTime(long time) override;
	virtual void fundamentalData(TickerId reqId, const std::string& data) override;
	virtual void deltaNeutralValidation(int reqId, const DeltaNeutralContract& deltaNeutralContract) override;
	virtual void tickSnapshotEnd(int reqId) override;
	virtual void marketDataType(TickerId reqId, int marketDataType) override;
	virtual void commissionReport(const CommissionReport& commissionReport) override;
	virtual void position(const std::string& account, const Contract& contract, double position, double avgCost) override;
	virtual void positionEnd() override;
	virtual void accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) override;
	virtual void accountSummaryEnd(int reqId) override;
	virtual void verifyMessageAPI(const std::string& apiData) override;
	virtual void verifyCompleted(bool isSuccessful, const std::string& errorText) override;
	virtual void displayGroupList(int reqId, const std::string& groups) override;
	virtual void displayGroupUpdated(int reqId, const std::string& contractInfo) override;
	virtual void verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange) override;
	virtual void verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText) override;
	virtual void connectAck() override;
	virtual void positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double avgCost) override;
	virtual void positionMultiEnd(int reqId) override;
	virtual void accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) override;
	virtual void accountUpdateMultiEnd(int reqId) override;
	virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
		const std::string& multiplier, const std::set<std::string>& expirations, const std::set<double>& strikes) override;
	virtual void securityDefinitionOptionalParameterEnd(int reqId) override;
	virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier>& tiers) override;
	virtual void familyCodes(const std::vector<FamilyCode>& familyCodes) override;
	virtual void symbolSamples(int reqId, const std::vector<ContractDescription>& contractDescriptions) override;
	virtual void mktDepthExchanges(const std::vector<DepthMktDataDescription>& depthMktDataDescriptions) override;
	virtual void tickNews(int tickerId, time_t timeStamp, const std::string& providerCode, const std::string& articleId, const std::string& headline, const std::string& extraData) override;
	virtual void smartComponents(int reqId, const SmartComponentsMap& theMap) override;
	virtual void tickReqParams(int tickerId, double minTick, const std::string& bboExchange, int snapshotPermissions) override;
	virtual void newsProviders(const std::vector<NewsProvider>& newsProviders) override;
	virtual void newsArticle(int requestId, int articleType, const std::string& articleText) override;
	virtual void historicalNews(int requestId, const std::string& time, const std::string& providerCode, const std::string& articleId, const std::string& headline) override;
	virtual void historicalNewsEnd(int requestId, bool hasMore) override;
	virtual void headTimestamp(int reqId, const std::string& headTimestamp) override;
	virtual void histogramData(int reqId, const HistogramDataVector& data) override;
	virtual void historicalDataUpdate(TickerId reqId, const Bar& bar) override;
	virtual void rerouteMktDataReq(int reqId, int conid, const std::string& exchange) override;
	virtual void rerouteMktDepthReq(int reqId, int conid, const std::string& exchange) override;
	virtual void marketRule(int marketRuleId, const std::vector<PriceIncrement>& priceIncrements) override;
	virtual void pnl(int reqId, double dailyPnL, double unrealizedPnL, double realizedPnL) override;
	virtual void pnlSingle(int reqId, int pos, double dailyPnL, double unrealizedPnL, double realizedPnL, double value) override;
	virtual void historicalTicks(int reqId, const std::vector<HistoricalTick>& ticks, bool done) override;
	virtual void historicalTicksBidAsk(int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done) override;
	virtual void historicalTicksLast(int reqId, const std::vector<HistoricalTickLast>& ticks, bool done) override;
	virtual void tickByTickAllLast(int reqId, int tickType, time_t time, double price, int size, const TickAttribLast& tickAttribLast, const std::string& exchange, const std::string& specialConditions) override;
	virtual void tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, int bidSize, int askSize, const TickAttribBidAsk& tickAttribBidAsk) override;
	virtual void tickByTickMidPoint(int reqId, time_t time, double midPoint) override;
	virtual void orderBound(long long orderId, int apiClientId, int apiOrderId) override;
	virtual void completedOrder(const Contract& contract, const Order& order, const OrderState& orderState) override;
	virtual void completedOrdersEnd() override;

private:
	// Converts UNIX time to a human-readable string
	std::string FromUNIXTimeToString(time_t time);

	// A message listening loop that runs in a separate thread
	void MessageListeningLoop();

	// (Re)starts the message listener
	void StartListeningForMessages();
	
	// Stops the listener
	void StopListeningForMessages();

	void FromContractInfoToContract(Contract& contractOut, const ContractInfo& contractInfoIn);
	void FromContractDetailsToContractInfo(ContractInfo& contractInfoOut, const ContractDetails& contractDetailsIn);

private:
	EReaderOSSignal mOSSignal;
	unsigned long mSignalWaitTimeout;

	std::mutex mConnectionMutex;
	std::atomic<bool> mIsTryingToConnect;
	std::thread mAsyncConnectionThread;
	static int mClientCount;
	std::unique_ptr<EClientSocket> mClientSocketPtr;
	bool mExtraAuth;
	std::unique_ptr<EReader> mReaderPtr;
	std::atomic<bool> mListenForMessages;
	std::thread mMessgeListeningThread;

	// Logging
	LogFunction *mLogFunctionPtr;
	void* mLogObjectPtr;

	// Order placement
	std::mutex mOrderIdMutex;
	std::condition_variable mOrderIdConditionVariable;
	OrderId mOrderId;

	// Requesting contract data
	std::mutex mContractRequestMutex;
	std::condition_variable mContractRequestConditionVariable;
	int mContractRequestId;
	struct ContractRequestResponse
	{
		void Reset();
		bool mIsDone{ false };
		std::vector<ContractInfo> mReceivedContractInfos;
	};
	std::map<int, ContractRequestResponse> mRequestId_To_ContractRequestResponse;
	struct ContractInfoHashFunction 
	{
		size_t operator()(const ContractInfo& c) const
		{
			std::string symbol = std::string(c.Symbol);
			std::string exchange = std::string(c.Exchange);
			std::string currency = std::string(c.Currency);
			size_t hash1 = std::hash<std::string>()(symbol);
			size_t hash2 = std::hash<std::string>()(exchange);
			size_t hash3 = std::hash<std::string>()(currency);
			return hash1 ^ hash2 ^ hash3;
		}
	};
	std::unordered_map<ContractInfo, long, ContractInfoHashFunction> ContractInfo_To_ContractId;

	// Limit Order Book
	struct LimitOrderBook
	{
		struct Side
		{
			typedef LimitOrderBookEntry Entry;
			std::vector<Entry> Entries;
		} Bid, Ask;

		LimitOrderBook(int supportedDepth);		
		const Side::Entry *PerformOperation(int position, const std::string& marketMaker, int operation, int side, double price, int size);

		std::unordered_map<int, std::string> MMId_To_Name;
		std::unordered_map<std::string, int> MMName_To_Id;
		int MMCount = 1;
		const int Depth;
	};

	//
	// Requesting market data
	//
	long mMarketDataRequestId;
	std::unordered_map<long, void*> mRequestId_To_ReceiveObject;

	// Base Market data
	std::unordered_map<long, ReceivePriceSizeDataFunction*> mRequestId_To_ReceivePriceSizeFunc;
	std::unordered_map<long, ReceiveVolumeDataFunction*> mRequestId_To_ReceiveVolumeFunc;
	std::unordered_map<long, ReceivePriceDataFunction*> mRequestId_To_ReceivePriceFunc;
	std::unordered_map<long, std::unordered_map<ReceiveMarketDataType, std::pair<double, int>>> mRequestIdDataType_To_PriceSize;
	std::unordered_map<long, int> mRequestId_To_Volume;
	std::unordered_map<long, std::unordered_map<ReceivePriceDataType, double>> mRequestIdPriceType_To_Price;

	// Time and Sales data
	std::unordered_map<long, ReceiveTimeAndSalesDataFunction*> mRequestId_To_ReceiveTimeAndSalesFunc;

	// LOB data
	std::unordered_map<long, std::unique_ptr<LimitOrderBook>> mRequestId_To_LOB;
	std::unordered_map<long, ReceiveLimitOrderBookOperationDataFunc*> mRequestId_To_ReceiveLOBOperationFunc;
	std::unordered_map<long, ReceiveLimitOrderBookDataFunc*> mRequestId_To_ReceiveLOBFunc;
};
