#include "pch.h"
#include "Service.h"
#include "ClientPacketHandler.h"
#include "ThreadManager.h"
#include <chrono>

char sendData[] = "Hello World";

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		std::cout << "~ServerSession" << std::endl;
	}

	virtual void OnConnected() override
	{
		std::cout << "Connected To Server" << std::endl;
	}

	virtual void OnRecvPacket(BYTE* buffer, int32 len) override
	{
		ClientPacketHandler::HandlePacket(buffer, len);
	}

	virtual void OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		//cout << "Disconnected" << endl;
	}
};

int main()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));

	SocketUtils::Init();

	ClientServiceRef service = std::make_shared<ClientService>(
		NetAddress(L"61.255.49.141", 7777),
		std::make_shared<IocpCore>(),
		[]() { return std::make_shared<ServerSession>(); },
		5);

	assert(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	GThreadManager->Join();

	SocketUtils::Clear();
}