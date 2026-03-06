#pragma once
#include "Player.h"
#include "Monster.h"

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

public:
	GameObjectRef AddObject(ObjectType type);
	void RemoveObject(ObjectType type, uint id);

public:
	GameObjectRef GetObject(ObjectType type, uint id);
	const std::unordered_map<uint, PlayerRef>& GetPlayers() { return _players; }
	const std::unordered_map<uint, MonsterRef>& GetMonsters() { return _monsters; }
	const std::vector<GameRoomRef>& GetGameRooms() { return _gameRooms; }

private:
	// 추후 로그인 기능 추가 후 ID로 대체할 것
	uint _generatePlayerID{};
	uint _generateMonsterID{};
	uint _generateItemID{};

	std::vector<GameRoomRef> _gameRooms;
	std::unordered_map<uint, PlayerRef> _players;
	std::unordered_map<uint, MonsterRef> _monsters;
	std::unordered_map<uint, ItemRef> _items;

	uint _playerCount{};

private:
	// 현재 맵의 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도
	Difficulty _detailDifficulty{};

	std::unordered_map<GameRoomType, uint> _currentGameRoomCount;

	std::unordered_map<Dir, std::vector<DoorRef>> _connectableDoors;

	// 절차적으로 생성되는 방들이 기록되는 전체 공간
	std::unordered_map<std::pair<int, int>, short, PairHash> _map;

	// 각 방향별로 방이 생성될 확률
	std::unordered_map < Dir, float> _roomSpawnChance;

	Floor _minFloor;
	Floor _maxFloor;
};