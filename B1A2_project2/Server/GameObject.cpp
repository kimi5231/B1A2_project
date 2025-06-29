#include "pch.h"
#include "GameObject.h"
#include "Player.h"
#include "Stat.h"
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

	// ActorInfo
	player->SetActorInfo(_idGenerator++, 400, 200);

	// ObjectInfo
	player->SetObjectInfo(Protocol::OBJECT_STATE_TYPE_IDLE, Protocol::DIR_TYPE_RIGHT);

	// PlayerStat
	Stat* stat = GET_SINGLE(DataManager)->GetStat();
	player->SetPlayerStat(stat->GetPlayerStat());
	
	return player;
}