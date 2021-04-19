
#ifndef IGENERICCONNECTIONADAPTER_H
#define IGENERICCONNECTIONADAPTER_H

#define MAX_NAME_STRING_LENGTH 64
#define MAX_VERSION_STRING_LENGTH 32
#define MAX_DESCRIPTION_STRING_LENGTH 512
#define MAX_SYMBOL_NAME 16
#define MAX_EXCHANGE_NAME 16
#define MAX_CURRENCY_NAME 8
#define MAX_MARKET_MAKER_NAME 8

#include <string>
#include <cstring>
#include <vector>
#include <functional>

class IGenericConnectionAdapter;

//
// Library info
//
struct ConnectionAdapterLibraryInfo
{
	char Name[MAX_NAME_STRING_LENGTH];
	char Version[MAX_VERSION_STRING_LENGTH];
	char Description[MAX_DESCRIPTION_STRING_LENGTH];

	struct
	{
		bool PlaceLimitOrders : 1;
		bool PlaceMarketOrders : 1;
	} SupportedFeatures;

	struct
	{
		int Count;
	} Parameters;
};

struct ConnectionAdapterParameter
{
	enum class ValueType : char { String, Integer, Boolean, Real };
	union Value
	{
		char ValueStr[64];
		int ValueInt;
		bool ValueBool;
		double ValueReal;
	};

	char Name[64];
	ValueType Type;
	Value Default;
};
typedef ConnectionAdapterParameter ConnectionAdapterParameterInfo;

//
// Message logging
//
enum class LogType { Debug, Info, Warning, Error };
typedef void LogFunction(void*, LogType, const char*);

//
// Connection
//
enum class ConnectionStatus : char { Unknown, Disconnected, Connecting, Connected, Disconnecting };
enum class ResultStatus : char { Success, Failure, WaitTimeout };
struct ConnectResult;
typedef void ConnectCallbackFunction(ConnectResult);
struct ConnectInfo
{
	ConnectionAdapterParameter::Value* ParameterValues;
	void* CallbackObject;
	ConnectCallbackFunction *CallbackFunctionPtr;
};
struct ConnectResult
{
	void* CallbackObject;
	ResultStatus Status;
};

//
// Contracts
//
enum class SecurityType : char { Stock, Future, Option };
struct ContractInfo
{
	char Symbol[MAX_SYMBOL_NAME];
	char Exchange[MAX_EXCHANGE_NAME];
	char Currency[MAX_CURRENCY_NAME];
	SecurityType Type;
	union
	{
		struct
		{
			int StockData;
		} Stock;
		struct
		{
			char ExpiryDate[8];
		} Future;
		struct
		{
			int OptionData;
		} Option;
	};

	std::string ToShortString() const 
	{
		std::string retVal = std::string(Exchange) + ":" + std::string(Symbol) + "(" + std::string(Currency);
		switch (Type)
		{
		case SecurityType::Stock:
			retVal += ",STK";
			break;
		case SecurityType::Future:
			retVal += ",FUT," + std::string(Future.ExpiryDate, 8);
			break;
		case SecurityType::Option:
			retVal += ",OPT";
			break;
		}
		retVal += ")";
		return retVal;
	}

	bool operator==(const ContractInfo& otherC) const
	{
		return (strcmp(this->Symbol, otherC.Symbol) == 0 &&
			strcmp(this->Exchange, otherC.Exchange) == 0 &&
			strcmp(this->Currency, otherC.Currency) == 0);
	}
};
struct ContractQueryResult
{
	int ContractCount;
	int RequestId{ -1 };
	ResultStatus Status{ ResultStatus::Failure };
};

