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

	void AddLobbyClient(class Session* session);
	void RemoveLobbyClient(int id);

	Room* AddRoom(std::vector<char>& title);
	void  RemoveRoom(int id);

public:
	Room* GetRoom(int id) { return _rooms[id]; }
	std::array<Room*, MAX_ROOM>& GetRooms() { return _rooms; }

private:
	float _updateLobbyTime;
	std::unordered_map<int, class Session*> _lobbyClients;
	std::array<Room*, MAX_ROOM> _rooms;
};