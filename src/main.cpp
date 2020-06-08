
#include <IBKRAdapter.h>

#include <iostream>

using namespace std;

void logFunc(void* obj, const char *str)
{
	cout << "log: " << str << endl;
}

int main()
{
	IBKRAdapter* impl;
	ibkr::CreateAdapterImplementation(&impl);
	impl->SetLogFunction(&logFunc, nullptr);
	bool res = impl->Connect();

	if (res)
	{
		cout << "Connection established yo!" << endl;
		impl->StartListeningForMessages();

		int in;
		cin >> in;
	}

	ibkr::DestroyAdapterImplementation(&impl);
	return 0;
}
