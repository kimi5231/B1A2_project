#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "Session.h"
#include "Cube.h"
#include "Door.h"
#include "Cutlass.h"
#include "Spider.h"
#include "Obstacle.h"
#include "Lantern.h"
#include "EmotionGame.h"
#include "SellingMachine.h"

Room::Room()
{
	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;
}

Room::~Room()
{
}

void Room::Init()
{
	// Player ObjectPool 미리 확보
	for (int i = 0; i < MAX_ROOM_PLAYER; ++i)
	{
		_players[i] = new Player();
		_players[i]->SetID(i);
		_players[i]->SetObjectPoolState(ObjectPoolState::Reusable);
		_players[i]->SetOwnerRoom(this);
	}

	// Monster ObjectPool 미리 확보
	for (int i = 0; i < MAX_MONSTER; ++i)
	{
		MonsterType type = static_cast<MonsterType>(i % static_cast<int>(MonsterType::MonsterTypeCount));

		switch (type)
		{
		case MonsterType::Spider:
			_monsters[i] = new Spider(type, this);
			break;
		case MonsterType::EmotionGame:
			_monsters[i] = new EmotionGame(type, this);
			break;
		default:
			_monsters[i] = new Monster(type, this);
			break;
		}

		_monsters[i]->SetID(i);
		_monsters[i]->SetObjectPoolState(ObjectPoolState::Reusable);
		_monsters[i]->SetOwnerRoom(this);
	}

	// Item ObjectPool 미리 확보
	for (int i = 0; i < MAX_ITEM; ++i)
	{
		ItemType type = static_cast<ItemType>(i % static_cast<int>(ItemType::ItemTypeCount));

		switch (type)
		{
		case ItemType::CUTLASS:
			_items[i] = new Cutlass(type);
			break;
		case ItemType::Blaster:
		case ItemType::Key:
			_items[i] = new Tool(type);
			break;
		case ItemType::LANTERN:
			_items[i] = new Lantern(type);
			break;
		default:
			_items[i] = new Item(type);
			break;
		}

		_items[i]->SetID(i);
		_items[i]->SetObjectPoolState(ObjectPoolState::Reusable);
		_items[i]->SetOwnerRoom(this);
	}

	// 장애물 ObjectPool 미리 확보
	for (int i = 0; i < MAX_OBSTACLE; ++i)
	{
		ObstacleType type = static_cast<ObstacleType>(i % static_cast<int>(ObstacleType::ObstacleTypeCount));
		
		switch (type)
		{
		case ObstacleType::Web:
			_obstacles[i] = new Obstacle();
			break;
		default:
			_obstacles[i] = new Obstacle();
			break;
		}

		_obstacles[i]->SetID(i);
		_obstacles[i]->SetObjectPoolState(ObjectPoolState::Reusable);
		_obstacles[i]->SetOwnerRoom(this);
		_obstacles[i]->SetObstacleType(ObstacleType::Web);
	}

	// 테스트용 아이템 생성
	AddItem(false, ItemType::CardboardBox, { 0, 700, 25 });
	AddItem(true, ItemType::CUTLASS, { 0, 750, 25 });
	AddItem(true, ItemType::Blaster, { 0, 650, 25 });
	AddItem(true, ItemType::Key, { 0, 600, 25 });
	AddItem(true, ItemType::LANTERN, { 0, 550, 25 });

	// 테스트용 몬스터 생성
	Monster* spider = AddMonster(MonsterType::Spider, { 0, 675, 25 });
	spider->SetState(ObjectState::HIT, false);
	spider->SetState(ObjectState::IDLE, false);

	Monster* emotionGame = AddMonster(MonsterType::EmotionGame, { 0, 675, 25 });
	emotionGame->SetState(ObjectState::HIT, false);
	emotionGame->SetState(ObjectState::IDLE, false);

	// base 생성
	CubeInfo info = g_dataManager->GetCubeInfo(CubeType::Base);
	CubeRef base = std::make_shared<Cube>(Vector{0, 0, 0}, Back, info);
	base->SetID(0);
	_base = base;

	CreateFactoryCubes();
}

void Room::Update()
{
	using namespace std::chrono;

	static auto lastUpdate = steady_clock::now();
	const auto TICK = 50ms;

	auto now = steady_clock::now();
	if (now - lastUpdate >= TICK)
	{
		g_timer->Update();

		// Player Update
		for (const auto& player : _players)
		{
			if (player->GetObjectPoolState() != ObjectPoolState::InWorld)
				continue;

			player->Update();
		}
			
		// 몬스터 업데이트
		for (const auto& monster : _monsters)
		{
			if(monster->GetObjectPoolState() != ObjectPoolState::InWorld)
				 continue;
			
			monster->Update(this);
		}
			
		for (const auto& [id, item] : _processingItems)
		{
			if (item->GetObjectPoolState() != ObjectPoolState::InWorld)
				continue;

			item->Update();
		}
			
		lastUpdate = now;
	}
}

