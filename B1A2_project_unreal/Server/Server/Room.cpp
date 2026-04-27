#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "Cube.h"
#include "Door.h"
#include "Item.h"
#include "Cutlass.h"
#include "Spider.h"
#include "Obstacle.h"

Room::Room()
{
	_generatePlayerID = 1;
	_generateMonsterID = 1;
	_generateItemID = 1;
	_generateObstacleID = 1;

	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;

	CreateFactoryCubes();

	// 테스트용 아이템 생성
	ItemRef box = std::make_shared<Item>(ItemType::CardboardBox);
	box->SetID(_generateItemID++);
	box->SetPos({ 0, -100, 25 });
	box->SetObjectPoolState(ObjectPoolState::InWorld);
	_items.push_back(box);
	std::shared_ptr<Cutlass> cutlass = std::make_shared<Cutlass>(ItemType::CUTLASS);
	cutlass->SetID(_generateItemID++);
	cutlass->SetPos({ 0, -200, 25 });
	cutlass->SetObjectPoolState(ObjectPoolState::InWorld);
	_items.push_back(cutlass);
	ItemRef blaster = std::make_shared<Tool>(ItemType::Blaster);
	blaster->SetID(_generateItemID++);
	blaster->SetPos({ 0, 100, 25 });
	blaster->SetObjectPoolState(ObjectPoolState::InWorld);
	_items.push_back(blaster);
	ItemRef key = std::make_shared<Tool>(ItemType::Key);
	key->SetID(_generateItemID++);
	key->SetPos({ 0, 200, 25 });
	key->SetObjectPoolState(ObjectPoolState::InWorld);
	_items.push_back(key);
	ItemRef lantern = std::make_shared<Tool>(ItemType::LANTERN);
	lantern->SetID(_generateItemID++);
	lantern->SetPos({ 0, -100, 25 });
	lantern->SetObjectPoolState(ObjectPoolState::InWorld);
	_items.push_back(lantern);

	// 테스트용 몬스터 생성
	MonsterRef none1 = std::make_shared<Monster>(MonsterType::None);
	none1->SetID(_generateMonsterID++);
	none1->SetPos({0, 100, 65});
	none1->SetObjectPoolState(ObjectPoolState::InWorld);
	_monsters.push_back(none1);
	MonsterRef spider = std::make_shared<Spider>(MonsterType::Spider);
	spider->SetID(_generateMonsterID++);
	spider->SetPos({ 0, 100, 65 });
	spider->SetObjectPoolState(ObjectPoolState::InWorld);
	spider->SetState(ObjectState::DEAD, false);
	spider->SetState(ObjectState::IDLE, false);
	_monsters.push_back(spider);
	
	// 장애물 ObjectPool 미리 확보
	for (int i = 0; i < 10; i++)
	{
		ObstacleRef obstacle = std::make_shared<Obstacle>();
		obstacle->SetID(_generateObstacleID++);
		obstacle->SetObstacleType(ObstacleType::None);
		obstacle->SetObjectPoolState(ObjectPoolState::Reusable);
		_obstacles.push_back(obstacle);
	}
}

Room::~Room()
{
}

