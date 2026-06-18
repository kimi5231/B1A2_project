#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "Session.h"
#include "Cube.h"
#include "Hatch.h"
#include "Cutlass.h"
#include "Spider.h"
#include "Obstacle.h"
#include "Lantern.h"
#include "EmotionGame.h"
#include "SellingMachine.h"
#include "Ghost.h"
#include "PollutionMonitor.h"
#include "TrashCollector.h"

Room::Room()
{
	_roomState = RoomState::Reusable;

	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;

	// 몬스터별 최대 개수 초기화 (나중에 Json으로 읽어오기)
	_maxMonsterCount[MonsterType::Spider] = 9;
	_maxMonsterCount[MonsterType::EmotionGame] = 3;
	_maxMonsterCount[MonsterType::Ghost] = 1;
	_maxMonsterCount[MonsterType::TrashCollector] = 7;
	_maxMonsterCount[MonsterType::PollutionMonitor] = 1;

	_stage = -1;
	// 나중에 Json으로 읽어오기
	_goalCredit = 200;
	_collectCredit = 0;
	_currentCredit = 100;

	_mainQuest = new MainQuest();
	_mainQuest->UpdateQuest();
	_subQuest = new SubQuest();
	_subQuest->UpdateQuest();

	// 나중에 Json으로 읽어오기
	_currentPower = 0;
	_currentSurpriseCount = 0;
	_currentFearCount = 0;

	_updateMonsterTime = 0.f;
}

Room::~Room()
{
}

void Room::Init()
{
	// Player ObjectPool 미리 확보
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		_players[i] = new Player();
		_players[i]->SetID(i);
		_players[i]->SetOwnerRoom(this);
	}

	// Monster ObjectPool 미리 확보
	int monsterID = 0;
	for (const auto& [type, count] : _maxMonsterCount)
	{
		for (int i = 0; i < count; ++i)
		{
			switch (type)
			{
			case MonsterType::Spider:
				_monsters[monsterID] = new Spider(type, this);
				break;
			case MonsterType::EmotionGame:
				_monsters[monsterID] = new EmotionGame(type, this);
				break;
			case MonsterType::Ghost:
				_monsters[monsterID] = new Ghost(type, this);
				break;
			case MonsterType::PollutionMonitor:
				_monsters[monsterID] = new PollutionMonitor(type, this);
				break;
			case MonsterType::TrashCollector:
				_monsters[monsterID] = new TrashCollector(type, this);
				break;
			}

			_monsters[monsterID]->SetID(monsterID);
			_monsters[monsterID]->SetObjectPoolState(ObjectPoolState::Reusable);
			_monsters[monsterID]->SetOwnerRoom(this);
			monsterID++;
		}
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

	// Obstacle ObjectPool 미리 확보
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

	// Base 생성
	CubeInfo info = g_dataManager->GetCubeInfo(CubeType::Base);
	CubeRef base = std::make_shared<Cube>(Vector{ 0, 0, 0 }, Back, info);
	base->SetID(0);
	_cubes.push_back(base);

	// Hatch 생성
	Hatch* hatch = new Hatch(info.doorPos[0], Back, 0, Back);
	hatch->SetID(0);
	hatch->SetOwnerRoom(this);
	hatch->SetConnectedCubeID(1);
	base->AddDoor(hatch->GetID());
	_doors.push_back(hatch);
	
	_hatch = hatch;
}

void Room::Update()
{
	_updateMonsterTime += g_timer->GetDeltaTime();
	if (_updateMonsterTime > 0.05)
	{	 
		// 몬스터 업데이트
		for (const auto& monster : _monsters)
		{
			if(monster->GetObjectPoolState() != ObjectPoolState::InWorld)
				 continue;
			
			monster->Update(this);
		}
			
		for (const auto& [id, item] : _processingItems)
		{
			if (item->GetObjectPoolState() == ObjectPoolState::Reusable)
				continue;

			item->Update();
		}

		_hatch->Update();

		_updateMonsterTime = 0.f;
	}
}

void Room::SetupCubeConditions()
{
	
}

