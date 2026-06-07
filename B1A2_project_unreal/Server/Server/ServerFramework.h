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

	Room* AddRoom(std::vector<char>& title);

public:
	Room* GetRoom(int id) { return _rooms[id]; }
	std::array<Room*, MAX_ROOM>& GetRooms() { return _rooms; }
	std::vector<Room*>& GetWaitingRooms();

private:
	std::array<Room*, MAX_ROOM> _rooms;
};