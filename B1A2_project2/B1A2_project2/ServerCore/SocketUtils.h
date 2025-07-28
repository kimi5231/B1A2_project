#pragma once
#include "NetAddress.h"

class SocketUtils
{
public:
	// 비동기 통신을 위한 윈도우 내부 함수 포인터
	static LPFN_CONNECTEX ConnectEx;
	static LPFN_DISCONNECTEX DisconnectEx;
	static LPFN_ACCEPTEX AcceptEx;

public:
	static void Init();
	static void Clear();

	static bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);
	static SOCKET CreateSocket();

	// 소켓 옵션 설정 함수
	// 소켓 종료 시, 송신 데이터가 남아 있을 경우 대기 여부 지정
	static bool SetLinger(SOCKET socket, uint16 onoff, uint16 linger);
	// 서버 재시작 시 동일 포트 재사용 허용
	static bool SetReuseAddress(SOCKET socket, bool flag);
	// 수신 버퍼 크기 조절
	static bool SetRecvBufferSize(SOCKET socket, int32 size);
	// 송신 버퍼 크기 조절
	static bool SetSendBufferSize(SOCKET socket, int32 size);
	// Nagle 알고리즘 끄기(지연없이 즉시 송신)
	static bool SetTcpNoDelay(SOCKET socket, bool flag);
	// 해당 소켓이 어느 listen 소켓에서 수락되었는지 알려주기
	static bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket);

	// 소켓에 IP/포트 정보 연결
	static bool Bind(SOCKET socket, NetAddress netAddr);
	static bool Bind(SOCKET socket, SOCKADDR_IN netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);

	static bool Listen(SOCKET socket, int32 backlog = SOMAXCONN);
	static void Close(SOCKET& socket);
};

// 소켓 옵션 템플릿
template<typename T>
static inline bool SetSockOpt(SOCKET socket, int32 level, int32 optName, T optVal)
{
	// 소켓 옵션 설정
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
}