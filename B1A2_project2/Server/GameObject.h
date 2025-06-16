#pragma once
#include "Actor.h"



class GameObject : public Actor, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

public:
	void SetObjectInfo(Protocol::OBJECT_STATE_TYPE stat, Protocol::DIR_TYPE dir);
	Protocol::ObjectInfo GetObjectInfo() { return _info; }

	void SetRoom(GameRoomRef room) { _room = room; }

public:
	static PlayerRef CreatePlayer();

public:
	Protocol::ObjectInfo _info;
	GameRoomRef _room;
};