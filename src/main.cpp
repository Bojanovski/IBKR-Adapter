
#ifdef BUILD_TYPE_EXECUTABLE

#include <IGenericConnectionAdapter.h>

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

int main()
{
	IGenericConnectionAdapter* impl;
	CreateAdapterImplementation(&impl);
	impl->SetLogFunction(&logFunc, nullptr);
	bool res = impl->Connect();

	if (res)
	{
		cout << "Connection established" << endl;
		impl->StartListeningForMessages();

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

	DestroyAdapterImplementation(&impl);
	return 0;
}

#endif
