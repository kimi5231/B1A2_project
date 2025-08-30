#include "pch.h"

int main()
{
	//소켓 프로그래밍을 위한 WinSock 라이브러리 초기화 
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// client의 접속을 감지할 listen socket 생성
	// AF_INET: IPv4
	// SOCK_STREAM: TCP
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == 0)
		return 0;

	SOCKADDR_IN serverAddr;
	// 주소/포트 정보를 담을 구조체 초기화
	::memset(&serverAddr, 0, sizeof(serverAddr));
	// Ipv4
	serverAddr.sin_family = AF_INET;
	// 아무 IP로 접근해도 수락
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	// 포트 번호 설정
	serverAddr.sin_port = ::htons(7777);

	// 소켓에 주소/포트 정보 설정
	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	// listen socket을 수신 대기 상태로 설정
	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int addrLen = sizeof(clientAddr);

		// client 접속 시 통신하기 위한 client socket 생성
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
			return 0;

		std::cout << "Connected" << std::endl;

		while (true)
		{
			char recvBuffer[100];
			// 수신
			int recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen <= 0)
				return 0;

			std::cout << "Recv Data: " << recvBuffer << std::endl;
			std::cout << "Recv Data Len: " << recvLen << std::endl;
		}
	}

	// 종료
	::closesocket(listenSocket);
	::WSACleanup();
}