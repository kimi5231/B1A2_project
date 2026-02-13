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
		for (NetworkEventRef event : _sendEvents)
		{
			ProcessSend(event->packetID, event->serializedPacketData);
			event->isComplete = true;
		}

		_sendEvents.erase(std::remove_if(_sendEvents.begin(), _sendEvents.end(),
			[](NetworkEventRef event) {
				return event->isComplete;
			}), _sendEvents.end());
	}

	// 처리된 Recv 이벤트 삭제
	_recvEvents.erase(std::remove_if(_recvEvents.begin(), _recvEvents.end(),
		[](NetworkEventRef event) {
			return event->isComplete;
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
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_AddObject_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_AddObject_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_AddItem:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_AddItem_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_AddObject_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_UpdateObjectState:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_UpdateObjectState_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_UpdateObjectState_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_Move:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(sizeof(S_Move_Packet));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), sizeof(S_Move_Packet));
		_recvEvents.push_back(event);
		break;
	}
	case S_CreateGameRoom:
	{
		NetworkEventRef event = std::make_shared<NetworkEvent>();
		event->packetID = header.id;
		event->serializedPacketData.resize(packet.size() - sizeof(Header));
		memcpy(event->serializedPacketData.data(), packet.data() + sizeof(Header), packet.size() - sizeof(Header));
		_recvEvents.push_back(event);
		break;
	}
	}
}

void GameNetwork::ProcessSend(PacketID id, const std::vector<char>& packetData)
{
	std::vector<char> packet = CreatePakcet(id, packetData);
	int packetSize = packet.size();

	// packetSize 송신(고정 길이)
	send(_clientSocket, (char*)&packetSize, sizeof(int), 0);
	// packet 송신(가변 데이터)
	send(_clientSocket, packet.data(), packetSize, 0);
}

std::vector<char> GameNetwork::CreatePakcet(PacketID id, const std::vector<char>& packetData)
{
	// Header
	Header header;
	header.id = id;
	header.dataSize = packetData.size();

	// Packet
	std::vector<char> packet(sizeof(Header) + header.dataSize);
	memcpy(packet.data(), &header, sizeof(Header));
	memcpy(packet.data() + sizeof(Header), packetData.data(), header.dataSize);

	return packet;
}

void GameNetwork::SendUpdateObjectStatePacket(int id, ObjectType type, ObjectState state)
{
	// Packet Data 생성
	C_UpdateObjectState_Packet packetData{ id, type, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_UpdateObjectState;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void GameNetwork::SendMovePacket(ObjectType type, int id, Vector pos, Rotation rotation, ObjectState state)
{
	// Packet Data 생성
	C_Move_Packet packetData{ type, id, pos, rotation, state };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	NetworkEventRef event = std::make_shared<NetworkEvent>();
	event->packetID = C_Move;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}