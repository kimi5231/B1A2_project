#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "MyPlayer.h"

void ClientPacketHandler::HandlePacket(ServerSessionRef session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	case S_AddPlayer:
		Handle_S_AddPlayer(session, buffer, len);
		break;
	case S_RemoveObject:
		Handle_S_RemoveObject(session, buffer, len);
		break;
	case S_MyPlayer:
		Handle_S_MyPlayer(session, buffer, len);
		break;
	}
}

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	//uint16 id = header->id;
	uint16 size = header->size;

	Protocol::S_TEST pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	uint64 id = pkt.id();
	uint32 hp = pkt.hp();
	uint16 attack = pkt.attack();

	std::cout << "ID: " << id << " HP : " << hp << " ATT : " << attack << endl;

	for (int32 i = 0; i < pkt.buffs_size(); i++)
	{
		const Protocol::BuffData& data = pkt.buffs(i);
		std::cout << "BuffInfo : " << data.buffid() << " " << data.remaintime() << endl;
	}
}

void ClientPacketHandler::Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_MyPlayer pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ActorInfo& actorInfo = pkt.actor();
	const Protocol::ObjectInfo& objectInfo = pkt.object();
	const Protocol::PlayerStat& playerStat = pkt.stat();

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	// 추후 GameScene으로 변정 예정
	if (dynamic_cast<GameScene*>(scene))
	{
		GameScene* Scene = dynamic_cast<GameScene*>(scene);

		MyPlayer* player = Scene->SpawnObject<MyPlayer>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posx() }, LAYER_PLAYER);
		player->SetState(objectInfo.state());
		player->SetDir(objectInfo.dir());
		Scene->SetPlayer(player);
	}
}

void ClientPacketHandler::Handle_S_AddPlayer(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_AddPlayer pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	// 추후 GameScene으로 변정 예정
	if (dynamic_cast<GameScene*>(scene))
	{
		GameScene* Scene = dynamic_cast<GameScene*>(scene);

		const int32 size = pkt.actors_size();
		for (int32 i = 0; i < size; i++)
		{
			const Protocol::ActorInfo& actorInfo = pkt.actors(i);
			const Protocol::ObjectInfo& objectInfo = pkt.objects(i);
			const Protocol::PlayerStat& playerStat = pkt.stats(i);

			// 자기 자신은 제외
			if (actorInfo.id() == Scene->GetMyPlayer()->GetID())
				continue;

			Player* player = Scene->SpawnObject<Player>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posx() }, LAYER_PLAYER);
			player->SetState(objectInfo.state());
			player->SetDir(objectInfo.dir());
			//player->SetPlayerStat(playerStat);
		}	
	}
}

void ClientPacketHandler::Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_RemoveObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	{
		const int32 size = pkt.ids_size();
		for (int32 i = 0; i < size; i++)
		{
			const uint64& id = pkt.ids(i);

			Actor* actor = scene->GetActor(id);
			scene->RemoveActor(actor);
		}
	}
}