void Room::SetupCubeConditions()
{
	
}

void Room::CreateFactoryCubes()
{
	// 난이도에 맞춰 조건 설정
	CubeConditionInfo conditions = g_dataManager->GetGameRoomConditionInfo(_currentDifficulty, _detailDifficulty);

	// 방별 개수 초기화
	for (int i = 0; i < static_cast<int>(CubeType::GameRoomTypeCount); i++)
		_currentCubeCount[static_cast<CubeType>(i)] = 0;
	
	// 나중에 json으로 불러올 예정
	// array로 바꾸는 것도 고려할 것, 고정된 크기
	for (int i = 0; i < DirCount; i++)
		_roomSpawnChance[static_cast<Dir>(i)] = 0.25;

	// 층수 정하기
	std::uniform_int_distribution<int> selectFloor(conditions.floor.first, conditions.floor.second);
	int currentFloor = selectFloor(gen);
	 
	// 층마다 플래그 켜서 이거 킬때 옆에꺼 켜져있는지 확인하고 개수만큼 킬것
	_minFloor = F1_Base;
	_maxFloor = F1_Top;
	for (int i = 0; i < currentFloor; i++)
	{
		std::discrete_distribution selectFloorDir({ 0.5, 0.5 });
		
		// 나중에 정해진 범위를 넘어가지 않도록 처리 필요
		switch (selectFloorDir(gen))
		{
		case 0:
			// 위로 층수 증가
			_maxFloor = static_cast<Floor>(static_cast<int>(_maxFloor) + 1);
			break;
		case 1:
			// 아래로 층수 증가
			_minFloor = static_cast<Floor>(static_cast<int>(_minFloor) - 1);
			break;
		}
	}

	int generateCubeID = 0;
	int generateDoorID = 0;

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		CubeInfo info = g_dataManager->GetCubeInfo(CubeType::MainEntranceRoom);

		// Base와 연결하여 배치
		Vector pos{0, 675, 0};

		CubeRef cube = std::make_shared<Cube>(pos, Front, info);
		cube->SetID(generateCubeID++);

		std::vector<Door*> doors = cube->CreateDoors();
		for (auto& door : doors)
		{
			door->SetID(generateDoorID++);
			door->SetOwnerRoom(this);
			cube->AddDoor(door->GetID());
			_doors.push_back(door);
			_connectableDoors[door->GetDir()].push_back(door);
		}
			
		_cubes.push_back(cube);
		_currentCubeCount[CubeType::MainEntranceRoom]++;
	}

	// 이후 방 절차적 생성
	while(conditions.totalCubeCount != _cubes.size())
	{
		// 연결할 방향 선택
		Dir connectDir;
		while (true)
		{
			std::discrete_distribution selectDoorDir({ _roomSpawnChance[Front], _roomSpawnChance[Right], _roomSpawnChance[Back], _roomSpawnChance[Left] });
			connectDir = static_cast<Dir>(selectDoorDir(gen));
			if (_connectableDoors[connectDir].size() != 0)
				break;
		}

		// 연결할 방향에 맞는 문 선택
		std::uniform_int_distribution<int> selectDoor(0, _connectableDoors[connectDir].size() - 1);
		Door* door = _connectableDoors[connectDir][selectDoor(gen)];

		// CubeType 선택
		// 연결할 방의 타입에 따라 가능한 방 타입 다르게 설정
		CubeType type;
		CubeType prevRoomType = _cubes[door->GetOwnerCubeID()]->GetCubeType();
		switch (prevRoomType)
		{
		case CubeType::Staircase:
		{
			// 연결할 방이 계단 => 방, 난간 통로, 복도 가능
			std::uniform_int_distribution<int> selectGameRoomType(static_cast<int>(CubeType::GapRoom), static_cast<int>(CubeType::PipedHallways_Grid));
			type = static_cast<CubeType>(selectGameRoomType(gen));
			break;
		}
		case CubeType::RailCatwalk:
		case CubeType::PipedHallways_Line:
		{
			// 연결할 방이 난간 통로 or 복도 => 모든 방 가능
			std::uniform_int_distribution<int> selectGameRoomType(static_cast<int>(CubeType::GapRoom), static_cast<int>(CubeType::Staircase));
			type = static_cast<CubeType>(selectGameRoomType(gen));
			break;
		}
		default:
		{
			// 연결할 방이 일반 방 => 계단, 난간 통로, 복도 가능
			std::uniform_int_distribution<int> selectGameRoomType(static_cast<int>(CubeType::RailCatwalk), static_cast<int>(CubeType::Staircase));
			type = static_cast<CubeType>(selectGameRoomType(gen));
			break;
		}
		}

		CubeInfo info = g_dataManager->GetCubeInfo(type);

		// 선택된 CubeType이 이미 최대치만큼 있으면 다시 뽑기
		if (_currentCubeCount[type] == info.maxCreateCount[_currentDifficulty])
			continue;

		Vector pos{};
		Vector doorPos = door->GetPos();
		// 방의 방향은 문과 반대
		Dir dir = static_cast<Dir>((connectDir + 2) % 4);

		// 방의 방향에 맞춰 좌표 설정
		switch (dir)
		{
		case Front:
			pos = { doorPos.x - info.enterDistance, doorPos.y + info.size.y / 2, doorPos.z };
			break;
		case Right:
			pos = { doorPos.x - info.size.y / 2, doorPos.y - info.enterDistance, doorPos.z };
			break;
		case Back:
			pos = { doorPos.x + info.enterDistance, doorPos.y - info.size.y / 2, doorPos.z };
			break;
		case Left:
			pos = { doorPos.x + info.size.y / 2, doorPos.y + info.enterDistance, doorPos.z };
			break;
		}

		CubeRef newCube = std::make_shared<Cube>(pos, dir, info);

		// 방을 배치할 자리가 있는지 확인
		bool isCreate = true;
		for (const CubeRef cube : _cubes)
		{
			// 배치하려는 곳에 이미 방이 있으면 생성X
			if (cube->CheckCollision(newCube->GetBoundingBox()) || _base->CheckCollision(newCube->GetBoundingBox()))
			{
				isCreate = false;
				break;
			}
		}

		// 최소/최대 층수를 넘기지 않는지 확인
		/*if (static_cast<int>(_minFloor) * 500 > pos.y + info.size.y)
			continue;
		if (static_cast<int>(_maxFloor) * 500 < pos.y + info.size.y)
			continue;*/

		// 자리가 있으면 배치
		if (isCreate)
		{
			door->SetConnectedCubeID(generateCubeID);
			door->SetOwnerRoom(this);
			// 방과 연결된 문은 삭제
			door->SetConnectable(false);
			_connectableDoors[connectDir].erase(std::remove(_connectableDoors[connectDir].begin(), _connectableDoors[connectDir].end(), door), _connectableDoors[connectDir].end());

			// ID 부여
			newCube->SetID(generateCubeID++);

			// 연결된 방끼리 서로 기록
			newCube->AddConnectedRoom(_cubes[door->GetOwnerCubeID()]);
			newCube->AddDoor(door->GetID());
			_cubes[door->GetOwnerCubeID()]->AddConnectedRoom(newCube);

			_cubes.push_back(newCube);
			_currentCubeCount[type]++;

			// 문 생성
			std::vector<Door*> doors = newCube->CreateDoors();
			for (auto& door : doors)
			{
				door->SetID(generateDoorID++);
				door->SetOwnerRoom(this);
				newCube->AddDoor(door->GetID());
				_doors.push_back(door);
				_connectableDoors[door->GetDir()].push_back(door);
			}

			std::cout << "Create" << static_cast<int>(type) << std::endl;
		}
	}

	for (auto& doors : _connectableDoors)
	{
		for (auto& door : doors.second)
			door->SetDoorType(DoorType::Wall);
	}

	// SellingMachine 생성
	int generateSellingMachineID = 0;

	// 나중에 특수 판매기 설치 추가 예정
	while (_sellingMachines.size() < conditions.createSellingMachineCount)
	{
		std::uniform_int_distribution<int> selectCube(0, _cubes.size() - 1);
		CubeRef cube = _cubes[selectCube(gen)];
		CubeInfo info = cube->GetCubeInfo();

		if (info.isCreateSellingMachine)
		{
			std::uniform_int_distribution<int> selectSellingMachine(0, info.sellingMachinePos.size() - 1);
			int sellingMachineIndex = selectSellingMachine(gen);
			
			SellingMachine* sellingMachine = new SellingMachine(info.sellingMachineDir[sellingMachineIndex], false);
			sellingMachine->SetID(generateSellingMachineID++);
			sellingMachine->SetPos(cube->GetPos() + info.sellingMachinePos[sellingMachineIndex]);
			sellingMachine->SetOwnerRoom(this);
			sellingMachine->SetState(ObjectState::OPEN);
			_sellingMachines.push_back(sellingMachine);
		}
	}

	// 아이템 생성

	std::cout << "Success Create GameRooms" << std::endl;

	// 추후 다시 사용할 예정
	//g_framework->SendCreateGameRoomPacket(_gameRooms, true);
}