void Room::CreateCubes()
{
	// 난이도에 맞춰 조건 설정
	CubeConditionInfo conditions = g_dataManager->GetCubeConditionInfo(_currentDifficulty, _detailDifficulty);

	// 방별 개수 초기화
	for (int i = 0; i < static_cast<int>(CubeType::GameRoomTypeCount); ++i)
		_currentCubeCount[static_cast<CubeType>(i)] = 0;

	// 몬스터별 개수 초기화
	for (int i = 0; i < static_cast<int>(MonsterType::MonsterTypeCount); ++i)
		_currentMonsterCount[static_cast<MonsterType>(i)] = 0;

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

	int generateCubeID = 1;
	int generateDoorID = 1;

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

		// Base와 연결
		cube->AddConnectedRoom(_cubes[0]);
		cube->AddDoor(_doors[0]->GetID());
		_cubes[0]->AddConnectedRoom(cube);
			
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

			// 금액 제한 설정
			std::uniform_int_distribution<int> selectCreditLimit(conditions.sellingMachineCreditLimit.first, conditions.sellingMachineCreditLimit.second);
			int creditLimit = selectCreditLimit(gen);

			Vector cubePos = cube->GetPos();
			Vector pos{};
			pos.z = cubePos.z + info.sellingMachinePos[sellingMachineIndex].z;
			switch (cube->GetDir())
			{
			case Front:
				pos.x = cubePos.x + info.sellingMachinePos[sellingMachineIndex].x;
				pos.y = cubePos.y + info.sellingMachinePos[sellingMachineIndex].y;
				break;
			case Right:
				pos.x = cubePos.x - info.sellingMachinePos[sellingMachineIndex].y;
				pos.y = cubePos.y + info.sellingMachinePos[sellingMachineIndex].x;
				break;
			case Back:
				pos.x = cubePos.x - info.sellingMachinePos[sellingMachineIndex].x;
				pos.y = cubePos.y - info.sellingMachinePos[sellingMachineIndex].y;
				break;
			case Left:
				pos.x = cubePos.x + info.sellingMachinePos[sellingMachineIndex].y;
				pos.y = cubePos.y - info.sellingMachinePos[sellingMachineIndex].x;
				break;
			}

			Dir dir = static_cast<Dir>((cube->GetDir() + info.sellingMachineDir[sellingMachineIndex]) % DirCount);
			SellingMachine* sellingMachine = new SellingMachine(dir, false, creditLimit);
			sellingMachine->SetID(generateSellingMachineID++);
			sellingMachine->SetOwnerRoom(this);
			sellingMachine->SetPos(pos);
			sellingMachine->SetState(ObjectState::OPEN);
			_sellingMachines.push_back(sellingMachine);
		}
	}

	// 몬스터 생성
	// 테스트용 먼저 생성
	/*Monster* spider = AddMonster(MonsterType::Spider, { 0, 675, 25 });
	spider->SetState(ObjectState::HIT, false);
	spider->SetState(ObjectState::IDLE, false);
	_currentPower += spider->GetPower();
	_currentMonsterCount[MonsterType::Spider]++;*/

	Monster* trashCollector = AddMonster(MonsterType::TrashCollector, { 0, 675, 25 });
	trashCollector->SetState(ObjectState::HIT, false);
	trashCollector->SetState(ObjectState::IDLE, false);
	_currentPower += trashCollector->GetPower();
	_currentMonsterCount[MonsterType::TrashCollector]++;

	while (_currentPower < conditions.power)
	{
		MonsterType type;

		// 남은 파워가 8이상이면 Ghost까지 생성 가능
		if (conditions.power - _currentPower >= 8)
		{
			std::uniform_int_distribution<int> selectType(static_cast<int>(MonsterType::Spider), static_cast<int>(MonsterType::Ghost));
			type = static_cast<MonsterType>(selectType(gen));
		}

		// 남은 파워가 5이상이면 PollutionMonitor까지 생성 가능
		else if (conditions.power - _currentPower >= 5)
		{
			std::uniform_int_distribution<int> selectType(static_cast<int>(MonsterType::Spider), static_cast<int>(MonsterType::PollutionMonitor));
			type = static_cast<MonsterType>(selectType(gen));
		}

		// 남은 파워가 3이상이면 EmotionGame까지 생성 가능
		else if (conditions.power - _currentPower >= 3)
		{
			std::uniform_int_distribution<int> selectType(static_cast<int>(MonsterType::Spider), static_cast<int>(MonsterType::EmotionGame));
			type = static_cast<MonsterType>(selectType(gen));
		}

		// 남은 파워가 1이상이면 거미까지 생성 가능
		else if (conditions.power - _currentPower >= 1)
		{
			std::uniform_int_distribution<int> selectType(static_cast<int>(MonsterType::Spider), static_cast<int>(MonsterType::Spider));
			type = static_cast<MonsterType>(selectType(gen));
		}
			
		// 이미 최대 수만큼 생성됐다면 무시
		if (_currentMonsterCount[type] == _maxMonsterCount[type])
			continue;

		// 타입에 맞는 몬스터 생성 후 Power 증가
		std::uniform_int_distribution<int> selectCube(0, _cubes.size() - 1);
		int index = selectCube(gen);
		while (index < 2)
			index = selectCube(gen);
		CubeRef cube = _cubes[index];
		Monster* monster = AddMonster(type, SelectRandomPosInCube(cube));
		monster->SetState(ObjectState::HIT, false);
		monster->SetState(ObjectState::IDLE, false);
		_currentPower += monster->GetPower();
		_currentMonsterCount[type]++;

		std::cout << "Monster" << static_cast<int>(type) << " Spawn\n";
	}

	// 아이템 생성
	std::uniform_int_distribution<int> selectItemCount(conditions.createItemCount.first, conditions.createItemCount.second);
	int createItemCount = selectItemCount(gen);
	for (int i = 0; i < createItemCount; ++i)
	{
		CubeRef cube = nullptr;
		while (!cube)
		{
			std::uniform_int_distribution<int> selectCube(0, _cubes.size() - 1);
			cube = _cubes[selectCube(gen)];

			CubeInfo info = cube->GetCubeInfo();
			if(info.isCreateItem == false)
				cube = nullptr;
		}

		std::uniform_int_distribution<int> selectItemType(static_cast<int>(ItemType::CardboardBox), static_cast<int>(ItemType::EmptyCan));
		ItemType itemType = static_cast<ItemType>(selectItemType(gen));
		ItemInfo itemInfo = g_dataManager->GetItemInfo(itemType);
		Item* item = AddItem(false, itemType, SelectRandomPosInCube(itemInfo.size, cube));
	}

	AddItem(false, ItemType::CardboardBox, { 0, 675, 25 });
	AddItem(false, ItemType::CardboardBox, { 0, 750, 25 });
	/*AddItem(true, ItemType::CUTLASS, { 0, 0, 25 });
	AddItem(true, ItemType::Blaster, { 0, 100, 25 });
	AddItem(true, ItemType::Key, { 0, -100, 25 });
	AddItem(true, ItemType::LANTERN, { 0, 200, 25 });*/

	std::cout << "Success Create Cubes" << std::endl;
}

