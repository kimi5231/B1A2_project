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
	// temp
	void CreateGameRoom();
	
	void CreateFactoryGameRoom();

	GameObjectRef AddObject(ObjectType type);

public:
	GameObjectRef GetObject(UINT id) { return _players[id]; }
	const std::unordered_map<UINT, PlayerRef>& GetPlayers() { return _players; }
	const std::vector<GameRoomRef>& GetGameRooms() { return _gameRooms; }

private:
	// 추후 로그인 기능 추가 후 ID로 대체할 것
	UINT _generatePlayerID{};

	std::vector<GameRoomRef> _gameRooms;
	std::unordered_map<UINT, PlayerRef> _players;

	UINT _playerCount{};

private:
	// 현재 맵의 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도
	Difficulty _detailDifficulty{};

	int _gameRoomCount{};
};