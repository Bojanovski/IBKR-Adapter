
#include <IBKRAdapter.h>

#include <string>
#include <iostream>

using namespace std;
using namespace ibkr;

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
	IBKRAdapter* impl;
	ibkr::CreateAdapterImplementation(&impl);
	impl->SetLogFunction(&logFunc, nullptr);
	bool res = impl->Connect();

	if (res)
	{
		cout << "Connection established" << endl;
		impl->StartListeningForMessages();

		ibkr::ContractInfo contractInfo;
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
				ibkr::StockContractQuery query = { inStr, "", "USD" };
				ibkr::ContractQueryResult result;
				impl->GetStockContracts(query, &result);
				contractInfo = result.ContractInfoArray[0];
				cout << "Selected contract: " << contractInfo.Exchange << ":" << contractInfo.Symbol << " (" << contractInfo.Currency << ")" << endl;
			}
				break;

			case 2:
			{
				ibkr::PlaceOrderInfo placeInfo = { ActionType::Buy, 900.0, (double)atoi(inStr.c_str()), contractInfo };
				PlaceOrderResult result;
				impl->PlaceLimitOrder(placeInfo, &result);
			}
				break;

			default:
				break;
			}

		}
	}

	ibkr::DestroyAdapterImplementation(&impl);
	return 0;
}
