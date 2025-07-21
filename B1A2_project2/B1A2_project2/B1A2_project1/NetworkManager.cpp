#include "pch.h"
#include "NetworkManager.h"
#include "Service.h"
#include "ServerSession.h"

void NetworkManager::Init()
{
	SocketUtils::Init();

	_service = std::make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		std::make_shared<IocpCore>(),
		[=]() { return CreateSession(); },
		1);

	assert(_service->Start());
}

void NetworkManager::Update()
{
	_service->GetIocpCore()->Dispatch(0);
}

ServerSessionRef NetworkManager::CreateSession()
{
	return _session = std::make_shared<ServerSession>();
}

void NetworkManager::SendPacket(SendBufferRef sendBuffer)
{
	if (_session)
		_session->Send(sendBuffer);
}