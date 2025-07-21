#pragma once
#include "Actor.h"
#include "Stat.h"

class GameObject : public Actor, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void SetState(ObjectState state);
	ObjectState GetState() { return _objectInfo.state(); }

	void SetDir(Dir dir);
	Dir GetDir() { return _objectInfo.dir(); }

	void SetObjectInfo(Protocol::ObjectInfo info) { _objectInfo = info; }
	Protocol::ObjectInfo GetObjectInfo() { return _objectInfo; }

	void SetRoom(GameRoomRef room) { _room = room; }

public:
	static PlayerRef CreatePlayer();
	static MonsterRef CreateMonster(class FieldMonster fieldMonster);

public:
	void BroadcastMove();

public:
	GameRoomRef _room;

protected:
	Protocol::ObjectInfo _objectInfo;
	static atomic<uint64> _idGenerator;
};