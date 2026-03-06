#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	~Monster();

public:
	void Update(const std::vector<GameRoomRef>& gameRooms);
};