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

	// server와 session 연결
	session->gameRoom = GetRoomRef();
	session->player = player;
	player->SetSession(session);

	// 입장한 client에 myplayer 정보 보내기
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_MyPlayer(player);
		session->Send(sendBuffer);
	}

	// 모든 오브젝트 정보 전송
	{
		Protocol::S_AddPlayer pkt;

		for (auto& item : _players)
		{
			Protocol::ActorInfo* actorInfo = pkt.add_actor();
			Protocol::ObjectInfo* objectInfo = pkt.add_object();
			Protocol::PlayerStat* playerStat = pkt.add_stat();

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
}

void GameRoom::AddObject(GameObjectRef object)
{
	int64 id = object->GetId();

	static int32 test = 0;

	if (id == 1)
	{
		_players[id+test] = static_pointer_cast<Player>(object);
		test++;
	}
	
	object->SetRoom(shared_from_this());

	// 신규 objcet 정보 전송
	{
		Protocol::S_AddPlayer pkt;

		Protocol::ActorInfo* actorInfo = pkt.add_actor();
		Protocol::ObjectInfo * objectInfo = pkt.add_object();
		Protocol::PlayerStat* playerStat = pkt.add_stat();

		*actorInfo = object->GetActorInfo();
		*objectInfo = object->GetObjectInfo();


		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddPlayer(pkt);
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