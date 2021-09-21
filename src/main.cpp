
#ifdef BUILD_TYPE_EXECUTABLE

#include <IGenericConnectionAdapter.h>

#include "IBKRClient.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <atomic>

using namespace std;

std::string GetCurrentDateStr()
{
	auto now = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(now);

	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

	struct tm timeStruct;
	gmtime_s(&timeStruct, &tt);
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << std::to_string(timeStruct.tm_year + 1900) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mon + 1) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mday);
	return ss.str();
}

std::string GetCurrentDateTimeStr()
{
	auto now = std::chrono::system_clock::now();
	time_t tt = std::chrono::system_clock::to_time_t(now);

	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

	struct tm timeStruct;
	gmtime_s(&timeStruct, &tt);
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << std::to_string(timeStruct.tm_year + 1900) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mon + 1) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mday) << "_";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_hour) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_min) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_sec);// +":" +
	//ss << std::setw(2) << std::setfill('0') << std::to_string(millis);
	return ss.str();
}

class Writer
{
public:
	Writer()
		: mMaxLine(100)
		, mCurrentLine(0)
		, mTotalLinesWritten(0)
		, mState(State::Ping)
	{
		mToWrite[(int)State::Ping].resize(mMaxLine);
		mToWrite[(int)State::Pong].resize(mMaxLine);

		SetContractName("UNKNOWN");
	}

	~Writer()
	{
		if (mFileWritingThread && mFileWritingThread->joinable())
		{
			mFileWritingThread->join();
		}

		// Just write whatever is left
		if (!mOutFile.is_open())
		{
			mOutFile.open(mFileName, std::ios_base::app);
		}
		for (int i = 0; i < mCurrentLine; ++i)
		{
			mOutFile << mToWrite[(int)mState][i] << endl;
			mToWrite[(int)mState][i].clear();
		}
		mOutFile.close();
		mTotalLinesWritten += mCurrentLine;
		cout << "Lines written: " << mCurrentLine << ", total so far: " << mTotalLinesWritten  << endl;
	}

	void SetContractName(const std::string &contractName)
	{
		mContractName = contractName;
		mFileName = mContractName + "_" + GetCurrentDateStr() + ".txt";
	}

	void Add(const std::string& str)
	{
		mMtx.lock();
		mToWrite[(int)mState][mCurrentLine] = str;
		++mCurrentLine;

		if (mCurrentLine >= mMaxLine)
		{
			State state = mState;
			int linesToWrite = mCurrentLine;
			mState = (State)(((int)mState + 1) % 2);
			mCurrentLine = 0;

			if (mFileWritingThread && mFileWritingThread->joinable()) mFileWritingThread->join();
			mFileWritingThread = std::make_unique<std::thread>([this, state, linesToWrite]()
				{
					std::stringstream ss;
					for (int i = 0; i < linesToWrite; ++i)
					{
						ss << mToWrite[(int)state][i] << endl;
						mToWrite[(int)state][i].clear();
					}
					if (!mOutFile.is_open())
					{
						mOutFile.open(mFileName, std::ios_base::app);
					}
					mOutFile << ss.str();
					mTotalLinesWritten += linesToWrite;
					cout << "Lines written: " << linesToWrite << ", total so far: " << mTotalLinesWritten << endl;
				});
		}

		mMtx.unlock();
	}

private:
	enum class State : char { Ping, Pong };
	std::mutex mMtx;
	State mState;
	int mCurrentLine;
	int mTotalLinesWritten;
	std::vector<std::string> mToWrite[2];
	const int mMaxLine;
	std::unique_ptr<std::thread> mFileWritingThread;
	std::string mContractName;
	std::string mFileName;
	std::ofstream mOutFile;
};

Writer gWriter;

void logFunc(void* obj, LogType type, const char *str)
{
	if (type == LogType::Debug) return;

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

	//cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << typeStr << " - " << price << " : " << size << endl;
}

