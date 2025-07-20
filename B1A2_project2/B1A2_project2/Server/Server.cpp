#include "pch.h"
#include <thread>
#include <chrono>
#include "ThreadManager.h"
#include "SocketUtils.h"
#include "Listener.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "DataManager.h"

int main()
{
	// 상대 경로 알아오기
	std::filesystem::path resourcePath = std::filesystem::current_path().relative_path();
	
	// DataBase 파일 경로 설정
	resourcePath = std::filesystem::current_path().parent_path().parent_path().parent_path() / "Data";
	GET_SINGLE(DataManager)->Init(resourcePath);

	SocketUtils::Init();

	ServerServiceRef service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		[]() { return make_shared<GameSession>(); },
		100);

	assert(service->Start());

	while (true)
	{
		service->GetIocpCore()->Dispatch();
	}

	GThreadManager->Join();

	// 윈속 종료
	SocketUtils::Clear();
}