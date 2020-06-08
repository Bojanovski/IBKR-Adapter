#pragma once

class IBKRAdapter;
namespace ibkr
{
	typedef void LogFunction(void*, const char* msg);

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

	virtual void StartListeningForMessages() = 0;
	virtual void StopListeningForMessages() = 0;

	virtual void PlaceLimitOrder() = 0;
};
