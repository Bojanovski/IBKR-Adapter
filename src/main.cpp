
#ifdef BUILD_TYPE_EXECUTABLE

#include <IGenericConnectionAdapter.h>
#include "IBKRClient.h"

#include <string>
#include <iostream>

using namespace std;

void logFunc(void* obj, LogType type, const char *str)
{
	std::string typeStr = "";
	switch (type)
	{
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
	parameterValues[1].ValueInt = 7497;
	ConnectInfo connInfo;
	connInfo.ParameterValues = parameterValues.data();
	connInfo.CallbackObject = &continue_thread;
	connInfo.CallbackFunctionPtr = connectCallback;
	impl->Connect(connInfo);

	// Wait for the callback
	while (!continue_thread);

	if (impl->IsConnected())
	{
		cout << "Connection established" << endl;
		ContractInfo contractInfo;
		int inChoice;
		string inStr = "";
		while (true)
		{
			cout << endl << endl << "Instructions:" << endl;
			cout << "   1 <name>     - get contract" << endl;
			cout << "   2 <quantity> - buy" << endl;
			cout << "   3            - exit" << endl;

			cin >> inChoice;
			if (inChoice == 3) break;
			cin >> inStr;

			switch (inChoice)
			{
			case 1:
			{
				StockContractQuery query = { inStr, "", "USD" };
				ContractQueryResult result;
				impl->GetStockContracts(query, &result);
				if (result.Status != ResultStatus::Success) continue;
				contractInfo = result.ContractInfoArray[0];
				cout << "Selected contract: " << contractInfo.ToShortString() << endl;
			}
				break;

			case 2:
			{
				LimitOrderInfo placeInfo = { ActionType::Buy, 900.0, (double)atoi(inStr.c_str()), &contractInfo };
				PlaceOrderResult result;
				impl->PlaceLimitOrder(placeInfo, &result);
				if (result.Status != ResultStatus::Success) continue;
				cout << "Order placed: " << placeInfo.ToShortString() << " id: " << result.Id << endl;
			}
				break;

			default:
				break;
			}

		}
	}

	destroyAdapterPtr(&impl);
	return 0;
}

#endif
