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
	// 방별 개수 초기화
}

void Room::CreateFactoryGameRooms()
{
	// 난이도에 맞춰 조건 설정
	GameRoomConditionInfo conditions = g_dataManager->GetGameRoomConditionInfo(_currentDifficulty, _detailDifficulty);

	// 나중에 json으로 불러올 예정
	// array로 바꾸는 것도 고려할 것, 고정된 크기
	for (int i = 0; i < DirCount; i++)
		_roomSpawnChance[static_cast<Dir>(i)] = 0.25;

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		GameRoomInfo info = g_dataManager->GetGameRoomInfo(GameRoomType::MainEntranceRoom);

		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		gameRoom->SetGameRoomInfo(info);
		
		// 0층 맵 한 가운데에 배치
		// map은 10cm 단위이기 때문에 pos 1cm 단위로 변환
		Vector pos{ Width / 2 * 10, Height / 2 * 10, 0 };
		gameRoom->SetPos(pos);
		gameRoom->SetDir(Front);

		// index 계산 후 맵에 자치한 공간만큼 채우기(벽 제외)
		uint x = (pos.x - info.size.x / 2) / 10;
		uint y = (pos.y - info.size.y / 2) / 10;

		for (int i = x; i < x + (info.size.x / 10); i++)
		{
			for (int j = y; j < y + (info.size.y / 10); j++)
			{
				// 테두리는 벽으로 지정
				if (i == x || i == x + (info.size.x / 10) - 1 || j == y || j == y + (info.size.y / 10) - 1)
					SetTileState({ i, j }, Wall, 3);
				else
					SetTileState({ i, j }, Passable, 3);
			}	
		}

		std::vector<DoorRef>& doors = gameRoom->CreateDoors();
		for (const DoorRef door : doors)
		{
			_connectableDoors[door->GetDir()].push_back(door);
			
			// 문이 있는 곳도 갈 수 있도록 처리 (추후 문 상태에 따라 다르게 처리할 예정)
			Vector doorPos = door->GetPos();
			std::pair<int, int> index{ door->GetPos().x / 10, door->GetPos().y / 10 };

		    // 일부 방향은 인덱스 조정 필요
			switch (door->GetDir())
			{
			case Right:
				index.first -= 1;
				break;
			case Back:
				index.second -= 1;
				break;
			}

			SetTileState(index, Passable, 3);
		}

		_gameRooms.push_back(gameRoom);
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

			// 나중에 개수 따지기
			//if (_currentGameRoomCount[info.type] < info.maxCreateCount[_currentDifficulty])

			uint x{}, y{};
			Vector pos{};
			Vector doorPos = door->GetPos();
			// 방의 방향은 문과 반대
			Dir dir = static_cast<Dir>((connectDir + 2) % 4);

			// 방의 방향에 맞춰 좌표 설정
			switch (dir)
			{
			case Front:
				pos = {doorPos.x + info.enterDistance, doorPos.y + info.size.y / 2, doorPos.z};
				x = (pos.x - info.size.x / 2) / 10;
				y = (pos.y - info.size.y / 2) / 10;
				break;
			case Right:
				pos = { doorPos.x - info.size.y / 2, doorPos.y + info.enterDistance, doorPos.z };
				x = (pos.x - info.size.y / 2) / 10;
				y = (pos.y - info.size.x / 2) / 10;
				break;
			case Back:
				pos = { doorPos.x - info.enterDistance, doorPos.y - info.size.y / 2, doorPos.z };
				x = (pos.x - info.size.x / 2) / 10;
				y = (pos.y - info.size.y / 2) / 10;
				break;
			case Left:
				pos = { doorPos.x + info.size.y / 2, doorPos.y - info.enterDistance, doorPos.z };
				x = (pos.x - info.size.y / 2) / 10;
				y = (pos.y - info.size.x / 2) / 10;
				break;
			}

			// 방을 배치할 자리가 있는지 확인
			bool isCreate = true;

			switch (dir)
			{
			case Front:
			case Back:
				for (int i = x; i < x + (info.size.x / 10); i++)
				{
					for (int j = y; j < y + (info.size.y / 10); j++)
					{
						// 배치할 공간이 없음, 방 종류 변경 나중에 처리
						if (_map.find({ i, j }) != _map.end())
						{
							isCreate = false;
							break;
						}
					}
					
					if (!isCreate)
						break;
				}
				break;
			case Right:
			case Left:
				for (int i = x; i < x + (info.size.x / 10); i++)
				{
					for (int j = y; j < y + (info.size.y / 10); j++)
					{
						// 배치할 공간이 없음, 방 종류 변경 나중에 처리
						if (_map.find({ j, i }) != _map.end())
						{
							isCreate = false;
							break;
						}
					}

					if (!isCreate)
						break;
				}
				break;
			}

			// 배치 가능하면 방 생성 후 기록
			if (isCreate)
			{
				GameRoomRef gameRoom = std::make_shared<GameRoom>();
				gameRoom->SetGameRoomInfo(info);
				gameRoom->SetPos(pos);
				gameRoom->SetDir(dir);

				// 방과 연결된 문은 제외
				door->SetConnectable(false);
				_connectableDoors[connectDir].erase(std::remove(_connectableDoors[connectDir].begin(), _connectableDoors[connectDir].end(), door), _connectableDoors[connectDir].end());

				switch (dir)
				{
				case Front:
				case Back:
					for (int i = x; i < x + (info.size.x / 10); i++)
					{
						for (int j = y; j < y + (info.size.y / 10); j++)
						{
							// 테두리는 벽으로 지정
							if (i == x || i == x + (info.size.x / 10) - 1 || j == y || j == y + (info.size.y / 10) - 1)
								SetTileState({ i, j }, Wall, 3);
							else
								SetTileState({ i, j }, Passable, 3);
						}
					}
					break;
				case Right:
				case Left:
					for (int i = x; i < x + (info.size.x / 10); i++)
					{
						for (int j = y; j < y + (info.size.y / 10); j++)
						{
							// 테두리는 벽으로 지정
							if (i == x || i == x + (info.size.x / 10) - 1 || j == y || j == y + (info.size.y / 10) - 1)
								SetTileState({ i, j }, Wall, 3);
							else
								SetTileState({ i, j }, Passable, 3);
						}
					}
					break;
				}

				_gameRooms.push_back(gameRoom);

				// 문 생성 후 기록
				std::vector<DoorRef>& doors = gameRoom->CreateDoors();
				for (const DoorRef door : doors)
				{
					_connectableDoors[door->GetDir()].push_back(door);
				
					// 문이 있는 곳도 갈 수 있도록 처리 (추후 문 상태에 따라 다르게 처리할 예정)
					Vector doorPos = door->GetPos();
					std::pair<int, int> index{ door->GetPos().x / 10, door->GetPos().y / 10 };

					// 일부 방향은 인덱스 조정 필요
					switch (door->GetDir())
					{
					case Right:
						index.first -= 1;
						break;
					case Back:
						index.second -= 1;
						break;
					}

					SetTileState(index, Passable, 3);
				}
					
				std::cout << "Create" << static_cast<int>(type) << std::endl;
			}
		}

		// 그 외
	}

	std::cout << "Success Create GameRooms" << std::endl;

	/*for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (_map.find({ j, i }) != _map.end())
			{
				if((GetTileState({j, i}, 3) == Wall))
					std::cout << "■";
				else if((GetTileState({ j, i }, 3) == Passable))
					std::cout << "□";
			}
			else
				std::cout << "◇";
		}
		std::cout << std::endl;
	}*/

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
	}
}