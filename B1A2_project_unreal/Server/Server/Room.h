#pragma once
#include "Player.h"
#include "Monster.h"
#include "Item.h"

class Door;

class Room
{
public:
	Room();
	~Room();

public:
	void Init();
	void Update();

public:
	// 절차적 생성 관련 함수
	void SetupCubeConditions();
	void CreateFactoryCubes();

	void StartStage();
	void EndStage();

public:
	Player* AddPlayer();
	MonsterRef AddMonster(MonsterType monsterType, Vector pos, bool isSend);
	ItemRef AddItem(bool isTool, ItemType itemType, Vector pos, bool isSend);
	ObstacleRef AddObstacle(ObstacleType obstacleType, Vector pos, bool isSend);
	void RemoveObject(ObjectType type, int id);

	void AddProcessingItem(ItemRef item) { _processingItems[item->GetID()] = item; }
	void RemoveProcessingItem(int itemID) { _processingItems.erase(itemID); }

public:
	GameObjectRef GetGameObject(ObjectType type, uint id);
	GameObject* GetPlayer(ObjectType type, uint id);
	const std::array<Player*, MAX_ROOM_PLAYER>& GetPlayers() { return _players; }
	const std::vector<MonsterRef>& GetMonsters() { return _monsters; }
	const std::vector<ItemRef>& GetItems() { return _items; }
	const std::vector<CubeRef>& GetCubes() { return _cubes; }
	const std::vector<DoorRef>& GetDoors() { return _doors; }
	
private:
	uint _generatePlayerID{};
	uint _generateMonsterID{};
	uint _generateItemID{};
	int _generateObstacleID{};

	CubeRef _base;
	std::vector<CubeRef> _cubes;
	std::vector<DoorRef> _doors;
	std::vector<ObstacleRef> _obstacles;
	std::array<Player*, MAX_ROOM_PLAYER> _players;
	std::vector<MonsterRef> _monsters;
	std::vector<ItemRef> _items;
	std::unordered_map<int, ItemRef> _processingItems;

	uint _playerCount{};

private:
	// 현재 맵의 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도
	Difficulty _detailDifficulty{};

	std::unordered_map<CubeType, uint> _currentCubeCount;

	std::unordered_map<Dir, std::vector<DoorRef>> _connectableDoors;

	// 각 방향별로 방이 생성될 확률
	std::unordered_map < Dir, float> _roomSpawnChance;

	Floor _minFloor;
	Floor _maxFloor;
};