#include "pch.h"
#include "Listener.h"
#include "IocpEvent.h"
#include "Session.h"
#include "Service.h"

Listener::~Listener()
{
	SocketUtils::Close(_socket);

	// 남은 접속 이벤트 삭제
	for (IocpEvent* acceptEvent : _acceptEvents)
	{
		delete acceptEvent;
	}
}

bool Listener::StartAccept(ServerServiceRef service)
{
	_service = service;
	if (_service == nullptr)
		return false;

	// 소켓 생성
	_socket = SocketUtils::CreateSocket();
	if (_socket == INVALID_SOCKET)
		return false;

	// 소켓을 CP에 등록
	if (_service->GetIocpCore()->Register(shared_from_this()) == false)
		return false;

	// 서버 재시작 시 동일 포트 재사용 허용
	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	// 소켓 종료 시, 송신 데이터가 남아 있어도 대기하지 않도록 설정
	if (SocketUtils::SetLinger(_socket, 0, 0) == false)
		return false;

	// 소켓에 IP/포트 정보 연결
	if (SocketUtils::Bind(_socket, _service->GetNetAddress()) == false)
		return false;

	// Client 연결 대기 시작
	if (SocketUtils::Listen(_socket) == false)
		return false;

	// session의 수만큼 접속 이벤트 생성 및 등록
	const int32 acceptCount = _service->GetMaxSessionCount();
	for (int32 i = 0; i < acceptCount; i++)
	{
		IocpEvent* acceptEvent = new IocpEvent(EventType::Accept);
		acceptEvent->owner = shared_from_this();
		_acceptEvents.push_back(acceptEvent);
		// 접속 이벤트 등록
		RegisterAccept(acceptEvent);
	}

	return true;
}

void Listener::CloseSocket()
{
	SocketUtils::Close(_socket);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Listener::Dispatch(IocpEvent* acceptEvent, int32 numOfBytes)
{
	assert(acceptEvent->type == EventType::Accept);
	// 접속 이벤트 완료 처리
	ProcessAccept(acceptEvent);
}

void Listener::RegisterAccept(IocpEvent* acceptEvent)
{
	// session 생성 후, 접속 이벤트와 연결
	SessionRef session = _service->CreateSession();
	acceptEvent->Init();
	acceptEvent->session = session;

	DWORD bytesReceived = 0;
	// Client와 연결 시도
	if (false == SocketUtils::AcceptEx(_socket, session->GetSocket(), session->_recvBuffer.WritePos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, OUT & bytesReceived, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 아직 연결중이라면 재시도
			RegisterAccept(acceptEvent);
		}
	}
}

void Listener::ProcessAccept(IocpEvent* acceptEvent)
{
	SessionRef session = acceptEvent->session;

	// 해당 session이 어느 listen socket에 접속되었는지 확인
	if (false == SocketUtils::SetUpdateAcceptSocket(session->GetSocket(), _socket))
	{
		// 접속한 listen socket이 없으면 접속 요청 재시도
		RegisterAccept(acceptEvent);
		return;
	}

	SOCKADDR_IN sockAddress;
	int32 sizeOfSockAddr = sizeof(sockAddress);
	// Client의 IP/포트 정보 추출
	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeOfSockAddr))
	{
		// 추출 실패 시 접속 요청 재시도
		RegisterAccept(acceptEvent);
		return;
	}

	std::cout << "Client Connected!" << std::endl;

	// 추출한 정보 저장
	session->SetNetAddress(NetAddress(sockAddress));
	// 연결 이벤트 처리
	session->ProcessConnect();
	// 다음 client 접속 이벤트 등록
	RegisterAccept(acceptEvent);
}