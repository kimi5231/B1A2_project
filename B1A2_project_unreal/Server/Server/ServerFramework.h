#pragma once
#include "Packets.h"

class Room;

class ServerFramework
{
public:
	ServerFramework();
	~ServerFramework();

public:
	void Update();

public:
	Room* GetRoom() { return _room; }

private:
	Room* _room{};
};