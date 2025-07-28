#include "pch.h"
#include "Session.h"
#include "Service.h"

Session::Session() : _recvBuffer(BUFFER_SIZE)
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}

void Session::Send(SendBufferRef sendBuffer)
{
	bool registerSend = false;

	{
		WRITE_LOCK;
		_sendQueue.push(sendBuffer);
		// 송신중인지 확인
		registerSend = _sendRegistered.exchange(true) == false;
	}

	// CP에 송신 이벤트 등록
	if (registerSend)
		RegisterSend();
}

bool Session::Connect()
{
	// CP에 연결 이벤트 등록
	return RegisterConnect();
}

void Session::Disconnect(const WCHAR* cause)
{
	// 연결이 끊어졌는지 확인, 이미 끊어졌다면 리턴
	if (_connected.exchange(false) == false)
		return;

	// 방금 끊어졌다면, 연결 끊김 과정 진행
	std::wcout << "Disconnect : " << cause << std::endl;

	OnDisconnected();
	// 연결이 끊어졌으므로, Session 삭제
	GetService()->ReleaseSession(GetSessionRef());

	// CP에 연결 해제 이벤트 등록
	RegisterDisconnect();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	// 이벤트 타입에 따라 작업 처리
	switch (iocpEvent->type)
	{
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Disconnect:
		ProcessDisconnect();
		break;
	case EventType::Recv:
		ProcessRecv(numOfBytes);
		break;
	case EventType::Send:
		ProcessSend(numOfBytes);
		break;
	default:
		break;
	}
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	if (SocketUtils::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtils::BindAnyAddress(_socket, 0) == false)
		return false;

	_connectEvent.Init();
	// 연결 이벤트와 session 연결
	_connectEvent.owner = shared_from_this();

	DWORD numOfBytes = 0;
	SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSockAddr();
	// Server와 연결 시도
	if (false == SocketUtils::ConnectEx(_socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, &_connectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 연결 실패
			_connectEvent.owner = nullptr;
			return false;
		}
	}

	return true;
}

bool Session::RegisterDisconnect()
{
	_disconnectEvent.Init();
	// 수신 이벤트와 session 연결
	_disconnectEvent.owner = shared_from_this();

	// 연결 해제 시도
	if (false == SocketUtils::DisconnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 연결 해제 실패
			_disconnectEvent.owner = nullptr;
			return false;
		}
	}

	return true;
}

void Session::RegisterRecv()
{
	if (IsConnected() == false)
		return;

	_recvEvent.Init();
	// 수신 이벤트와 session 연결
	_recvEvent.owner = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	wsaBuf.len = _recvBuffer.FreeSize();

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	// 수신 시도
	if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 수신 실패, 오류 알림
			HandleError(errorCode);
			_recvEvent.owner = nullptr;
		}
	}
}

void Session::RegisterSend()
{
	if (IsConnected() == false)
		return;

	_sendEvent.Init();
	// 송신 이벤트와 session 연결
	_sendEvent.owner = shared_from_this();

	// 보낼 데이터를 sendEvent에 등록
	{
		WRITE_LOCK;

		int32 writeSize = 0;
		while (_sendQueue.empty() == false)
		{
			SendBufferRef sendBuffer = _sendQueue.front();

			writeSize += sendBuffer->WriteSize();

			_sendQueue.pop();
			_sendEvent.sendBuffers.push_back(sendBuffer);
		}
	}

	// Scatter-Gather
	// 흩어져 있는 데이터들을 모아서 한 방에 보냄
	std::vector<WSABUF> wsaBufs;
	wsaBufs.reserve(_sendEvent.sendBuffers.size());
	for (SendBufferRef sendBuffer : _sendEvent.sendBuffers)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		wsaBuf.len = static_cast<LONG>(sendBuffer->WriteSize());
		wsaBufs.push_back(wsaBuf);
	}

	DWORD numOfBytes = 0;
	// 송신 시도
	if (SOCKET_ERROR == ::WSASend(_socket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT & numOfBytes, 0, &_sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// 송신 실패, 오류 알림
			HandleError(errorCode);
			_sendEvent.owner = nullptr;
			_sendEvent.sendBuffers.clear();
			_sendRegistered.store(false);
		}
	}
}

void Session::ProcessConnect()
{
	_connectEvent.owner = nullptr;

	_connected.store(true);

	// Session 등록
	GetService()->AddSession(GetSessionRef());

	OnConnected();

	// 수신 이벤트 등록
	RegisterRecv();
}

void Session::ProcessDisconnect()
{
	_disconnectEvent.owner = nullptr;
}

void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.owner = nullptr;

	// 데이터의 크기가 0이면 연결 해제
	if (numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	// 수신 버퍼에 기록중 오류 발생 시, 연결 해제
	if (_recvBuffer.OnWrite(numOfBytes) == false)
	{
		Disconnect(L"OnWrite Overflow");
		return;
	}

	// 수신 버퍼의 내용을 읽는중 오류 발생 시, 연결 해제
	int32 dataSize = _recvBuffer.DataSize();
	int32 processLen = OnRecv(_recvBuffer.ReadPos(), dataSize);
	if (processLen < 0 || dataSize < processLen || _recvBuffer.OnRead(processLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	// 커서 정리
	_recvBuffer.Clean();

	// 수신 이벤트 등록
	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
	_sendEvent.owner = nullptr;
	_sendEvent.sendBuffers.clear();

	// 데이터의 크기가 0이면 연결 해제
	if (numOfBytes == 0)
	{
		Disconnect(L"Send 0");
		return;
	}

	OnSend(numOfBytes);

	bool registerSend = false;

	// 보낼 데이터가 있는지 확인
	{
		WRITE_LOCK;
		if (_sendQueue.empty())
			_sendRegistered.store(false);
		else
			registerSend = true;
	}

	// 송신 이벤트 등록
	if (registerSend)
		RegisterSend();
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		Disconnect(L"HandleError");
		break;
	default:
		std::cout << "Handle Error : " << errorCode << std::endl;
		break;
	}
}

//-----------------------------------------------------------------

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	// 처리한 총 길이
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;
		// 데이터의 크기가 헤더의 크기보다 작으면 종료
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));
		// 데이터의 크기가 헤더에 기록된 패킷의 크기보다 작으면 종료
		if (dataSize < header.size)
			break;

		// 패킷 조립 성공
		OnRecvPacket(&buffer[processLen], header.size);

		processLen += header.size;
	}

	return processLen;
}