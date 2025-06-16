#include "pch.h"
#include "GameObject.h"
#include "Stat.h"
#include "Player.h"
#include "DataManager.h"

GameObject::GameObject()
{
	// Stat Load
	GET_SINGLE(DataManager)->LoadStat();
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
	player->SetActorInfo(1, 400, 200);

	// ObjectInfo
	player->SetObjectInfo(Protocol::OBJECT_STATE_TYPE_IDLE, Protocol::DIR_TYPE_RIGHT);

	// PlayerStat
	Stat* stat = GET_SINGLE(DataManager)->GetStat();
	player->SetStat(stat->GetPlayerStat());

	return player;
}