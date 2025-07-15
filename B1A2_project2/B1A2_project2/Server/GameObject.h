#pragma once
#include "Actor.h"
#include "Stat.h"

class GameObject : public Actor, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void SetObjectInfo(Protocol::OBJECT_STATE_TYPE stat, Protocol::DIR_TYPE dir);
	void SetObjectInfo(Protocol::ObjectInfo info) { _info = info; }
	Protocol::ObjectInfo GetObjectInfo() { return _info; }

	void SetRoom(GameRoomRef room) { _room = room; }

public:
	static PlayerRef CreatePlayer();
	static MonsterRef CreateMonster(class FieldMonster fieldMonster);

public:
	GameRoomRef _room;

private:
	Protocol::ObjectInfo _info;
	static atomic<uint64> _idGenerator;
};