void Room::Update()
{
	using namespace std::chrono;

	static auto lastUpdate = steady_clock::now();
	const auto TICK = 50ms; // 20Hz, 50ms마다 실행

	auto now = steady_clock::now();
	if (now - lastUpdate >= TICK)
	{
		g_timer->Update();

		// 플레이어 업데이트
		for (const auto& item : _players)
			item.second->Update();

		// 몬스터 업데이트
		for (const auto& monster : _monsters)
			monster->Update(this);

		// 플레이어, 몬스터 충돌 처리
		/*for (const auto& playerItem : _players)
		{
			for (const auto& monsterItem : _monsters)
			{
				if (playerItem.second->CheckCollision(monsterItem.second->GetBoundingBox()))
					g_framework->SendRemoveObjectPacket(monsterItem.second->GetObjectType(), monsterItem.second->GetID(), true);
			}
		}*/

		for(const auto& item : _processingItems)
			item.second->Update();

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
	uint currentFloor = selectFloor(gen);
	 
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

	uint generateCubeID = 0;
	uint generateDoorID = 1;

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		CubeInfo info = g_dataManager->GetCubeInfo(CubeType::MainEntranceRoom);

		// 0층 중앙에 배치
		Vector pos{};

		CubeRef cube = std::make_shared<Cube>(pos, Front, info);
		cube->SetID(generateCubeID++);

		std::vector<DoorRef> doors = cube->CreateDoors();
		for (const DoorRef door : doors)
		{
			door->SetID(generateDoorID++);
			cube->AddDoor(door->GetID());
			_doors.push_back(door);
			_connectableDoors[door->GetDir()].push_back(door);
		}
			
		_cubes.push_back(cube);
		_currentCubeCount[CubeType::MainEntranceRoom]++;
	}

	// 이후 방 절차적 생성
	while(conditions.totalCubeCount != _cubes.size())
	//for (int i : std::views::iota(1u, conditions.totalCubeCount))
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
		DoorRef door = _connectableDoors[connectDir][selectDoor(gen)];

		// CubeType 선택
		// 연결할 방의 타입에 따라 가능한 방 타입 다르게 설정
		CubeType type;
		CubeType prevRoomType = _cubes[door->GetRoomID()]->GetCubeType();
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
			if (cube->CheckCollision(newCube->GetBoundingBox()))
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
			// 방과 연결된 문은 삭제
			door->SetConnectable(false);
			_connectableDoors[connectDir].erase(std::remove(_connectableDoors[connectDir].begin(), _connectableDoors[connectDir].end(), door), _connectableDoors[connectDir].end());

			// ID 부여
			newCube->SetID(generateCubeID++);

			// 연결된 방끼리 서로 기록
			newCube->AddConnectedRoom(_cubes[door->GetRoomID()]);
			newCube->AddDoor(door->GetID());
			_cubes[door->GetRoomID()]->AddConnectedRoom(newCube);

			_cubes.push_back(newCube);
			_currentCubeCount[type]++;

			// 문 생성
			std::vector<DoorRef> doors = newCube->CreateDoors();
			for (const DoorRef door : doors)
			{
				door->SetID(generateDoorID++);
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

	std::cout << "Success Create GameRooms" << std::endl;

	// 아이템 생성

	// 추후 다시 사용할 예정
	//g_framework->SendCreateGameRoomPacket(_gameRooms, true);
}

GameObjectRef Room::AddObject(ObjectType type)
{
	GameObjectRef object;

	// 나중에 코드 정리하기
	switch (type) 
	{
	case ObjectType::Player:
	{
		_players[_generatePlayerID] = std::make_shared<Player>();
		object = _players[_generatePlayerID];
		// temp
		Vector pos = object->GetPos();
		pos.x += _playerCount * 100;
		object->SetPos(pos);
		object->SetID(_generatePlayerID++);
		_playerCount++;
	}
		break;
	}

	g_framework->SendAddObjectPacket(object, true);

	return object;
}

MonsterRef Room::AddMonster(MonsterType monsterType, Vector pos, bool isSend)
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

			if (isSend)
				g_framework->SendSpawnMonsterPacket(monster, true);

			return monster;
		}
	}
}

ItemRef Room::AddItem(bool isTool, ItemType itemType, Vector pos, bool isSend)
{
	for (auto& item : _items)
	{
		// 재사용 가능한 아이템 찾기
		if (item->GetObjectPoolState() == ObjectPoolState::Reusable && isTool == (dynamic_pointer_cast<Tool>(item) != nullptr))
		{
			// 재사용이 가능하면, 정보 재설정
			item->SetPos(pos);
			item->SetItemType(itemType);

			// ObjectPoolState 변경
			item->SetObjectPoolState(ObjectPoolState::InWorld);

			if (isSend)
				g_framework->SendAddItemPacket(item, isTool, true);

			return item;
		}
	}
}

ObstacleRef Room::AddObstacle(ObstacleType obstacleType, Vector pos, bool isSend)
{
	for (auto& obstacle : _obstacles)
	{
		// 재사용 가능한 장애물 찾기
		if (obstacle->GetObjectPoolState() == ObjectPoolState::Reusable && obstacle->GetObstacleType() == obstacleType)
		{
			// 재사용이 가능하면, 정보 재설정
			obstacle->SetPos(pos);
			obstacle->SetObstacleType(obstacleType);

			// ObjectPoolState 변경
			obstacle->SetObjectPoolState(ObjectPoolState::InWorld);

			//if (isSend)
			//	g_framework->SendSpawnObstaclePacket(obstacle, true);

			return obstacle;
		}
	}
}

void Room::RemoveObject(ObjectType type, uint id, bool isSend)
{
	switch (type)
	{
	case ObjectType::Player:
		_players.erase(id);
		break;
	case ObjectType::Item:
		_items[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	}

	if(isSend)
		g_framework->SendRemoveObjectPacket(type, id, true);
}

GameObjectRef Room::GetGameObject(ObjectType type, uint id)
{
	switch (type)
	{
	case ObjectType::Player:
		return _players[id];
		break;
	case ObjectType::Monster:
		return _monsters[id];
		break;
	case ObjectType::Item:
		return _items[id - 1];
		break;
	case ObjectType::Door:
		return _doors[id - 1];
		break;
	}
}