void Room::StartStage()
{
	// Cube 생성
	CreateFactoryCubes();
	//g_network->SendCreateCubesPacket(_cubes, _doors, true);

	AddItem(false, ItemType::CardboardBox, { 0, 700, 25 });
	AddItem(true, ItemType::CUTLASS, { 0, 750, 25 });
	AddItem(true, ItemType::Blaster, { 0, 650, 25 });
	AddItem(true, ItemType::Key, { 0, 600, 25 });
	AddItem(true, ItemType::LANTERN, { 0, 550, 25 });

	Monster* spider = AddMonster(MonsterType::Spider, { 0, 675, 25 });
	spider->SetState(ObjectState::HIT, false);
	spider->SetState(ObjectState::IDLE, false);

	Monster* emotionGame = AddMonster(MonsterType::EmotionGame, { 0, 675, 25 });
	emotionGame->SetState(ObjectState::HIT, false);
	emotionGame->SetState(ObjectState::IDLE, false);
}

void Room::EndStage()
{
	_cubes.clear();
	_doors.clear();
	_sellingMachines.clear();
	_connectableDoors.clear();

	for(auto& monster : _monsters)
		monster->SetObjectPoolState(ObjectPoolState::Reusable);
	for(auto& item : _items)
		item->SetObjectPoolState(ObjectPoolState::Reusable);
	for (auto& obstacle : _obstacles)
		obstacle->SetObjectPoolState(ObjectPoolState::Reusable);
}

