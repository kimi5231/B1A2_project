#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "TiredOfficeWorker.h"
#include "BrokenCopyMachine.h"
#include "Stat.h"
#include "Stage.h"
#include "GameRoom.h"
#include "ServerPacketHandler.h"
#include "DataManager.h"

std::atomic<uint64> GameObject::_idGenerator = 1;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::SetState(ObjectState state)
{
	if (_objectInfo.state() == state)
		return;

	_objectInfo.set_state(state);

	BroadcastMove();
}

void GameObject::SetDir(Dir dir)
{
	_objectInfo.set_dir(dir);

	BroadcastMove();
}

PlayerRef GameObject::CreatePlayer()
{
	PlayerRef player = std::make_shared<Player>();

	// 나중에 세이브 데이터에 맞춰 설정할 예정
	// ActorInfo
	player->SetActorInfo(_idGenerator++, { 400, 200 });

	// ObjectInfo
	player->SetState(IDLE);
	player->SetDir(DIR_RIGHT);

	// Client에서 보내는 stat과 비교하는 용도 (패킷 포함X)
	// Stat
	Stat* stat = GET_SINGLE(DataManager)->GetStat();
	player->SetPlayerStat(stat->GetPlayerStat());

	return player;
}

MonsterRef GameObject::CreateMonster(FieldMonster fieldMonster)
{
	// ID에 따라 몬스터 종류 구별
	if (20100 <= fieldMonster.id && fieldMonster.id <= 20199) // TOW
	{
		TiredOfficeWorkerRef tow = std::make_shared<TiredOfficeWorker>();
		
		// ActorInfo
		tow->SetActorInfo(fieldMonster.id, fieldMonster.spawnPos);

		// ObjectInfo
		tow->SetState(IDLE);
		tow->SetDir(fieldMonster.dir);

		// Client에서 보내는 정보와 비교하는 용도 (패킷 포함X)
		Stat* stat = GET_SINGLE(DataManager)->GetStat();
		tow->SetTiredOfficeWorkerStat(stat->GetTiredOfficeWorkerStat());
		tow->SetMovingDistance(fieldMonster.movingDistance);
		tow->SetMovementLimit(fieldMonster.movementLimit);
		
		return tow;
	}
	else if (20200 <= fieldMonster.id && fieldMonster.id <= 20299) // BCM
	{
		BrokenCopyMachineRef bcm = std::make_shared<BrokenCopyMachine>();

		// ActorInfo
		bcm->SetActorInfo(fieldMonster.id, fieldMonster.spawnPos);

		// ObjectInfo
		bcm->SetState(IDLE);
		bcm->SetDir(fieldMonster.dir);

		// Client에서 보내는 정보와 비교하는 용도 (패킷 포함X)
		Stat* stat = GET_SINGLE(DataManager)->GetStat();
		bcm->SetBrokenCopyMachineStat(stat->GetBrokenCopyMachineStat());
		return bcm;
	}
}

void GameObject::BroadcastMove()
{
	if (_room)
	{
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_Move(_actorInfo, _objectInfo);
		_room->Broadcast(sendBuffer);
	}
}