void Room::StartStage()
{
	// RoomState 변경
	_roomState = RoomState::Play;

	// Cube 생성
	CreateCubes();

	for (auto& p : _players)
	{
		if (p->GetClient())
			g_network->SendCreateCubesPacket(_cubes, _doors, _sellingMachines, p->GetClient());
	}

	// Hatch 열어두기
	_hatch->SetState(ObjectState::OPEN);

	_stage++;

	// 처음 시작하는 것이라면 아래 작업은 제외
	if (_stage == 1)
		return;
	
	// 기간이 다 된 SubQuest 업데이트
	if (_subQuest->GetDeadLine() == 0)
	{
		_subQuest->UpdateQuest();
		
		for (auto& p : _players)
		{
			if (p->GetClient())
				g_network->SendUpdateQuestPacket(_subQuest, false, p->GetClient());
		}
	}

	_subQuest->MinusDeadLine();
}

void Room::EndStage()
{
	// 3 스테이지가 지날 때마다 목표 크레딧 달성 여부 확인 및 초기화
	if (_stage % 3 == 0)
	{
		Quota info = g_dataManager->GetQuota();

		// 달성하지 못했다면 게임 오버 패킷 전송 및 게임 초기화
		if (_goalCredit > _collectCredit)
		{
			_goalCredit = info.initialQuota;
			_currentCredit = 0;

			_stage = 0;

			for (auto& player : _players)
			{
				if (player->GetClient())
					g_network->SendGameOverPacket(player->GetClient());
			}
		}
		else // 달성했다면 다음 스테이지 goalCredit 계산
		{
			int goalCredit = _goalCredit;
			float emotionCount = (_currentFearCount + _currentSurpriseCount + _currentSadCount) / info.avgBadEmotionCnt;
			float e = std::max(info.minEmotion, std::min(info.maxEmotion, info.baseEmotion - emotionCount));
			_goalCredit = goalCredit + info.increaseCredit * (1 + (_stage % 3) * (_stage % 3) / info.relaxivityValue) * e;
			_goalCredit = std::round(_goalCredit);
		}

		_collectCredit = 0;
	}

	// RoomState 변경
	if (_currentPlayerCount < MAX_PLAYER)
		_roomState = RoomState::Wait;
	else
		_roomState = RoomState::Full;

	// 다음 스테이지 난이도 변경

	// Player 초기화 및 Credit 업데이트
	for (auto& player : _players)
	{
		if (player->GetClient())
		{
			player->SetPos({ 0, 0, 25 });
			g_network->SendMovePacket(player, player->GetClient());
			g_network->SendUpdateCreditPacket(_goalCredit, _collectCredit, _currentCredit, player->GetClient());
			player->SetState(ObjectState::IDLE, true);
		}
	}

	// 누적 감정 횟수 초기화
	_currentSurpriseCount = 0;
	_currentFearCount = 0;
	_currentSadCount = 0;

	// 나중에 자료형 바꾸기
	_cubes.erase(_cubes.begin() + 1, _cubes.end());
	_doors.erase(_doors.begin() + 1, _doors.end());
	_sellingMachines.clear();
	_connectableDoors.clear();

	for(auto& monster : _monsters)
		monster->SetObjectPoolState(ObjectPoolState::Reusable);
	for (auto& item : _items)
	{
		// Base에 있는 Item은 제외
		if(item->GetCurrentCubeID() != 0)
			item->SetObjectPoolState(ObjectPoolState::Reusable);
	}
	for (auto& obstacle : _obstacles)
		obstacle->SetObjectPoolState(ObjectPoolState::Reusable);
}

