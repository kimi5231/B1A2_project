#pragma once
#include "Player.h"

class RoomInfo;

class Room
{
public:
	Room();
	~Room();

public:
	void Update();

public:
	void CreateGameRoom();

	GameObjectRef AddObject(ObjectType type);

public:
	GameObjectRef GetObject(UINT id) { return _players[id]; }
	const std::unordered_map<UINT, PlayerRef>& GetPlayers() { return _players; }

	// temp
	const std::vector<GameRoomRef>& GetGameRooms() { return _gameRooms; }

private:
	UINT _generatePlayerID{};

	std::vector<GameRoomRef> _gameRooms;
	std::unordered_map<UINT, PlayerRef> _players;

	// temp
	UINT _playerCount{};
};