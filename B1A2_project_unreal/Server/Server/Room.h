#pragma once
#include "Player.h"

class Door;

class Room
{
public:
	Room();
	~Room();

public:
	void Update();

public:
	// 절차적 생성 관련 함수
	void SetupGameRoomConditions();
	void CreateFactoryGameRooms();

	void SetTileState(std::pair<int, int> index, TileState state, int layer);

public:
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

	std::unordered_map<Dir, std::vector<DoorRef>> _connectableDoors;

	// 절차적으로 생성되는 방들이 기록되는 전체 공간
	std::array<std::array<char, Width>, Height> _map;

	std::unordered_map<std::pair<int, int>, short, PairHash> map;

	// 각 방향별로 방이 생성될 확률
	std::unordered_map < Dir, float> _roomSpawnChance;
};