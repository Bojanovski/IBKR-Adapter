
#ifdef BUILD_TYPE_EXECUTABLE

#include <IGenericConnectionAdapter.h>

#include "IBKRClient.h"

#include <string>
#include <iostream>
#include <memory>
#include <atomic>

using namespace std;

void logFunc(void* obj, LogType type, const char *str)
{
	std::string typeStr = "";
	switch (type)
	{
	case LogType::Debug:
		typeStr += "Debug";
		break;
	case LogType::Info:
		typeStr += "Info";
		break;
	case LogType::Warning:
		typeStr += "Warning";
		break;
	case LogType::Error:
		typeStr += "Error";
		break;
	default:
		return;
	}
	cout << typeStr << ": " << str << endl;
}

void receiveMarketDataFunc(void* obj, int requestId, ReceiveMarketDataType type, double price, int size)
{
	std::string typeStr;
	switch (type)
	{
	case ReceiveMarketDataType::Bid:
		typeStr = "Bid";
		break;
	case ReceiveMarketDataType::Ask:
		typeStr = "Ask";
		break;
	case ReceiveMarketDataType::Last:
		typeStr = "Last";
		break;
	case ReceiveMarketDataType::Unknown:
		typeStr = "Unknown";
		break;
	default:
		break;
	}

	cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << typeStr << " - " << price << " : " << size << endl;
}

void receiveVolumeDataFunc(void* obj, int requestId, int size)
{
	cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << "Daily Volume: " << size << endl;
}

void receivePriceDataFunc(void* obj, int requestId, ReceivePriceDataType priceType, double price)
{
	std::string typeStr;
	switch (priceType)
	{
	case ReceivePriceDataType::High:
		typeStr = "High";
		break;
	case ReceivePriceDataType::Low:
		typeStr = "Low";
		break;
	case ReceivePriceDataType::Open:
		typeStr = "Open";
		break;
	case ReceivePriceDataType::Close:
		typeStr = "Close";
		break;
	default:
		break;
	}

	cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << typeStr << ": " << price << endl;
}

void receiveTimeAndSalesDataFunc(void* obj, int requestId, time_t time, ReceiveTimeAndSalesType type, double price, int size)
{
	std::string typeStr;
	switch (type)
	{
	case ReceiveTimeAndSalesType::Buy:
		typeStr = "Buy";
		break;
	case ReceiveTimeAndSalesType::Sell:
		typeStr = "Sell";
		break;
	case ReceiveTimeAndSalesType::Unknown:
		typeStr = "Unknown";
		break;
	default:
		break;
	}

	cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << typeStr << ": " << price << endl;
}

void connectCallback(ConnectResult result)
{
	auto continue_thread = static_cast<std::atomic<bool> *>(result.CallbackObject);
	*continue_thread = true;
}

int main()
{
	// Function pointers check
	CreateAdapterImplementationPtr createAdapterPtr = CREATE_ADAPTER_FUNC;
	DestroyAdapterImplementationPtr destroyAdapterPtr = DESTROY_ADAPTER_FUNC;
	GetInfoImplementationPtr getInfoPtr = GET_INFO_FUNC;
	GetParameterInfoImplementationPtr getParamInfoPtr = GET_PARAM_INFO_FUNC;

	// Display the info
	ConnectionAdapterLibraryInfo adapterInfo;
	getInfoPtr(&adapterInfo);
	cout << adapterInfo.Name << endl;
	cout << adapterInfo.Version << endl;
	cout << adapterInfo.Description << endl;
	cout << "----------------------------------" << endl;

	// Get the parameter info
	std::vector<ConnectionAdapterParameterInfo> parameters(adapterInfo.Parameters.Count);
	getParamInfoPtr(parameters.data());

	IGenericConnectionAdapter* impl;
	createAdapterPtr(&impl);
	impl->SetLogFunction(&logFunc, nullptr);
	std::atomic<bool>continue_thread = false;

	std::vector<ConnectionAdapterParameter::Value> parameterValues(adapterInfo.Parameters.Count);
	strcpy_s(parameterValues[0].ValueStr, sizeof(parameterValues[0].ValueStr), "127.0.0.1");
	parameterValues[1].ValueInt = 7497; // TWS
	//parameterValues[1].ValueInt = 4001; // GATEWAY
	ConnectInfo connInfo;
	connInfo.ParameterValues = parameterValues.data();
	connInfo.CallbackObject = &continue_thread;
	connInfo.CallbackFunctionPtr = connectCallback;
	impl->Connect(connInfo);

	// Wait for the callback
	while (!continue_thread);

	if (impl->GetConnectionStatus() == ConnectionStatus::Connected)
	{
		cout << "Connection established" << endl;
		ContractInfo contractInfo;
		DataRequestResult result;
		int inChoice;
		string inStr = "";
		while (true)
		{
			cout << endl << endl << "Instructions:" << endl;
			cout << "   1 <name> <type>	- get contract" << endl;
			cout << "   2 <quantity>	- buy" << endl;
			cout << "   3				- get data" << endl;
			cout << "   4				- get time and sales" << endl;
			cout << "   5				- cancel get data" << endl;
			cout << "   6				- exit" << endl;

			cin >> inChoice;
			bool breakLoop = true;
			switch (inChoice)
			{
			case 1:
			{
				breakLoop = false;
				cin >> inStr;
				int type;
				cin >> type;
				ContractInfo query;
				query.Type = (SecurityType)type;

				// Future specific stuff
				memcpy(query.Future.ExpiryDate, "20210621", 8);

				strcpy_s(query.Symbol, sizeof(inStr.data()), inStr.data());
				strcpy_s(query.Currency, sizeof("USD"), "USD");
				strcpy_s(query.Exchange, sizeof(""), "");
				ContractQueryResult result;
				impl->GetContractCount(query, &result);
				if (result.Status != ResultStatus::Success) continue;
				std::vector<ContractInfo> contracts(result.ContractCount);
				impl->GetContracts(result, contracts.data());
				contractInfo = contracts[0];
				cout << "Selected contract: " << contractInfo.ToShortString() << endl;
			}
			break;

			case 2:
			{
				breakLoop = false;
				cin >> inStr;
				LimitOrderInfo placeInfo = { ActionType::Buy, 900.0, (double)atoi(inStr.c_str()), &contractInfo };
				PlaceOrderResult result;
				impl->PlaceLimitOrder(placeInfo, &result);
				if (result.Status != ResultStatus::Success) continue;
				cout << "Order placed: " << placeInfo.ToShortString() << " id: " << result.Id << endl;
			}
			break;

			case 3:
			{
				breakLoop = false;
				BaseMarketDataInfo info = { &contractInfo, &receiveMarketDataFunc, &receiveVolumeDataFunc, &receivePriceDataFunc, nullptr };
				result = DataRequestResult();
				impl->RequestMarketData(info, &result);
			}
			break;

			case 4:
			{
				breakLoop = false;
				TimeAndSalesDataInfo info = { &contractInfo, &receiveTimeAndSalesDataFunc, nullptr };
				result = DataRequestResult();
				impl->RequestTimeAndSalesData(info, &result);
			}
			break;
			
			case 5:
			{
				breakLoop = false;
				impl->CancelMarketData(result);
			}
			break;

			default:
				break;
			}

			if (breakLoop)
			{
				break;
			}
		}
	}

	impl->Disconnect();
	destroyAdapterPtr(&impl);
	return 0;
}

#endif
