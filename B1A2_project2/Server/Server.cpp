#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include "ThreadManager.h"
#include "SocketUtils.h"
#include "Listener.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "DataManager.h"

#include <chrono>

int main()
{
	// 상대 경로 알아오기
	std::filesystem::path resourcePath = std::filesystem::current_path().relative_path();
	
	// DataBase 파일 경로 설정
	resourcePath = std::filesystem::current_path().parent_path().parent_path().parent_path() / "Data";
	GET_SINGLE(DataManager)->Init(resourcePath);

	SocketUtils::Init();

	ServerServiceRef service = make_shared<ServerService>(
		NetAddress(L"61.255.49.141", 7777),
		make_shared<IocpCore>(),
		[]() { return make_shared<GameSession>(); }, // TODO : SessionManager 등
		100);

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

	char sendData[1000] = "Hello World";

	while (true)
	{
		vector<BuffData> buffs{ BuffData {100, 1.5f}, BuffData{200, 2.3f}, BuffData {300, 0.7f } };
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_TEST(1001, 100, 10, buffs);
		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}


	GThreadManager->Join();

	// 윈속 종료
	SocketUtils::Clear();
}