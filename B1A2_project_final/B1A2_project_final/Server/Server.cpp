#include "pch.h"

// Socket 클래스 추가? (Socket, RecvBuffer, SendBuffer 포함)

int main()
{
	//소켓 프로그래밍을 위한 WinSock 라이브러리 초기화 
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// client의 접속을 감지할 listenSocket을 비동기로 생성
	// AF_INET: IPv4
	// SOCK_STREAM: TCP
	SOCKET listenSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == 0)
		return 0;

	// listenSocket을 Non-Blocking Socket으로 설정
	u_long mode = 1;
	ioctlsocket(listenSocket, FIONBIO, &mode);

	SOCKADDR_IN serverAddr;
	// 주소/포트 정보를 담을 구조체 초기화
	::memset(&serverAddr, 0, sizeof(serverAddr));
	// IPv4
	serverAddr.sin_family = AF_INET;
	// 아무 IP로 접근해도 수락
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	// 포트 번호 설정
	serverAddr.sin_port = ::htons(7777);

	// 소켓에 주소/포트 정보 설정
	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	// listenSocket을 수신 대기 상태로 설정
	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	std::cout << "Server Start" << std::endl;

	int clientNum = 0;

	std::vector<WSAPOLLFD> pollfds;
	std::vector<SOCKET> clients;

	while (true)
	{
		pollfds.clear();

		// clientSocket 관찰 대상 등록
		for (SOCKET client : clients)
		{
			WSAPOLLFD pollfd;
			pollfd.events = POLLRDNORM | POLLWRNORM;
			pollfd.fd = client;
			pollfd.revents = 0;
			pollfds.push_back(pollfd);
		}

		// listenSocket 관찰 대상 등록
		WSAPOLLFD pollfd;
		pollfd.events = POLLRDNORM;
		pollfd.fd = listenSocket;
		pollfd.revents = 0;
		pollfds.push_back(pollfd);

		// 이벤트 발생 관찰
		::WSAPoll(pollfds.data(), pollfds.size(), 100);

		for (WSAPOLLFD pollfd : pollfds)
		{
			// 이벤트가 발생했을 경우
			if (pollfd.revents != 0)
			{
				// listenSocket
				if (pollfd.fd == listenSocket)
				{
					SOCKADDR_IN clientAddr;
					::memset(&clientAddr, 0, sizeof(clientAddr));
					int addrLen = sizeof(clientAddr);

					// client 접속 시 통신하기 위한 clientSocket 생성
					SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
					if (clientSocket == INVALID_SOCKET)
						return 0;

					// clientSocket을 Non-Blocking Socket으로 설정
					u_long mode = 1;
					ioctlsocket(clientSocket, FIONBIO, &mode);

					clients.push_back(clientSocket);

					std::cout << "Connected" << std::endl;
				}
				else // clientSocket
				{
					char recvBuffer[100];
					SOCKET clientSocket = pollfd.fd;
					// 수신
					int recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
					if (recvLen > 0)
					{
						Protocol::TEST msg;
						// Byte 배열(recvBuffer)을 Protobuf 객체로 변환
						if (msg.ParseFromArray(recvBuffer, recvLen))
						{
							std::cout << "Recv Data: " << msg.test().num() << std::endl;
							std::cout << "Recv Data Len: " << recvLen << std::endl;
						}
						else
						{
							// 변환 실패 처리
						}
					}
					else if (recvLen == 0)
					{
						closesocket(clientSocket);
						clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
						std::cout << "DisConnected" << std::endl;
						break;
					}
				}
			}
		}
	}

	// 종료
	::closesocket(listenSocket);
	::WSACleanup();
}