
#ifndef IGENERICCONNECTIONADAPTER_H
#define IGENERICCONNECTIONADAPTER_H

#include <string>
#include <vector>

class IGenericConnectionAdapter;

//
// Message logging
//
enum class LogType { Info, Warning, Error };
typedef void LogFunction(void*, LogType, const char* msg);

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
// Utilities and actions
//
struct SupportedFeatures
{
	bool PlaceLimitOrders : 1;
	bool PlaceMarketOrders : 1;
};
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
	virtual bool Connect() = 0;
	virtual bool IsConnected() = 0;
	virtual void Disconnect() = 0;

	virtual void GetSupportedFeatures(SupportedFeatures *supportedFeatures) = 0;
	virtual void StartListeningForMessages() = 0;
	virtual void StopListeningForMessages() = 0;

	virtual void GetStockContracts(const StockContractQuery& query, ContractQueryResult* result) = 0;

	virtual void PlaceLimitOrder(const LimitOrderInfo& orderInfo, PlaceOrderResult* result) = 0;
};

//
// Factory function pointers declarations
//
#define CREATE_ADAPTER_FUNC _create_adapter_implementation
#define DESTROY_ADAPTER_FUNC _destroy_adapter_implementation
#define ADD_QUOTES(x) #x
#define TO_STRING(x) ADD_QUOTES(x)
#define CREATE_ADAPTER_IMPLEMENTATION_NAME TO_STRING(CREATE_ADAPTER_FUNC)
#define DESTROY_ADAPTER_IMPLEMENTATION_NAME TO_STRING(DESTROY_ADAPTER_FUNC)
typedef void (*CreateAdapterImplementationPtr)(IGenericConnectionAdapter**);
typedef void (*DestroyAdapterImplementationPtr)(IGenericConnectionAdapter**);


#endif // IGENERICCONNECTIONADAPTER_H
