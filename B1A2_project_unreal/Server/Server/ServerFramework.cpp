#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"
#include "Player.h"
#include "GameRoom.h"
#include "Item.h"
#include "Door.h"

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
			for (SendEventRef event : _sendEvents)
			{
				if (event->isBroadcast)
				{
					Broadcast(event->packetID, event->serializedPacketData);
					event->isComplete = true;
					break;
				}

				if (client->socket == event->clientSocket)
				{
					ProcessSend(event->packetID, event->serializedPacketData, event->clientSocket);
					event->isComplete = true;
				}
			}

			_sendEvents.erase(std::remove_if(_sendEvents.begin(), _sendEvents.end(),
				[](SendEventRef event) {
					return event->isComplete;
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
	case C_GetItem:
		C_GetItem_Packet getItemPacket;
		memcpy(&getItemPacket, packet.data() + sizeof(Header), sizeof(C_GetItem_Packet));
		ProcessGetItemPacket(getItemPacket);
		break;
	}
}

void ServerFramework::ProcessSend(PacketID id, const std::vector<char>& packetData, SOCKET clientSocket)
{
	std::vector<char> packet = CreatePakcet(id, packetData);
	int packetSize = packet.size();

	// packetSize 송신(고정 길이)
	send(clientSocket, (char*)&packetSize, sizeof(int), 0);
	// packet 송신(가변 데이터)
	send(clientSocket, packet.data(), packetSize, 0);
}

std::vector<char> ServerFramework::CreatePakcet(PacketID id, const std::vector<char>& packetData)
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

template<class T>
std::vector<char> ServerFramework::SerializePOD(const T& pod)
{
	std::vector<char> serializedData(sizeof(pod));
	memcpy(serializedData.data(), &pod, sizeof(pod));
	
	return serializedData;
}

template<class T>
std::vector<char> ServerFramework::SerializeVector(const std::vector<T>& vector)
{
	int size = vector.size();

	std::vector<char> serializedData(sizeof(int) + vector.size() * sizeof(T));
	memcpy(serializedData.data(), &size, sizeof(int));
	memcpy(serializedData.data() + sizeof(int), vector.data(), size * sizeof(T));

	return serializedData;
}

template<class T>
std::vector<T> ServerFramework::DeserializeVector(const std::vector<char>& data)
{
	int size;
	memcpy(&size, data.data(), sizeof(int));
	
	std::vector<T> vector(size);
	memcpy(vector.data(), data.data() + sizeof(int), size * sizeof(T));

	return vector;
}

void ServerFramework::SendAddObjectPacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_AddObject_Packet packetData{ object->GetObjectType(), object->GetID(), object->GetPos(), object->GetRotation()};

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_AddObject;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendAddItemPacket(ItemRef item, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_AddItem_Packet packetData{ item->GetObjectType(), item->GetItemType(), item->GetID(), item->GetPos(), item->GetRotation() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_AddItem;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendRemoveObjectPacket(ObjectType objectType, uint objectID, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_RemoveObject_Packet packetData{ objectType, objectID };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_RemoveObject;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendUpdateObjectStatePacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_UpdateObjectState_Packet packetData{ object->GetID(), object->GetObjectType(), object->GetState() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_UpdateObjectState;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendMovePacket(GameObjectRef object, bool broadcast, SOCKET client)
{
	// Packet Data 생성
	S_Move_Packet packetData{ object->GetObjectType(), object->GetID(), object->GetPos(), object->GetRotation(), object->GetState() };

	// Packet Serialize
	std::vector<char> serializedPacketData = SerializePOD(packetData);

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_Move;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::SendCreateGameRoomPacket(const std::unordered_map<uint, GameRoomRef>& gameRooms, bool broadcast, SOCKET client)
{
	std::vector<GameRoomDTO> roomInfos;
	roomInfos.resize(gameRooms.size());

	uint idx = 0;
	std::vector<DoorRef> walls;
	for (const auto& gameRoom : gameRooms)
	{
		roomInfos[idx].type = gameRoom.second->GetGameRoomType();
		roomInfos[idx].pos = gameRoom.second->GetPos();
		roomInfos[idx].dir = gameRoom.second->GetDir();

		walls.insert(walls.end(), gameRoom.second->GetWalls().begin(), gameRoom.second->GetWalls().end());
		idx++;
	}

	std::vector<WallDTO> wallInfos;
	wallInfos.resize(walls.size());
	
	idx = 0;
	for (const DoorRef wall : walls)
	{
		wallInfos[idx].pos = wall->GetPos();
		wallInfos[idx].dir = wall->GetDir();
		idx++;
	}
	
	// Packet Serialize
	std::vector<char> gameRoomData = SerializeVector(roomInfos);
	std::vector<char> wallData = SerializeVector(wallInfos);
	std::vector<char> serializedPacketData;

	serializedPacketData.insert(serializedPacketData.end(), gameRoomData.begin(), gameRoomData.end());
	serializedPacketData.insert(serializedPacketData.end(), wallData.begin(), wallData.end());

	// SendEvent 생성
	SendEventRef event = std::make_shared<SendEvent>();
	event->isBroadcast = broadcast;
	event->clientSocket = client;
	event->packetID = S_CreateGameRoom;
	event->serializedPacketData = serializedPacketData;

	_sendEvents.push_back(event);
}

void ServerFramework::Broadcast(PacketID id, const std::vector<char>& packetData)
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

	// 새로 접속한 Client에게 Room에 있는 모든 Player 정보 송신
	const std::unordered_map<uint, PlayerRef>& players = _room->GetPlayers();
	for (const auto& item : players)
		SendAddObjectPacket(item.second, false, newClient->socket);
	const std::unordered_map<uint, MonsterRef>& monsters = _room->GetMonsters();
	for (const auto& item : monsters)
		SendAddObjectPacket(item.second, false, newClient->socket);

	// 추후 삭제 예정
	_room->AddObject(ObjectType::Monster);
	_room->AddObject(ObjectType::Item);
}

void ServerFramework::ProcessDisconnect(ClientRef client)
{

}

void ServerFramework::ProcessUpdateObjectStatePacket(C_UpdateObjectState_Packet packet)
{
	GameObjectRef object = _room->GetObject(packet.type, packet.objectID);

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
	GameObjectRef object = _room->GetObject(packet.type, packet.objectID);

	if (object == nullptr)
		return;

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

void ServerFramework::ProcessGetItemPacket(C_GetItem_Packet packet)
{
	// Player가 요청한 아이템이 얻을 수 있는 것인지 확인
	GameObjectRef item = _room->GetObject(ObjectType::Item, packet.itemID);

	// 얻을 수 없는 아이템이면 요청 거절
	if (item == nullptr)
		return;

	// 얻을 수 있는 조건인지 확인하는 코드 추가 필요
	
	// 얻을 수 있는 아이템이라면 Player 인벤토리에 추가 후, 맵에서 Item 삭제
	_room->RemoveObject(ObjectType::Item, packet.itemID);
}