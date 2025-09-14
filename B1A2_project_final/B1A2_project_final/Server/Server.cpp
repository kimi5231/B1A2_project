#include "pch.h"
#include "Room.h"

int main()
{
	Room room;

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

	std::vector<char> recvBuffer;
	std::array<uint32_t, 2> header{};

	while (true)
	{
		pollfds.clear();

		// clientSocket 관찰 대상 등록
		for (SOCKET client : room._clients)
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

					room._clients.push_back(clientSocket);

					std::cout << "Connected" << std::endl;
				}
				else // clientSocket
				{
					char temp[100];
					SOCKET clientSocket = pollfd.fd;
					// 수신
					int recvLen = ::recv(clientSocket, temp, sizeof(temp), 0);

					if (recvLen < 0)
					{
						// recv 실패 처리
					}
					else if (recvLen == 0)
					{
						closesocket(clientSocket);
						room._clients.erase(std::remove(room._clients.begin(), room._clients.end(), clientSocket), room._clients.end());
						std::cout << "DisConnected" << std::endl;
						break;
					}
					else
					{
						// 수신된 데이터 누적
						recvBuffer.insert(recvBuffer.end(), temp, temp + recvLen);

						// 헤더 추출
						if (recvLen > sizeof(header) && !header[0] && !header[1])
						{
							// 패킷 size
							std::memcpy(&header[0], recvBuffer.data(), sizeof(uint32_t));
							header[0] = ::ntohl(header[0]);
							recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + sizeof(uint32_t));

							// 패킷 ID
							std::memcpy(&header[1], recvBuffer.data(), sizeof(uint32_t));
							header[1] = ::ntohl(header[1]);
							recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + sizeof(uint32_t));
							
							std::cout << "pkt size: " << header[0] << std::endl;
							std::cout << "pkt ID: " << header[1] << std::endl;
						}
						else if (recvLen > header[0]) // 본문 추출
						{
							switch (header[1])
							{
							case TEST:
								{
									Protocol::TEST pkt;

									// Byte 배열(recvBuffer)을 Protobuf 객체로 변환
									if (pkt.ParseFromArray(recvBuffer.data(), header[0]))
									{
										std::cout << "Recv Data: " << pkt.test().num() << std::endl;
										recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + header[0]);
										header[0] = 0;
										header[1] = 0;
									}
									else
									{
										// 변환 실패 처리
									}
								}
								break;
							case EnterRoom:
								Protocol::EnterRoom pkt;

								// Byte 배열(recvBuffer)을 Protobuf 객체로 변환
								if (pkt.ParseFromArray(recvBuffer.data(), header[0]))
								{
									room.CreatePlayer();
									recvBuffer.erase(recvBuffer.begin(), recvBuffer.begin() + header[0]);
									header[0] = 0;
									header[1] = 0;
								}
								else
								{
									// 변환 실패 처리
								}
								break;
							}
						}
					}
				}
			}
		}
	}

	// 종료
	::closesocket(listenSocket);
	::WSACleanup();
}