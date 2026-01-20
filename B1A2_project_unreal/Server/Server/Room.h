#pragma once
#include "Player.h"

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

	void SetupGameRoomConditions();

	void CreateFactoryGameRooms();

	GameObjectRef AddObject(ObjectType type);

public:
	GameObjectRef GetObject(uint id) { return _players[id]; }
	const std::unordered_map<uint, PlayerRef>& GetPlayers() { return _players; }
	const std::vector<GameRoomRef>& GetGameRooms() { return _gameRooms; }

private:
	// 추후 로그인 기능 추가 후 ID로 대체할 것
	uint _generatePlayerID{};

	std::vector<GameRoomRef> _gameRooms;
	std::unordered_map<uint, PlayerRef> _players;

	uint _playerCount{};

private:
	// 현재 맵의 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도
	Difficulty _detailDifficulty{};

	std::unordered_map<GameRoomType, uint> _currentGameRoomCount;
};