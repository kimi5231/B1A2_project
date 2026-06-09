#pragma once
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "MainQuest.h"
#include "SubQuest.h"

class Door;
class Hatch;
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
	void CreateCubes();

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

	void PlusCredit(int credit);
	void MinusCredit(int credit);
	
	void AddFearCount() { _currentFearCount++; }
	void AddSurpriseCount() { _currentSurpriseCount++; }
	void AddSadCount() { _currentSadCount++; }

	Player* SelectPlayerForGhost();

	Quest* IsNeedForQuest(ItemType itemType);

public:
	int GetID() { return _id; }
	RoomState GetRoomState() { return _roomState; }
	void SetRoomState(RoomState state) { _roomState = state; }
	int GetCurrentPlayerCount() { return _currentPlayerCount; }
	const std::vector<char>& GetTitle() { return _title; }
	void SetTitle(const std::vector<char>& title) { _title.insert(_title.end(), title.begin(), title.end());  }

public:
	GameObject* GetGameObject(ObjectType type, int id);
	const std::array<Player*, MAX_PLAYER>& GetPlayers() { return _players; }
	const std::array<Monster*, MAX_MONSTER>& GetMonsters() { return _monsters; }
	const std::array<Item*, MAX_ITEM>& GetItems() { return _items; }
	const std::vector<CubeRef>& GetCubes() { return _cubes; }
	const std::vector<Door*>& GetDoors() { return _doors; }
	const std::vector<SellingMachine*>& GetSellingMachine() { return _sellingMachines; }
	int GetGoalCredit() { return _goalCredit; }
	int GetCollectCredit() { return _collectCredit; }
	int GetCurrentCredit() { return _currentCredit; }
	int GetCurrentFearCount() { return _currentFearCount; }
	int GetCurrentSurpriseCount() { return _currentSurpriseCount; }
	Quest* GetMainQuest() { return _mainQuest; }
	Quest* GetSubQuest() { return _subQuest; }
	int GetCurrentStage() { return _stage; }

// Lobby에 나타낼 정보
private:
	int _id;
	RoomState _roomState;
	int _currentPlayerCount;
	std::vector<char> _title;

// 절차적 생성에 필요한 정보
private:
	// 현재 난이도
	Difficulty _currentDifficulty{};
	// 세부 난이도 (삭제 예정)
	Difficulty _detailDifficulty{};

	// 나중에 JSON으로 읽어오기
	std::unordered_map<MonsterType, int> _maxMonsterCount;
	std::unordered_map < Dir, float> _roomSpawnChance;
	Floor _minFloor;
	Floor _maxFloor;

	std::unordered_map<CubeType, int> _currentCubeCount;
	std::unordered_map<MonsterType, int> _currentMonsterCount;
	std::unordered_map<Dir, std::vector<Door*>> _connectableDoors;

// 게임 진행에 필요한 정보
private:
	int _stage;
	int _goalCredit;
	int _collectCredit;
	int _currentCredit;

	MainQuest* _mainQuest;
	SubQuest* _subQuest;

	int _currentPower;

	int _currentSurpriseCount;
	int _currentFearCount;
	int _currentSadCount;

	Hatch* _hatch;
	std::vector<CubeRef> _cubes;
	std::vector<Door*> _doors;
	std::vector<SellingMachine*> _sellingMachines;
	std::array<Player*, MAX_PLAYER> _players;
	std::array<Monster*, MAX_MONSTER> _monsters;
	std::array<Item*, MAX_ITEM> _items;
	std::array<Obstacle*, MAX_OBSTACLE> _obstacles;
	std::unordered_map<int, Item*> _processingItems;
};