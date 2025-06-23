#include "pch.h"
#include "GameRoom.h"
#include "GameObject.h"
#include "Player.h"
#include "GameSession.h"
#include "ServerPacketHandler.h"

GameRoomRef GRoom = make_shared<GameRoom>();

GameRoom::GameRoom()
{
}

GameRoom::~GameRoom()
{
}

void GameRoom::Init()
{
}

void GameRoom::Update()
{
}

void GameRoom::EnterRoom(GameSessionRef session)
{
	PlayerRef player = GameObject::CreatePlayer();

	// server�� session ����
	session->gameRoom = GetRoomRef();
	session->player = player;
	player->SetSession(session);

	// ������ client�� myplayer ���� ������
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_MyPlayer(player);
		session->Send(sendBuffer);
	}

	// Room�� �ִ� ��� Object ������ ������ client�� ����
	{
		Protocol::S_AddPlayer pkt;

		for (auto& item : _players)
		{
			Protocol::ActorInfo* actorInfo = pkt.add_actor();
			Protocol::ObjectInfo* objectInfo = pkt.add_object();

			*actorInfo = item.second->GetActorInfo();
			*objectInfo = item.second->GetObjectInfo();
		}

		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddPlayer(pkt);
		session->Send(sendBuffer);
	}

	AddObject(player);
}

void GameRoom::LeaveRoom(GameSessionRef session)
{
	if (session == nullptr)
		return;

	// ����ִ��� Ȯ��
	if (session->player == nullptr)
		return;

	RemoveObject(session->player);
}

void GameRoom::AddObject(GameObjectRef object)
{
	int64 id = object->GetId();

	// id�� �̿��� ��ü Ÿ�� ����
	if (1 <= id || id >= 100)	// Player
	{
		// �ű� Player �߰�
		PlayerRef player = static_pointer_cast<Player>(object);
		_players[id] = player;
		
		// �ű� Player ������ ���� Player�鿡�� ����
		{
			Protocol::S_AddPlayer pkt;

			Protocol::ActorInfo* actorInfo = pkt.add_actor();
			Protocol::ObjectInfo* objectInfo = pkt.add_object();

			// ���� ����
			*actorInfo = player->GetActorInfo();
			*objectInfo = player->GetObjectInfo();

			SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddPlayer(pkt);
			Broadcast(sendBuffer);
		}
	}
	
	// �ű� Object�� ���� �����ϴ� Room ���
	object->SetRoom(shared_from_this());
}

void GameRoom::RemoveObject(GameObjectRef object)
{
	if (object == nullptr)
		return;

	uint64 id = object->GetId();

	if (1 <= id || id <= 100)
	{
		_players.erase(id);
	}

	object->_room = nullptr;

	// Room�� �ִ� ��� object���� object ���� ���� ����
	{
		Protocol::S_RemoveObject pkt;
		pkt.add_ids(id);

		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_RemoveObject(pkt);
		Broadcast(sendBuffer);
	}
}

void GameRoom::Broadcast(SendBufferRef& sendBuffer)
{
	for (auto& item : _players)
	{
		item.second->GetSession()->Send(sendBuffer);
	}
}