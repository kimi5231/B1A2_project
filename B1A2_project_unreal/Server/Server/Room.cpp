#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "GameRoom.h"
#include "Door.h"
#include "Item.h"
#include <chrono>

Room::Room()
{
	_generatePlayerID = 1;
	_generateMonsterID = 1;
	_generateItemID = 1;

	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;

	CreateFactoryGameRooms();
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
		// 플레이어 업데이트
		for (const auto& item : _players)
			item.second->Update();

		// 몬스터 업데이트
		for (const auto& item : _monsters)
			item.second->Update(_map);

		lastUpdate = now;
	}
}

void Room::SetupGameRoomConditions()
{
	
}

void Room::CreateFactoryGameRooms()
{
	// 난이도에 맞춰 조건 설정
	GameRoomConditionInfo conditions = g_dataManager->GetGameRoomConditionInfo(_currentDifficulty, _detailDifficulty);

	// 방별 개수 초기화
	for (int i = 0; i < static_cast<int>(GameRoomType::GameRoomTypeCount); i++)
		_currentGameRoomCount[static_cast<GameRoomType>(i)] = 0;
	
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

	uint generateGameRoomID = 1;

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		GameRoomInfo info = g_dataManager->GetGameRoomInfo(GameRoomType::MainEntranceRoom);

		// 0층 중앙에 배치
		Vector pos{};

		GameRoomRef gameRoom = std::make_shared<GameRoom>(pos, Front, info);

		std::vector<DoorRef>& doors = gameRoom->CreateDoors();
		for (const DoorRef door : doors)
			_connectableDoors[door->GetDir()].push_back(door);

		_gameRooms[generateGameRoomID++] = gameRoom;
		_currentGameRoomCount[GameRoomType::MainEntranceRoom]++;
	}

	// 이후 방 절차적 생성
	// 방별 최대 최소 개수 고려 아직X
	//while(conditions.totalGameRoomCount != _gameRooms.size())
	for (int i : std::views::iota(1u, conditions.totalGameRoomCount))
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

		// 이전 방이 계단
		//if (prevRoom->GetGameRoomType() == GameRoomType::Staircase)
		
		// 이전 방이 난간 통로 or 복도 => 모든 방 가능
		//if (prevRoom->GetGameRoomType() == GameRoomType::RailCatwalk || prevRoom->GetGameRoomType() == GameRoomType::PipedHallways_Line)
		{
			// GameRoomType 선택
			std::uniform_int_distribution<int> selectGameRoomType(static_cast<int>(GameRoomType::GapRoom), static_cast<int>(GameRoomType::Staircase));
			GameRoomType type = static_cast<GameRoomType>(selectGameRoomType(gen));
			GameRoomInfo info = g_dataManager->GetGameRoomInfo(type);

			// 선택된 GameRoomType이 이미 최대치만큼 있으면 다시 뽑기
			if (_currentGameRoomCount[type] == info.maxCreateCount[_currentDifficulty])
				continue;

			Vector pos{};
			Vector doorPos = door->GetPos();
			// 방의 방향은 문과 반대
			Dir dir = static_cast<Dir>((connectDir + 2) % 4);

			// 방의 방향에 맞춰 좌표 설정
			switch (dir)
			{
			case Front:
				pos = {doorPos.x + info.enterDistance, doorPos.y + info.size.y / 2, doorPos.z};
				break;
			case Right:
				pos = { doorPos.x - info.size.y / 2, doorPos.y + info.enterDistance, doorPos.z };
				break;
			case Back:
				pos = { doorPos.x - info.enterDistance, doorPos.y - info.size.y / 2, doorPos.z };
				break;
			case Left:
				pos = { doorPos.x + info.size.y / 2, doorPos.y - info.enterDistance, doorPos.z };
				break;
			}

			GameRoomRef newRoom = std::make_shared<GameRoom>(pos, dir, info);

			// 방을 배치할 자리가 있는지 확인
			bool isCreate = true;
			for (const auto& gameRoom : _gameRooms)
			{
				// 배치하려는 곳에 이미 방이 있으면 생성X
				if (gameRoom.second->CheckCollision(newRoom->GetBoundingBox()))
				{
					isCreate = false;
					break;
				}
			}

			// 최소/최대 층수를 넘기지 않는지 확인
			if (static_cast<int>(_minFloor) * 500 > pos.y + info.size.y)
				continue;

			if (static_cast<int>(_maxFloor) * 500 < pos.y + info.size.y)
				continue;
			
			// 자리가 있으면 배치
			if (isCreate)
			{
				// 방과 연결된 문은 삭제
				door->SetConnectable(false);
				_connectableDoors[connectDir].erase(std::remove(_connectableDoors[connectDir].begin(), _connectableDoors[connectDir].end(), door), _connectableDoors[connectDir].end());
				
				_gameRooms[generateGameRoomID++] = newRoom;
				_currentGameRoomCount[type]++;

				// 문 생성
				std::vector<DoorRef>& doors = newRoom->CreateDoors();
				for (const DoorRef door : doors)
					_connectableDoors[door->GetDir()].push_back(door);
					
				std::cout << "Create" << static_cast<int>(type) << std::endl;
			}
		}

		// 그 외
	}

	std::cout << "Success Create GameRooms" << std::endl;

	// 아이템 생성

	// 추후 다시 사용할 예정
	//g_framework->SendCreateGameRoomPacket(_gameRooms, true);
}

void Room::SetTileState(std::pair<int, int> index, TileState state, int layer)
{
	// 해당 층 비트 지우기
	_map[index] &= ~LAYER_MASK(layer);
	// TileState 변경
	_map[index] |= (state << LAYER_SHIFT(layer));
}

short Room::GetTileState(std::pair<int, int> index, int layer)
{
	return (_map[index] & LAYER_MASK(layer)) >> LAYER_SHIFT(layer);
}

GameObjectRef Room::AddObject(ObjectType type)
{
	GameObjectRef object;

	// 나중에 코드 정리하기
	switch (type) 
	{
	case ObjectType::Player:
		_players[_generatePlayerID] = std::make_shared<Player>();
		object = _players[_generatePlayerID];
		// temp
		Vector pos = object->GetPos();
		pos.x += _playerCount * 100;
		object->SetPos(pos);
		object->SetID(_generatePlayerID++);
		_playerCount++;
		g_framework->SendAddObjectPacket(object, true);
		break;
	// temp. 추후 Monster Type별로 나눌 예정
	case ObjectType::Monster:
		_monsters[_generateMonsterID] = std::make_shared<Monster>();
		object = _monsters[_generateMonsterID];
		object->SetID(_generateMonsterID++);
		g_framework->SendAddObjectPacket(object, true);
		break;
	case ObjectType::Item:
		// ItemType 나중에 바꾸기
		_items[_generateItemID] = std::make_shared<Item>(ItemType::CardboardBox);
		object = _items[_generateItemID];
		object->SetID(_generateItemID);
		g_framework->SendAddItemPacket(_items[_generateItemID++], true);
		break;
	}

	return object;
}

void Room::RemoveObject(ObjectType type, uint id)
{
	switch (type)
	{
	case ObjectType::Item:
		_items.erase(id);
		g_framework->SendRemoveObjectPacket(type, id, true);
		break;
	}
}

GameObjectRef Room::GetObject(ObjectType type, uint id)
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
		return _items[id];
		break;
	}
}