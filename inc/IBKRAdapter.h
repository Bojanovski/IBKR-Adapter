#pragma once

#include <string>
#include <vector>

class IBKRAdapter;
namespace ibkr
{
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
	};
	enum class ResultStatus { Success, Failure, WaitTimeout };
	struct ContractQueryResult
	{
		std::vector<ContractInfo> ContractInfoArray;
		int RequestId = -1;
		ResultStatus Status;
	};

	//
	// Utilities and actions
	//
	struct SupportedFeatures
	{
		bool PlaceLimitOrders : 1;
		bool PlaceMarketOrders : 1;
	};
	enum class ActionType { Buy, Sell };
	struct PlaceOrderInfo
	{
		ActionType Action;
		double Price;
		double Quantity;
		ContractInfo ConInfo;
	};
	typedef long OrderId;
	struct PlaceOrderResult
	{
		OrderId Id{ -1 };
		ResultStatus Status;
	};
	struct StockContractQuery
	{
		std::string Symbol;
		std::string Exchange;
		std::string Currency;
	};

	void CreateAdapterImplementation(IBKRAdapter** implementation);
	void DestroyAdapterImplementation(IBKRAdapter** implementation);
}

class IBKRAdapter
{
public:
	virtual void SetLogFunction(ibkr::LogFunction* logFunctionPtr, void* logObjectPtr) = 0;
	virtual bool Connect() = 0;
	virtual bool IsConnected() = 0;
	virtual void Disconnect() = 0;

	virtual void GetSupportedFeatures(ibkr::SupportedFeatures *supportedFeatures) = 0;
	virtual void StartListeningForMessages() = 0;
	virtual void StopListeningForMessages() = 0;

	virtual void GetStockContracts(const ibkr::StockContractQuery& query, ibkr::ContractQueryResult* result) = 0;

	virtual void PlaceLimitOrder(const ibkr::PlaceOrderInfo& placeOrderInfo, ibkr::PlaceOrderResult* result) = 0;
};
