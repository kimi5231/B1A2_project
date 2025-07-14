#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "TiredOfficeWorker.h"
#include "Stat.h"
#include "Stage.h"
#include "DataManager.h"

atomic<uint64> GameObject::_idGenerator = 1;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::SetObjectInfo(Protocol::OBJECT_STATE_TYPE stat, Protocol::DIR_TYPE dir)
{
	Protocol::ObjectInfo info;

	info.set_dir(dir);
	info.set_state(stat);

	_info = info;
}

PlayerRef GameObject::CreatePlayer()
{
	PlayerRef player = std::make_shared<Player>();

	// 나중에 세이브 데이터에 맞춰 설정할 예정
	// ActorInfo
	player->SetActorInfo(_idGenerator++, { 400, 200 });

	// ObjectInfo
	player->SetObjectInfo(Protocol::OBJECT_STATE_TYPE_IDLE, Protocol::DIR_TYPE_RIGHT);

	// Client에서 보내는 stat과 비교하는 용도 (패킷 포함X)
	// Stat
	Stat* stat = GET_SINGLE(DataManager)->GetStat();
	player->SetPlayerStat(stat->GetPlayerStat());

	return player;
}

MonsterRef GameObject::CreateMonster(FieldMonster fieldMonster)
{
	MonsterRef monster = std::make_shared<Monster>();

	// ActorInfo
	monster->SetActorInfo(fieldMonster.id, fieldMonster.spawnPos);

	// ObjectInfo
	monster->SetObjectInfo(Protocol::OBJECT_STATE_TYPE_IDLE, fieldMonster.dir);

	if (20100 <= fieldMonster.id || fieldMonster.id <= 20199)
	{
		std::shared_ptr<TiredOfficeWorker> tow = std::dynamic_pointer_cast<TiredOfficeWorker>(monster);
		
		// TiredOfficeWorkerStat
		Stat* stat = GET_SINGLE(DataManager)->GetStat();
		//tow->SetTiredOfficeWorkerStat(stat->GetTiredOfficeWorkerStat());
		tow->SetMovingDistance(fieldMonster.movingDistance);
		tow->SetMovementLimitX(fieldMonster.movementLimit.x);
		tow->SetMovementLimitY(fieldMonster.movementLimit.y);
	}

	return monster;
}