Player* Room::AddPlayer()
{
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		// 재사용 가능한 플레이어 찾기
		if (_players[i]->GetObjectPoolState() == ObjectPoolState::Reusable)
		{
			// ObjectPoolState 변경
			_players[i]->Init();
			_currentPlayerCount++;

			if (_currentPlayerCount == 4)
				_roomState = RoomState::Full;

			for (auto& player : _players)
			{
				if(player->GetClient())
					g_network->SendAddPlayerPacket(_players[i], player->GetClient());
			}
				
			return _players[i];
		}
	}

	return nullptr; 
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

	return nullptr;
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

void Room::RemoveObject(ObjectType type, int id, bool isSend)
{
	switch (type)
	{
	case ObjectType::Player:
		_players[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		_players[id]->SetPos({0, 0, 0});
		_currentPlayerCount--;

		if (_currentPlayerCount == 0)
		{
			SetCollectCredit(0);
			EndStage();
			SetRoomState(RoomState::Reusable);
			return;
		}

		if (_currentPlayerCount < 4 && _roomState != RoomState::Play)
			_roomState = RoomState::Wait;

		// 초기화
		break;
	case ObjectType::Item:
		_items[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	case ObjectType::Obstacle:
		_obstacles[id]->SetObjectPoolState(ObjectPoolState::Reusable);
		break;
	}

	if (isSend)
	{
		for (auto& player : _players)
		{
			if (player->GetClient())
				g_network->SendRemoveObjectPacket(type, id, player->GetClient());
		}
	}
}

void Room::PlusCredit(int credit)
{
	_collectCredit += credit;
	_currentCredit += credit;
	if (_collectCredit > _goalCredit)
		_collectCredit = _goalCredit;

	for (auto& player : _players)
	{
		if (player->GetClient())
			g_network->SendUpdateCreditPacket(_goalCredit, _collectCredit, _currentCredit, player->GetClient());
	}
}

void Room::MinusCredit(int credit)
{
	_currentCredit -= credit;
	if (_currentCredit < 0)
		_currentCredit = 0;

	for (auto& player : _players)
	{
		if (player->GetClient())
			g_network->SendUpdateCreditPacket(_goalCredit, _collectCredit, _currentCredit, player->GetClient());
	}
}

Player* Room::SelectPlayerForGhost()
{
	std::uniform_int_distribution<int> selectCondition(0, 1);
	Player* player = nullptr;

	switch (selectCondition(gen))
	{
	case 0:	// FearCount가  가장 높은 플레이어 선택
	{
		int fearCount = -1;
		for (auto& p : _players)
		{
			if (!p->GetClient())
				continue;

			if (p->GetFearCount() > fearCount)
			{
				fearCount = p->GetFearCount();
				player = p;
			}
		}
		break;
	}
	case 1:	// FearCount가  가장 낮은 플레이어 선택
	{
		int fearCount = std::numeric_limits<int>::max();
		for (auto& p : _players)
		{
			if (!p->GetClient())
				continue;

			if (p->GetFearCount() < fearCount)
			{
				fearCount = p->GetFearCount();
				player = p;
			}
		}
		break;
	}
	//case 2:	// 가지고 있는 Scrap의 가격이 가장 높은 플레이어 선택
	//	break;
	}

	return player;
}

Quest* Room::IsNeedForQuest(ItemType itemType)
{
	if(_mainQuest->IsNeed(itemType))
		return _mainQuest;

	if (_subQuest->IsNeed(itemType))
		return _subQuest;

	return nullptr;
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