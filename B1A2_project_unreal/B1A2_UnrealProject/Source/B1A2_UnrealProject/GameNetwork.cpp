#include "GameNetwork.h"

GameNetwork::GameNetwork()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		//std::cout << "윈속 초기화 실패" << std::endl;
		return;
	}

	// listenSocket 생성
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == INVALID_SOCKET)
	{
		//std::cout << "listenSocket 생성 실패" << std::endl;
		return;
	}

	// connect
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(7777);
	if (connect(_clientSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		//std::cout << "bind 실패" << std::endl;
		return;
	}
}

GameNetwork::~GameNetwork()
{
	// clientSocket 종료
	closesocket(_clientSocket);

	// 윈속 종료
	WSACleanup();
}
