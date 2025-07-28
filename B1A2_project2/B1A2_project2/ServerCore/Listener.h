#pragma once
#include "IocpCore.h"
#include "NetAddress.h"

//class AcceptEvent;

class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

public:
	// session의 접속 요청을 받을 준비 시작
	bool StartAccept(ServerServiceRef service);
	void CloseSocket();

public:
	virtual HANDLE GetHandle() override;
	// CP 작업 처리
	virtual void Dispatch(struct IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

private:
	// 접속 이벤트 등록
	void RegisterAccept(IocpEvent* acceptEvent);
	// 접속 이벤트 완료 처리
	void ProcessAccept(IocpEvent* acceptEvent);

protected:
	SOCKET _socket = INVALID_SOCKET;
	std::vector<IocpEvent*> _acceptEvents;
	ServerServiceRef _service;
};