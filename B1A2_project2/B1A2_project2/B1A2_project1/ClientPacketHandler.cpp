#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "MyPlayer.h"
#include "TiredOfficeWorker.h"
#include "BrokenCopyMachine.h"

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
	case S_AddObject:
		Handle_S_AddObject(session, buffer, len);
		break;
	case S_RemoveObject:
		Handle_S_RemoveObject(session, buffer, len);
		break;
	case S_MyPlayer:
		Handle_S_MyPlayer(session, buffer, len);
		break;
	case S_Move:
		Handle_S_Move(session, buffer, len);
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

void ClientPacketHandler::Handle_S_AddObject(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_AddObject pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	if (dynamic_cast<GameScene*>(scene))
	{
		GameScene* Scene = dynamic_cast<GameScene*>(scene);

		const int32 size = pkt.actors_size();
		for (int32 i = 0; i < size; i++)
		{
			const Protocol::ActorInfo& actorInfo = pkt.actors(i);
			const Protocol::ObjectInfo& objectInfo = pkt.objects(i);

			int32 id = actorInfo.id();

			// id를 이용해 객체 타입 구분ㅇㅁㅇ
			if (1 <= id && id <= 100)	// Player
			{
				// 자기 자신은 제외
				if (id == Scene->GetMyPlayer()->GetID())
					continue;

				Player* player = Scene->SpawnObject<Player>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posy() }, LAYER_PLAYER);
				player->SetObjectInfo(objectInfo);
			}
			else if(20100 <= id && id <= 20199)	// TOW
			{
				TiredOfficeWorker* tow = Scene->SpawnObject<TiredOfficeWorker>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posy() }, LAYER_MONSTER);
				tow->SetObjectInfo(objectInfo);
			}
			else if (20200 <= id && id <= 20299)	// BCM
			{
				BrokenCopyMachine* bcm = Scene->SpawnObject<BrokenCopyMachine>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posy() }, LAYER_MONSTER);
				bcm->SetObjectInfo(objectInfo);
			}
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

void ClientPacketHandler::Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_MyPlayer pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ActorInfo& actorInfo = pkt.actor();
	const Protocol::ObjectInfo& objectInfo = pkt.object();

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	if (dynamic_cast<GameScene*>(scene))
	{
		GameScene* Scene = dynamic_cast<GameScene*>(scene);

		MyPlayer* player = Scene->SpawnObject<MyPlayer>(actorInfo.id(), Vec2{ actorInfo.posx(), actorInfo.posx() }, LAYER_PLAYER);
		player->SetObjectInfo(objectInfo);
		Scene->SetPlayer(player);
	}
}

void ClientPacketHandler::Handle_S_Move(ServerSessionRef session, BYTE* buffer, int32 len)
{
	PacketHeader* header = (PacketHeader*)buffer;
	uint16 size = header->size;

	Protocol::S_Move pkt;
	pkt.ParseFromArray(&header[1], size - sizeof(PacketHeader));

	const Protocol::ActorInfo& actorInfo = pkt.actor();
	const Protocol::ObjectInfo& objectInfo = pkt.object();

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();

	if (dynamic_cast<GameScene*>(scene))
	{
		GameScene* gameScene = dynamic_cast<GameScene*>(scene);

		// 자기 자신 제외
		int32 id = gameScene->GetMyPlayer()->GetID();
		if (id == actorInfo.id())
			return;

		Actor* actor = gameScene->GetActor(id);
		if (dynamic_cast<GameObject*>(actor))
		{
			GameObject* object = dynamic_cast<GameObject*>(actor);

			object->SetActorInfo(actorInfo);
			object->SetObjectInfo(objectInfo);
		}
	}
}

SendBufferRef ClientPacketHandler::Make_C_Move()
{
	Protocol::C_Move pkt;

	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	MyPlayer* myPlayer = scene->GetMyPlayer();

	*pkt.mutable_actor() = myPlayer->GetActorInfo();
	*pkt.mutable_object() = myPlayer->GetObjectInfo();

	return MakeSendBuffer(pkt, C_Move);
}