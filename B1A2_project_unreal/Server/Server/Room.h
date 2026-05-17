#pragma once
#include "Player.h"
#include "Monster.h"
#include "Item.h"

class Door;
class SellingMachine;

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
	Monster* AddMonster(MonsterType monsterType, Vector pos);
	Item* AddItem(bool isTool, ItemType itemType, Vector pos);
	Obstacle* AddObstacle(ObstacleType obstacleType, Vector pos, Rotation rotation);
	void RemoveObject(ObjectType type, int id, bool isSend);

	void AddProcessingItem(Item* item) { _processingItems[item->GetID()] = item; }
	void RemoveProcessingItem(int itemID) { _processingItems.erase(itemID); }

	void PlusCredit(int credit) { _currentCredit += credit; if (_currentCredit > _goalCredit) _currentCredit = _goalCredit; }
	void MinusCredit(int credit) { _currentCredit -= credit; if (_currentCredit < 0) _currentCredit = 0; }

public:
	GameObject* GetGameObject(ObjectType type, int id);
	const std::array<Player*, MAX_PLAYER>& GetPlayers() { return _players; }
	const std::array<Monster*, MAX_MONSTER>& GetMonsters() { return _monsters; }
	const std::array<Item*, MAX_ITEM>& GetItems() { return _items; }
	const std::vector<CubeRef>& GetCubes() { return _cubes; }
	const std::vector<Door*>& GetDoors() { return _doors; }
	const std::vector<SellingMachine*>& GetSellingMachine() { return _sellingMachines; }
	int GetGoalCredit() { return _goalCredit; }
	int GetCurrentCredit() { return _currentCredit; }

private:
	CubeRef _base;
	std::vector<CubeRef> _cubes;
	std::vector<Door*> _doors;
	std::vector<SellingMachine*> _sellingMachines;
	std::array<Player*, MAX_PLAYER> _players;
	std::array<Monster*, MAX_MONSTER> _monsters;
	std::array<Item*, MAX_ITEM> _items;
	std::array<Obstacle*, MAX_OBSTACLE> _obstacles;
	std::unordered_map<int, Item*> _processingItems;

private:
	// 현재 맵의 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도
	Difficulty _detailDifficulty{};

	std::unordered_map<CubeType, int> _currentCubeCount;

	std::unordered_map<Dir, std::vector<Door*>> _connectableDoors;

	// 각 방향별로 방이 생성될 확률
	std::unordered_map < Dir, float> _roomSpawnChance;

	Floor _minFloor;
	Floor _maxFloor;

	int _goalCredit;
	int _currentCredit;
};