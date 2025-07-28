#pragma once
// Iocp 큐에 들어가는 관찰 대상들의 상위 클래스
class IocpObject : public std::enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(struct IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

// Iocp 큐(CP)를 담당하는 클래스
class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle() { return _iocpHandle; }

	// 소켓을 CP에 등록
	bool Register(IocpObjectRef iocpObject);
	// CP에서 작업 꺼내기
	bool Dispatch(uint32 timeoutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};