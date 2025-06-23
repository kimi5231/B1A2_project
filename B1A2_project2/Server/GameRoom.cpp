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

	// Room에 있는 모든 Object 정보를 입장한 client에 전송
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

	// 살아있는지 확인
	if (session->player == nullptr)
		return;

	RemoveObject(session->player);
}

void GameRoom::AddObject(GameObjectRef object)
{
	int64 id = object->GetId();

	// id를 이용해 객체 타입 구분
	if (1 <= id || id >= 100)	// Player
	{
		// 신규 Player 추가
		PlayerRef player = static_pointer_cast<Player>(object);
		_players[id] = player;
		
		// 신규 Player 정보를 기존 Player들에게 전송
		{
			Protocol::S_AddPlayer pkt;

			Protocol::ActorInfo* actorInfo = pkt.add_actor();
			Protocol::ObjectInfo* objectInfo = pkt.add_object();

			// 값을 수정
			*actorInfo = player->GetActorInfo();
			*objectInfo = player->GetObjectInfo();

			SendBufferRef sendBuffer = ServerPacketHandler::Make_S_AddPlayer(pkt);
			Broadcast(sendBuffer);
		}
	}
	
	// 신규 Object가 현재 존재하는 Room 기록
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

	// Room에 있는 모든 object에게 object 삭제 정보 전송
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