Player* Room::AddPlayer()
{
	for (int i = 0; i < MAX_ROOM_PLAYER; ++i)
	{
		// 재사용 가능한 플레이어 찾기
		if (_players[i]->GetObjectPoolState() == ObjectPoolState::Reusable)
		{
			// ObjectPoolState 변경
			_players[i]->SetObjectPoolState(ObjectPoolState::InWorld);

			for (auto& player : _players)
			{
				if(player->GetClient())
					g_network->SendAddPlayerPacket(_players[i], player->GetClient());
			}
				
			return _players[i];
		}
	}
}

Monster* Room::AddMonster(MonsterType monsterType, Vector pos)
{
	for (auto& monster : _monsters)
	{
		// 같은 종류의 재사용 가능한 몬스터 찾기
		if (monster->GetObjectPoolState() == ObjectPoolState::Reusable && monster->GetMonsterType() == monsterType)
		{
			// 재사용이 가능하면, 정보 재설정
			monster->SetPos(pos);

			// ObjectPoolState 변경
			monster->SetObjectPoolState(ObjectPoolState::InWorld);

			for (auto& player : _players)
			{
				if (player->GetClient())
					g_network->SendAddMonsterPacket(monster, player->GetClient());
			}

			return monster;
		}
	}
}

Item* Room::AddItem(bool isTool, ItemType itemType, Vector pos)
{
	for (auto& item : _items)
	{
		// 재사용 가능한 아이템 찾기
		if (item->GetObjectPoolState() == ObjectPoolState::Reusable && isTool == (dynamic_cast<Tool*>(item) != nullptr))
		{
			// 재사용이 가능하면, 정보 재설정
			item->SetPos(pos);
			item->SetItemType(itemType);

			// ObjectPoolState 변경
			item->SetObjectPoolState(ObjectPoolState::InWorld);

			for (auto& player : _players)
			{
				if (player->GetClient())
					g_network->SendAddItemPacket(item, isTool, player->GetClient());
			}

			return item;
		}
	}
}

Obstacle* Room::AddObstacle(ObstacleType obstacleType, Vector pos, Rotation rotation)
{
	for (auto& obstacle : _obstacles)
	{
		// 재사용 가능한 장애물 찾기
		if (obstacle->GetObjectPoolState() == ObjectPoolState::Reusable && obstacle->GetObstacleType() == obstacleType)
		{
			// 재사용이 가능하면, 정보 재설정
			obstacle->SetPos(pos);
			obstacle->SetRotation(rotation);
			obstacle->SetObstacleType(obstacleType);

			// ObjectPoolState 변경
			obstacle->SetObjectPoolState(ObjectPoolState::InWorld);

			for (auto& player : _players)
			{
				if (player->GetClient())
					g_network->SendAddObstaclePacket(obstacle, player->GetClient());
			}

			return obstacle;
		}
	}
}

void Room::RemoveObject(ObjectType type, int id)
{
	switch (type)
	{
	case ObjectType::Player:
		_players[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	case ObjectType::Item:
		_items[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	case ObjectType::Obstacle:
		_obstacles[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	}

	for (auto& player : _players)
	{
		if (player->GetClient())
			g_network->SendRemoveObjectPacket(type, id, player->GetClient());
	}		
}

GameObject* Room::GetGameObject(ObjectType type, int id)
{
	switch (type)
	{
	case ObjectType::Player:
		return _players[id];
	case ObjectType::Monster:
		return _monsters[id];
	case ObjectType::Item:
		return _items[id];
	case ObjectType::Door:
		return _doors[id];
	case ObjectType::SellingMachine:
		return _sellingMachines[id];
	}
}