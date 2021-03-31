
#ifndef IGENERICCONNECTIONADAPTER_H
#define IGENERICCONNECTIONADAPTER_H

#define MAX_CALLBACK_OBJECTS_COUNT 8
#define MAX_NAME_STRING_LENGTH 64
#define MAX_VERSION_STRING_LENGTH 32
#define MAX_DESCRIPTION_STRING_LENGTH 512

#include <string>
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
	enum class ValueType { String, Integer, Boolean, Real };
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
enum class ConnectionStatus { Unknown, Disconnected, Connecting, Connected, Disconnecting };
enum class ResultStatus { Success, Failure, WaitTimeout };
struct ConnectResult;
typedef void ConnectCallbackFunction(ConnectResult);
struct ConnectInfo
{
	ConnectionAdapterParameter::Value* ParameterValues;
	void* CallbackObjects[MAX_CALLBACK_OBJECTS_COUNT];
	ConnectCallbackFunction *CallbackFunctionPtr;
};
struct ConnectResult
{
	void* CallbackObjects[MAX_CALLBACK_OBJECTS_COUNT];
	ResultStatus Status;
};

//
// Contracts
//
struct ContractInfo
{
	std::string Symbol;
	std::string Exchange;
	std::string Currency;

	std::string ToShortString() const { return (Exchange + ":" + Symbol + "(" + Currency + ")"); }

	bool operator==(const ContractInfo& otherC) const
	{
		return (this->Symbol == otherC.Symbol && this->Exchange == otherC.Exchange && this->Currency == otherC.Currency);
	}

	struct HashFunction {
		size_t operator()(const ContractInfo& c) const
		{
			size_t hash1 = std::hash<std::string>()(c.Symbol);
			size_t hash2 = std::hash<std::string>()(c.Exchange);
			size_t hash3 = std::hash<std::string>()(c.Currency);
			return hash1 ^ hash2 ^ hash3;
		}
	};
};
struct ContractQueryResult
{
	std::vector<ContractInfo> ContractInfoArray;
	int RequestId{ -1 };
	ResultStatus Status{ ResultStatus::Failure };
};

//
// Market Data
//
enum class ReceiveMarketDataType { Bid, Ask, Last, Unknown };
typedef void ReceiveMarketDataFunction(void*, int, ReceiveMarketDataType, double, int);
typedef void ReceiveVolumeDataFunction(void*, int, int);
enum class ReceivePriceDataType { High, Low, Open, Close, Unknown };
typedef void ReceivePriceDataFunction(void*, int, ReceivePriceDataType, double);
struct MarketDataInfo
{
	ContractInfo* ConInfoPtr;
	ReceiveMarketDataFunction* ReceiveMarketDataFunctionPtr;
	ReceiveVolumeDataFunction* ReceiveVolumeDataFunctionPtr;
	ReceivePriceDataFunction* ReceivePriceDataFunctionPtr;
	void* ReceiveMarketDataObjectPtr;
};
struct MarketDataRequestResult
{
	long RequestId;
};

//
// Actions
//
enum class ActionType { Buy = 0, Sell = 1 };
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

	virtual void GetStockContracts(const ContractInfo& query, ContractQueryResult* result) = 0;

	virtual void RequestMarketData(const MarketDataInfo& marketDataInfo, MarketDataRequestResult* result) = 0;
	virtual void CancelMarketData(const MarketDataRequestResult& requestResult) = 0;

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