void receiveVolumeDataFunc(void* obj, int requestId, int size)
{
	std::string timeStr = GetCurrentDateTimeStr();
	std::string str = "2," + // 2 for total daily volume
		timeStr + "," +
		std::to_string(size);
	gWriter.Add(str);

	//cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << "Daily Volume: " << size << endl;
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

	//cout << "+++++++++++++++++++++++ Request Id: " << requestId << " - " << typeStr << ": " << price << endl;
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

	struct tm timeStruct;
	gmtime_s(&timeStruct, &time);
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << std::to_string(timeStruct.tm_year + 1900) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mon + 1) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mday) << "_";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_hour) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_min) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_sec);// +":" +
	//ss << std::setw(2) << std::setfill('0') << std::to_string(millis);
	std::string timeStr = ss.str();

	std::string str = "0," + // 0 for time and sales
		timeStr + "," +
		std::to_string(price) + "," +
		std::to_string(size);
	gWriter.Add(str);

	//cout << "+++++++++++++++++++++++ Request Id: " << requestId << " : " << price << " : " << size << endl;
}

void receiveLimitOrderBookOperationDataFunc(void* obj, int requestId, int position, int MMId, int operation, int side, double price, int size)
{
	std::string timeStr = GetCurrentDateTimeStr();
	std::string str = "1," + // 1 for LOB
		timeStr + "," +
		std::to_string(position) + "," +
		std::to_string(operation) + "," +
		std::to_string(side) + "," +
		std::to_string(price) + "," +
		std::to_string(size);
	gWriter.Add(str);
}

void receiveLimitOrderBookDataFunc(void* obj, int requestId, int depth, LimitOrderBookEntry* askArray, LimitOrderBookEntry* bidArray)
{
	//cout << "-----------------------------------" << endl;
	for (int i = 0; i < depth; ++i)
	{
		//cout << bidArray[i].Price << "  " << bidArray[i].Size << "  |  " << askArray[i].Price << "  " << askArray[i].Size << endl;
	}
	//cout << "-----------------------------------" << endl;
}

void receiveHistoricalDataFunc(void* obj, int requestId, bool isUpdate, HistoricalBarEntry* entry)
{
	struct tm timeStruct;
	gmtime_s(&timeStruct, &entry->Time);
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << std::to_string(timeStruct.tm_year + 1900) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mon + 1) << "-";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_mday) << "_";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_hour) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_min) << ":";
	ss << std::setw(2) << std::setfill('0') << std::to_string(timeStruct.tm_sec);// +":" +
	//ss << std::setw(2) << std::setfill('0') << std::to_string(millis);
	std::string timeStr = ss.str();

	cout << "+++++++++++++++++++++++ Request Id: " << requestId << " : " <<
		timeStr << " : " << (isUpdate ? "updated" : "historic") << " : " << entry->Open << " : " << entry->High << " : " << entry->Low << " : " << entry->Close << " : " << entry->Volume << endl;
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
			cout << "   1 <name> <type>	- get contract (type: 0 - stock, 1 - future, 2 - option)" << endl;
			cout << "   2 <quantity>	- buy" << endl;
			cout << "   3				- get data" << endl;
			cout << "   4				- get time and sales" << endl;
			cout << "   5				- get limit order book" << endl;
			cout << "   6				- get historic data" << endl;
			cout << "   7				- cancel get data" << endl;
			cout << "   8				- exit" << endl;

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
				memcpy(query.ExpiryDate, "20211221", EXPIRY_DATE_SIZE);

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
				gWriter.SetContractName(contractInfo.ToShortString());
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
				impl->RequestBaseMarketData(info, &result);
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
				LimitOrderBookDataInfo info = { &contractInfo, 10, &receiveLimitOrderBookOperationDataFunc, &receiveLimitOrderBookDataFunc, nullptr };
				result = DataRequestResult();
				impl->RequestLimitOrderBookData(info, &result);
			}
			break;

			case 6:
			{
				breakLoop = false;
				HistoricalDataInfo info = { &contractInfo, &receiveHistoricalDataFunc, nullptr };
				result = DataRequestResult();
				impl->RequestHistoricalData(info, &result);
			}
			break;
			
			case 7:
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
