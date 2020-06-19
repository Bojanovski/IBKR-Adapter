
#ifndef IGENERICCONNECTIONADAPTER_H
#define IGENERICCONNECTIONADAPTER_H

#include <string>
#include <vector>
#include <functional>

class IGenericConnectionAdapter;

//
// Library info
//
struct ConnectionAdapterLibraryInfo
{
	char Name[64];
	char Version[64];
	char Description[512];

	struct
	{
		bool PlaceLimitOrders : 1;
		bool PlaceMarketOrders : 1;
	} SupportedFeatures;
};

//
// Message logging
//
enum class LogType { Info, Warning, Error };
typedef void LogFunction(void*, LogType, const char* msg);

//
// Connection
//
struct ConnectionInfo
{
	std::string IP;
	int Port;
	int ClientId;
};

//
// Contracts
//
typedef long ContractId;
struct ContractInfo
{
	ContractId Id{ -1 };
	std::string Symbol;
	std::string Exchange;
	std::string Currency;

	std::string ToShortString() const { return (Exchange + ":" + Symbol + "(" + Currency + ")"); }
};
enum class ResultStatus { Success, Failure, WaitTimeout };
struct ContractQueryResult
{
	std::vector<ContractInfo> ContractInfoArray;
	int RequestId{ -1 };
	ResultStatus Status{ ResultStatus::Failure };
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
struct StockContractQuery
{
	std::string Symbol;
	std::string Exchange;
	std::string Currency;
};

class IGenericConnectionAdapter
{
public:
	virtual void SetLogFunction(LogFunction* logFunctionPtr, void* logObjectPtr) = 0;
	virtual void Connect(const ConnectionInfo& connectionInfo, std::function<void()> callback) = 0;
	virtual bool IsConnected() = 0;
	virtual void Disconnect() = 0;

	virtual void GetStockContracts(const StockContractQuery& query, ContractQueryResult* result) = 0;

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
#define CREATE_ADAPTER_IMPLEMENTATION_NAME TO_STRING(CREATE_ADAPTER_FUNC)
#define DESTROY_ADAPTER_IMPLEMENTATION_NAME TO_STRING(DESTROY_ADAPTER_FUNC)
#define GET_INFO_IMPLEMENTATION_NAME TO_STRING(GET_INFO_FUNC)
typedef void (*CreateAdapterImplementationPtr)(IGenericConnectionAdapter**);
typedef void (*DestroyAdapterImplementationPtr)(IGenericConnectionAdapter**);
typedef void (*GetInfoImplementationPtr)(ConnectionAdapterLibraryInfo*);


#endif // IGENERICCONNECTIONADAPTER_H
