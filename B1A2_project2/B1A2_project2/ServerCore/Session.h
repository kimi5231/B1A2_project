#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"
#include "RecvBuffer.h"

class Service;

class Session : public IocpObject
{
	friend class Listener;
	friend class IocpCore;
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	Session();
	virtual ~Session();

public:
	void Send(SendBufferRef sendBuffer);
	bool Connect();
	void Disconnect(const WCHAR* cause);

public:
	std::shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(std::shared_ptr<Service> service) { _service = service; }
	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET GetSocket() { return _socket; }
	bool IsConnected() { return _connected; }
	SessionRef GetSessionRef() { return std::static_pointer_cast<Session>(shared_from_this()); }

private:
	virtual HANDLE GetHandle() override;
	// CP 작업 처리
	virtual void Dispatch(struct IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
	// CP에 이벤트 등록
	bool RegisterConnect();
	bool RegisterDisconnect();
	void RegisterRecv();
	void RegisterSend();

	// 이벤트 처리
	void ProcessConnect();
	void ProcessDisconnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	// 오류 알림
	void HandleError(int32 errorCode);

protected:
	virtual void OnConnected() {}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) {}
	virtual void OnDisconnected() {}

private:
	std::weak_ptr<Service> _service;
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress{};
	std::atomic<bool> _connected = false;

private:
	USE_LOCK;

	// 수신
	RecvBuffer _recvBuffer;

	// 송신
	std::queue<SendBufferRef> _sendQueue;
	std::atomic<bool> _sendRegistered = false;


private:
	IocpEvent _connectEvent{ EventType::Connect };
	IocpEvent _disconnectEvent{ EventType::Disconnect };
	IocpEvent _recvEvent{ EventType::Recv };
	IocpEvent _sendEvent{ EventType::Send };
};

//-----------------------------------------------------------------

struct PacketHeader
{
	uint16 size;
	uint16 id; // Protocol ID
};

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	PacketSessionRef GetPacketSessionRef() { return std::static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) abstract;
};