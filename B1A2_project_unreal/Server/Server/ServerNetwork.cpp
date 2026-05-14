#include "pch.h"
#include "ServerNetwork.h"
#include "Session.h"
#include "ExpOver.h"
#include "Room.h"

ServerNetwork::ServerNetwork()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "윈속 초기화 실패" << std::endl;
		return;
	}

	// listenSocket 생성
	_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_listenSocket == INVALID_SOCKET)
	{
		std::cout << "listenSocket 생성 실패" << std::endl;
		return;
	}

	// bind
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	if (bind(_listenSocket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		std::cout << "bind 실패" << std::endl;
		return;
	}

	// listen
	if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "listen 실패" << std::endl;
		return;
	}

	// iocp port 생성
	_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// listenSocket 등록
	CreateIoCompletionPort((HANDLE)_listenSocket, _iocp, -1, 0);
}

ServerNetwork::~ServerNetwork()
{
	// listenSocket 종료
	closesocket(_listenSocket);

	// 윈속 종료
	WSACleanup();
}

void ServerNetwork::Update()
{
	DWORD numBytes;
	ULONG_PTR key;
	LPOVERLAPPED over;
	GetQueuedCompletionStatus(_iocp, &numBytes, &key, &over, INFINITE);
	
	// 접속자가 많을 시 로그인 실패 패킷을 보내야 함으로, clientSocket 생성
	SOCKET clientSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	ExpOver acceptOver(IOType::Accept);
	AcceptEx(_listenSocket, clientSocket, &acceptOver._buffer, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, NULL, &acceptOver._over);

	if (over == nullptr)
	{
		if (key == -1)
			exit(-1);
		
		std::cout << "client[" << key << "] 접속 종료\n";
		_clients[key]._isConnected = false;
		closesocket(_clients[key]._clientSocket);
		_clients[key]._clientSocket = INVALID_SOCKET;

		// 같은 방에 있는 Client들에게 접속 종료 알림
		for (auto& player : _clients[key]._room->GetPlayers())
			if (player->GetClient()._isConnected)
				player->GetClient().send_remove_player(key);

		return;
	}

	ExpOver* expOver = reinterpret_cast<ExpOver*>(over);
	switch (expOver->_ioType)
	{
	case IOType::Accept:
		std::cout << "Client 접속" << std::endl;

		int clientIndex = -1;
		for (int i = 0; i < MAX_PLAYER; ++i)
		{
			if (!_clients[i]._isConnected)
			{
				clientIndex = i;
				break;
			}
		}
			
		if (clientIndex == -1)
		{
			// 로그인 실패 패킷 전송
			
		}
		else
		{
			// clientSocket 등록
			CreateIoCompletionPort((HANDLE)clientSocket, _iocp, clientIndex, 0);
			_clients[clientIndex]._clientSocket = clientSocket;
			_clients[clientIndex]._id = clientIndex;
			_clients[clientIndex]._isConnected = true;
			_clients[clientIndex]._prevRecv = 0;

			// 새로 접속한 
			for (auto& other : clients) {
				if (false == other.m_is_connected) continue;
				if (other.m_id == player_index) continue;
				//other.send_add_player(player_index);
				clients[player_index].send_add_player(other.m_id);
			}

			clients[player_index].do_recv();
		}
		client_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
		AcceptEx(server, client_socket, &accept_over.m_buff, 0,
			sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
			NULL, &accept_over.m_over);
		break;
	case IOType::Recv:
	{
		int player_index = static_cast<int>(key);
		// Player 접속 종료
		if (numBytes == 0)
		{
			std::cout << "client[" << key << "] Disconnected.\n";
			clients[key].m_is_connected = false;
			for (auto& cl : clients)
				if (true == cl.m_is_connected)
					cl.send_remove_player(key);
			closesocket(clients[key].m_client);
			clients[key].m_client = INVALID_SOCKET;
			continue;
		}
		SESSION& cl = clients[player_index];
		unsigned char* p = reinterpret_cast<unsigned char*>(exp_over->m_buff);
		int data_size = numBytes + cl.m_prev_recv;
		while (data_size > 0) {
			int packet_size = p[0];
			if (packet_size > data_size) break;
			cl.process_packet(p);
			p += packet_size;
			data_size -= packet_size;
		}
		if (data_size > 0) {
			memmove(cl.m_recv_over.m_buff, p, data_size);
			cl.m_prev_recv = data_size;
		}
		cl.do_recv();
	}
	break;
	case IOType::Send:
		ExpOver* o = reinterpret_cast<ExpOver*>(over);
		delete o;
		break;		
	default:
		std::cout << "Unknown IO type.\n";
		exit(-1);
		break;
	}
}