//
// Market Data
//
enum class ReceiveMarketDataType : char { Bid, Ask, Last, Unknown };
typedef void ReceivePriceSizeDataFunction(void*, int, ReceiveMarketDataType, double, int);
typedef void ReceiveVolumeDataFunction(void*, int, int);
enum class ReceivePriceDataType : char { High, Low, Open, Close, Unknown };
typedef void ReceivePriceDataFunction(void*, int, ReceivePriceDataType, double);
struct BaseMarketDataInfo
{
	const ContractInfo* ConInfoPtr;
	ReceivePriceSizeDataFunction* ReceivePriceSizeDataFunctionPtr;
	ReceiveVolumeDataFunction* ReceiveVolumeDataFunctionPtr;
	ReceivePriceDataFunction* ReceivePriceDataFunctionPtr;
	void* ReceiveBaseMarketDataObjectPtr;
};
enum class ReceiveTimeAndSalesType : char { Buy, Sell, Unknown };
typedef void ReceiveTimeAndSalesDataFunction(void*, int, time_t, ReceiveTimeAndSalesType, double, int);
struct TimeAndSalesDataInfo
{
	const ContractInfo* ConInfoPtr;
	ReceiveTimeAndSalesDataFunction* ReceiveTimeAndSalesDataFunctionPtr;
	void* ReceiveTimeAndSalesDataObjectPtr;
};
struct LimitOrderBookEntry
{
	double Price;
	int Size;
	int MMId; // market maker Id
};
typedef void ReceiveLimitOrderBookOperationDataFunc(void* obj, int requestId, int position, int MMId, int operation, int side, double price, int size);
typedef void ReceiveLimitOrderBookDataFunc(void* obj, int requestId, int depth, LimitOrderBookEntry* askArray, LimitOrderBookEntry* bidArray);
struct LimitOrderBookDataInfo
{
	const ContractInfo* ConInfoPtr;
	int Depth;
	ReceiveLimitOrderBookOperationDataFunc* LOBDataOperationFunctionPtr;
	ReceiveLimitOrderBookDataFunc* LOBDataFunctionPtr;
	void* LOBDataObjectPtr;
};
enum class DataRequestType : char { MarketData, TimeAndSales, LimitOrderBook };
struct DataRequestResult
{
	long RequestId;
	DataRequestType Type;
};

//
// Actions
//
enum class ActionType : char { Buy = 0, Sell = 1 };
inline std::string ActionTypeToString(const ActionType& at) {switch (at){case ActionType::Buy:return "BUY"; case ActionType::Sell:return "SELL"; default: return "";}}
struct LimitOrderInfo
{
	ActionType Action;
	double Price;
	double Quantity;
	ContractInfo *ConInfoPtr;

	std::string ToShortString() const { 
		return (ActionTypeToString(Action) + ":" +
			std::to_string((int)Quantity) + "-" + ConInfoPtr->Symbol + "@" +
			std::to_string(Price) + "(" + ConInfoPtr->Currency + ")");
}
};
typedef long OrderId;
struct PlaceOrderResult
{
	OrderId Id{ -1 };
	ResultStatus Status{ ResultStatus::Failure };
};

class IGenericConnectionAdapter
{
public:
	virtual void SetLogFunction(LogFunction* logFunctionPtr, void* logObjectPtr) = 0;
	virtual void Connect(const ConnectInfo& connectInfo) = 0;
	virtual ConnectionStatus GetConnectionStatus() = 0;
	virtual void Disconnect() = 0;
	virtual void GetContractCount(const ContractInfo& query, ContractQueryResult* result) = 0;
	virtual void GetContracts(const ContractQueryResult& requestResult, ContractInfo *resultArray) = 0;
	virtual void RequestMarketData(const BaseMarketDataInfo& dataInfo, DataRequestResult* result) = 0;
	virtual void RequestTimeAndSalesData(const TimeAndSalesDataInfo& dataInfo, DataRequestResult* result) = 0;
	virtual void RequestLimitOrderBookData(const LimitOrderBookDataInfo& dataInfo, DataRequestResult* result) = 0;
	virtual void GetMarketMakerName(const DataRequestResult& requestResult, int MMId, char* nameDest, int *nameSize) = 0;
	virtual void CancelMarketData(const DataRequestResult& requestResult) = 0;

	virtual void PlaceLimitOrder(const LimitOrderInfo& orderInfo, PlaceOrderResult* result) = 0;
};

//
// Factory function pointers declarations
//
#define ADD_QUOTES(x) #x
#define TO_STRING(x) ADD_QUOTES(x)
#define CREATE_ADAPTER_FUNC _create_adapter_function_implementation
#define DESTROY_ADAPTER_FUNC _destroy_adapter_function_implementation
#define GET_INFO_FUNC _get_info_function_implementation
#define GET_PARAM_INFO_FUNC _get_param_info_function_implementation
#define CREATE_ADAPTER_IMPLEMENTATION_NAME TO_STRING(CREATE_ADAPTER_FUNC)
#define DESTROY_ADAPTER_IMPLEMENTATION_NAME TO_STRING(DESTROY_ADAPTER_FUNC)
#define GET_INFO_IMPLEMENTATION_NAME TO_STRING(GET_INFO_FUNC)
#define GET_PARAM_INFO_IMPLEMENTATION_NAME TO_STRING(GET_PARAM_INFO_FUNC)
typedef void (*CreateAdapterImplementationPtr)(IGenericConnectionAdapter**);
typedef void (*DestroyAdapterImplementationPtr)(IGenericConnectionAdapter**);
typedef void (*GetInfoImplementationPtr)(ConnectionAdapterLibraryInfo*);
typedef void (*GetParameterInfoImplementationPtr)(ConnectionAdapterParameterInfo*);

#endif // IGENERICCONNECTIONADAPTER_H
