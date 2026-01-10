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

void GameNetwork::Update()
{
	// socket set 초기화
	FD_ZERO(&_readSet);
	FD_ZERO(&_writeSet);

	// readSet, writeSet에 clientSocket 등록
	FD_SET(_clientSocket, &_readSet);
	FD_SET(_clientSocket, &_writeSet);

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
	{
		//std::cout << "select 실패" << std::endl;
		return;
	}

	if (FD_ISSET(_clientSocket, &_readSet))
	{
		ProcessRecv();
	}

	// send가 가능할 때마다 true
	if (FD_ISSET(_clientSocket, &_writeSet))
	{
		for (auto& sendEvent : _sendEvents)
		{
			std::visit([this](const auto& event) {
				ProcessSend(event->packetID, event->packetData);
				event->isComplete = true;
			}, sendEvent);
		}

		_sendEvents.erase(std::remove_if(_sendEvents.begin(), _sendEvents.end(),
			[](const auto& sendEvent) {
				return std::visit([](const auto& event) {return event->isComplete;}, sendEvent);
			}), _sendEvents.end());
	}

	// 처리된 이벤트 삭제
	_recvEvents.erase(std::remove_if(_recvEvents.begin(), _recvEvents.end(),
		[](const auto& recvEvent) {
			return std::visit([](const auto& event) {return event->isComplete;}, recvEvent);
		}), _recvEvents.end());
}

void GameNetwork::ProcessRecv()
{
	// PacketSize 수신(고정 길이)
	int packetSize{};
	if (recv(_clientSocket, (char*)&packetSize, sizeof(int), MSG_WAITALL) <= 0)
	{
		//ProcessDisconnect(client);
		return;
	}

	// Packet 수신(가변 데이터)
	std::vector<char> packet(512);
	if (recv(_clientSocket, packet.data(), packetSize, MSG_WAITALL) <= 0)
	{
		//ProcessDisconnect(client);
		return;
	}

	// Header 추출
	Header header;
	memcpy(&header, packet.data(), sizeof(Header));

	// Data 추출
	switch (header.id)
	{
	case S_AddObject:
	{
		NetworkEventRef<S_AddObject_Packet> event = std::make_shared<NetworkEvent<S_AddObject_Packet>>();
		event->packetID = header.id;
		memcpy(&event->packetData, packet.data() + sizeof(Header), sizeof(S_AddObject_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateObjectState:
	{
		NetworkEventRef<S_UpdateObjectState_Packet> event = std::make_shared<NetworkEvent<S_UpdateObjectState_Packet>>();
		event->packetID = header.id;
		memcpy(&event->packetData, packet.data() + sizeof(Header), sizeof(S_UpdateObjectState_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_Move:
	{
		NetworkEventRef<S_Move_Packet> event = std::make_shared<NetworkEvent<S_Move_Packet>>();
		event->packetID = header.id;
		memcpy(&event->packetData, packet.data() + sizeof(Header), sizeof(S_Move_Packet));
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::SendUpdateObjectStatePacket(int id, ObjectType type, MoveState state)
{
	// Packet Data 생성
	C_UpdateObjectState_Packet packetData{ id, type, state };

	// SendEvent 생성
	NetworkEventRef<C_UpdateObjectState_Packet> event = std::make_shared<NetworkEvent<C_UpdateObjectState_Packet>>();
	event->packetID = C_UpdateObjectState;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(int id, Vector pos, Rotation rotation, MoveState state)
{
	// Packet Data 생성
	C_Move_Packet packetData{ id, pos, rotation, state };

	// SendEvent 생성
	NetworkEventRef<C_Move_Packet> event = std::make_shared<NetworkEvent<C_Move_Packet>>();
	event->packetID = C_Move;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}