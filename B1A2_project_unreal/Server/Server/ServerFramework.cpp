#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"
#include "Player.h"
#include "GameRoom.h"

ServerFramework::ServerFramework()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "윈속 초기화 실패" << std::endl;
		return;
	}

	// listenSocket 생성
	_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
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
	addr.sin_port = htons(7777);
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

	// Room 생성
	_room = new Room();
}

ServerFramework::~ServerFramework()
{
	delete _room;

	// listenSocket 종료
	closesocket(_listenSocket);

	// 윈속 종료
	WSACleanup();
}

void ServerFramework::Update()
{
	// socket set 초기화
	FD_ZERO(&_readSet);
	FD_ZERO(&_writeSet);

	// readSet에 listenSocket 등록
	FD_SET(_listenSocket, &_readSet);

	// readSet, writeSet에 clientSocket 등록
	for (ClientRef client : _clients)
	{
		FD_SET(client->socket, &_readSet);
		FD_SET(client->socket, &_writeSet);
	}

	// select
	if (select(0, &_readSet, &_writeSet, NULL, 0) == SOCKET_ERROR)
	{
		std::cout << "select 실패" << std::endl;
		return;
	}

	// listenSocekt accept 확인
	if (FD_ISSET(_listenSocket, &_readSet))
	{
		// accept
		SOCKET clientSocket;
		sockaddr_in clientAddr;
		int addrLen = sizeof(clientAddr);
		clientSocket = accept(_listenSocket, (sockaddr*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cout << "clientSocket 생성 실패" << std::endl;
		}

		ProcessAccept(clientSocket);
	}

	for (ClientRef client : _clients)
	{
		if (FD_ISSET(client->socket, &_readSet))
		{
			ProcessRecv(client);
		}

		// send가 가능할 때마다 true
		if (FD_ISSET(client->socket, &_writeSet))
		{
			for (auto& sendEvent : _sendEvents)
			{
				std::visit([this, client](auto& event) {
					if (event->isBroadcast)
					{
						Broadcast(event->packetID, event->packetData);
						event->isComplete = true;
						return;
					}

					if (client->socket == event->clientSocket)
					{
						ProcessSend(event->packetID, event->packetData, event->clientSocket);
						event->isComplete = true;
					}
					}, sendEvent);
			}

			_sendEvents.erase(std::remove_if(_sendEvents.begin(), _sendEvents.end(),
				[](const auto& sendEvent) {
					return std::visit([](const auto& event) {return event->isComplete;}, sendEvent);
				}), _sendEvents.end());
		}
	}

	// 연결 끊긴 Client 제거
	for (ClientRef client : _removeClients)
	{
		closesocket(client->socket);
		_clients.erase(std::find(_clients.begin(), _clients.end(), client));
	}

	_removeClients.clear();

	_room->Update();
}

void ServerFramework::ProcessRecv(ClientRef client)
{
	// PacketSize 수신(고정 길이)
	int packetSize{};
	if (recv(client->socket, (char*)&packetSize, sizeof(int), MSG_WAITALL) <= 0)
	{
		ProcessDisconnect(client);
		return;
	}

	// Packet 수신(가변 데이터)
	std::vector<char> packet(512);
	if (recv(client->socket, packet.data(), packetSize, MSG_WAITALL) <= 0)
	{
		ProcessDisconnect(client);
		return;
	}

	// Header 추출
	Header header;
	memcpy(&header, packet.data(), sizeof(Header));

	// Data 추출
	switch (header.id)
	{
	case C_Move:
		C_Move_Packet movePacket;
		memcpy(&movePacket, packet.data() + sizeof(Header), sizeof(C_Move_Packet));
		ProcessMovePacket(movePacket);
		break;
	}
}

template <class T>
void ServerFramework::ProcessSend(PacketID id, const T& packetData, SOCKET clientSocket)
{
	std::vector<char> packet = CreatePakcet(id, packetData);
	int packetSize = packet.size();

	// packetSize 송신(고정 길이)
	send(clientSocket, (char*)&packetSize, sizeof(int), 0);
	// packet 송신(가변 데이터)
	send(clientSocket, packet.data(), packetSize, 0);
}

template<class T>
std::vector<char> ServerFramework::CreatePakcet(PacketID id, const T& packetData)
{
	// Header
	Header header;
	header.id = id;
	header.dataSize = sizeof(packetData);

	// Packet
	std::vector<char> packet(sizeof(Header) + header.dataSize);
	memcpy(packet.data(), &header, sizeof(Header));
	memcpy(packet.data() + sizeof(Header), &packetData, header.dataSize);

	return packet;
}

void ServerFramework::SendAddObjectPacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_AddObject_Packet packetData{ object->GetID(), object->GetPos(), object->GetRotation()};

	// SendEvent 생성
	SendEventRef<S_AddObject_Packet> event = std::make_shared<SendEvent<S_AddObject_Packet>>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_AddObject;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendUpdateObjectStatePacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_UpdateObjectState_Packet packetData{ object->GetID(), object->GetObjectType(), object->GetState() };

	// SendEvent 생성
	SendEventRef<S_UpdateObjectState_Packet> event = std::make_shared<SendEvent<S_UpdateObjectState_Packet>>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_UpdateObjectState;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendMovePacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_Move_Packet packetData{ object->GetID(), object->GetPos(), object->GetRotation(), object->GetState() };

	// SendEvent 생성
	SendEventRef<S_Move_Packet> event = std::make_shared<SendEvent<S_Move_Packet>>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_Move;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendCreateGameRoomPacket(const std::vector<GameRoomRef>& gameRooms, bool broadcast, SOCKET client)
{
	GameRoomInfo roomList[5];

	for (int i = 0; i < gameRooms.size(); i++)
	{
		roomList[i].type = gameRooms[i]->GetGameRoomType();
		roomList[i].pos = gameRooms[i]->GetPos();
		roomList[i].size = gameRooms[i]->GetSize();
	}

	// Packet Data 생성
	S_CreateGameRoom_Packet packetData{ roomList[0], roomList[1], roomList[2], roomList[3], roomList[4]};

	// SendEvent 생성
	SendEventRef<S_CreateGameRoom_Packet> event = std::make_shared<SendEvent<S_CreateGameRoom_Packet>>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_CreateGameRoom;
	event->packetData = packetData;

	_sendEvents.push_back(event);
}

template<class T>
void ServerFramework::Broadcast(PacketID id, const T& packetData)
{
	// Room에 있는 모든 Client에게 Packet 송신
	for (ClientRef client : _clients)
		ProcessSend(id, packetData, client->socket);
}

void ServerFramework::ProcessAccept(SOCKET clientSocket)
{
	// 접속한 Client를 나타낼 Player 추가
	GameObjectRef player = _room->AddObject(ObjectType::Player);

	ClientRef newClient = std::make_shared<Client>();
	newClient->socket = clientSocket;
	newClient->player = std::dynamic_pointer_cast<Player>(player);

	_clients.push_back(newClient);

	std::cout << "Client 접속" << std::endl;

	// 추후 게임 시작 시 broadcast로 보내도록 코드 옮기기
	// GameRoom 정보 송신
	SendCreateGameRoomPacket(_room->GetGameRooms(), false, newClient->socket);

	// 새로 접속한 Client에게 Room에 있는 모든 Player 정보 송신 (자기 자신 포함)
	const std::unordered_map<UINT, PlayerRef>& players = _room->GetPlayers();
	for (const auto& item : players)
		SendAddObjectPacket(item.second, false, newClient->socket);
}

void ServerFramework::ProcessDisconnect(ClientRef client)
{

}

void ServerFramework::ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet)
{
	GameObjectRef object = _room->GetObject(packet.objectID);

	object->SetState(packet.state);

	// 자신을 제외한 모든 클라이언트에게 알리기
	for (ClientRef client : _clients)
	{
		if (client->player->GetID() != packet.objectID)
			SendUpdateObjectStatePacket(object, false, client->socket);
	}
}

void ServerFramework::ProcessMovePacket(C_Move_Packet packet)
{
	GameObjectRef object = _room->GetObject(packet.objectID);

	object->SetPos(packet.pos);
	object->SetRotation(packet.rotation);
	object->SetState(packet.state);

	// 자신을 제외한 모든 클라이언트에게 알리기
	for (ClientRef client : _clients)
	{
		if (client->player->GetID() != packet.objectID)
			SendMovePacket(object, false, client->socket);
	}
}