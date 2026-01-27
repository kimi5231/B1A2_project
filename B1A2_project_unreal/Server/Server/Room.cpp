#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "GameRoom.h"
#include "Door.h"

Room::Room()
{
	_generatePlayerID = 1;

	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;

	CreateFactoryGameRooms();
}

Room::~Room()
{
}

void Room::Update()
{
	for (const auto& item : _players)
		item.second->Update();
}

void Room::SetupGameRoomConditions()
{
	// 방별 개수 초기화
	//std::iota(_currentGameRoomCount.begin(), _currentGameRoomCount.end(), 0);
}

void Room::CreateFactoryGameRooms()
{
	// 난이도에 맞춰 조건 설정
	GameRoomConditionInfo conditions = g_dataManager->GetGameRoomConditionInfo(_currentDifficulty, _detailDifficulty);

	// 나중에 json으로 불러올 예정
	// array로 바꾸는 것도 고려할 것, 고정된 크기
	for (int i = 0; i < DirCount; i++)
		_roomSpawnChance[static_cast<Dir>(i)] = 0.25;

	// map 초기화
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
			_map[i][j] = '0';
	}

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		GameRoomInfo info = g_dataManager->GetGameRoomInfo(GameRoomType::MainEntranceRoom);

		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		gameRoom->SetGameRoomInfo(info);
		
		// 1층에 배치
		//Vector pos{ Width / 2 * 100, info.size.y / 2, 0 };
		Vector pos{ Width / 2 * 100, Height / 2 * 100, 0 };
		gameRoom->SetPos(pos);
		gameRoom->SetDir(Front);

		// 방 배치 후 차지한 자리 채우기
		//uint x = (pos.x + info.leftTopPos[Front].x) / 100;
		//uint y = (pos.y + info.leftTopPos[Front].y) / 100;

		uint x = (pos.x - info.size.x / 2) / 100;
		uint y = (pos.x - info.size.x / 2) / 100;

		for (int i = 0; i < (info.size.y / 100); i++)
		{
			for (int j = 0; j < (info.size.x / 100); j++)
				_map[y][x++] = '0' + static_cast<int>(GameRoomType::MainEntranceRoom) + 1;
			y++;
			//x = (pos.x + info.leftTopPos[Front].x) / 100;
			x = (pos.x - info.size.x / 2) / 100;
		}
		//std::iota(_map[x].begin(), _map[x].begin() + size.x, '0');

		std::vector<DoorRef>& doors = gameRoom->CreateDoors();
		for (const DoorRef door : doors)
			_connectableDoors[door->GetDir()].push_back(door);

		_gameRooms.push_back(gameRoom);
	}

	// 이후 방 절차적 생성
	// 방별 최대 최소 개수 고려 아직X
	//while(conditions.totalGameRoomCount != _gameRooms.size())
	for (int i : std::views::iota(1u, conditions.totalGameRoomCount))
	{
		Dir connectDir;
		while (true)
		{
			// 연결할 방향 선택
			std::discrete_distribution disc({ _roomSpawnChance[Front], _roomSpawnChance[Right], _roomSpawnChance[Back], _roomSpawnChance[Left] });
			connectDir = static_cast<Dir>(disc(gen));
			if (_connectableDoors[connectDir].size() == 0)
				continue;
			break;
		}

		// 연결할 방향에 맞는 문 선택
		std::uniform_int_distribution<int> dist(0, _connectableDoors[connectDir].size() - 1);
		DoorRef door = _connectableDoors[connectDir][dist(gen)];

		// 이전 방이 계단
		//if (prevRoom->GetGameRoomType() == GameRoomType::Staircase)
		
		// 이전 방이 난간 통로 or 복도 => 모든 방 가능
		//if (prevRoom->GetGameRoomType() == GameRoomType::RailCatwalk || prevRoom->GetGameRoomType() == GameRoomType::PipedHallways_Line)
		{
			std::uniform_int_distribution<int> dist1(1, static_cast<int>(GameRoomType::ServerRoom));
			GameRoomType type = static_cast<GameRoomType>(dist1(gen));
			//GameRoomType type = static_cast<GameRoomType>(3);
			GameRoomInfo info = g_dataManager->GetGameRoomInfo(type);

			// 나중에 개수 따지기
			//if (_currentGameRoomCount[info.type] < info.maxCreateCount[_currentDifficulty])

			// 배치할 위치 계산 후 배치 가능한지 판단
			// 연결할 방의 좌표 문 방향에 따라 설정
			uint x{}, y{};
			Vector pos;
			Vector doorPos = door->GetPos();

			// 방의 방향은 문과 반대
			Dir dir = static_cast<Dir>((connectDir + 2) % 4);

			// 소수점때문에 걸릴 수도 있으니 인덱스 한 칸 추가
			switch (dir)
			{
			case Front:
				pos = {doorPos.x + info.enterDistance, doorPos.y + info.size.y / 2, doorPos.z};
				x = (pos.x - info.size.x / 2) / 100;
				y = (pos.y - info.size.y / 2) / 100 + 1;
				break;
			case Right:
				pos = { doorPos.x + info.size.x / 2, doorPos.y + info.enterDistance, doorPos.z };
				x = (pos.x - info.size.y / 2) / 100 - 1;
				y = (pos.y - info.size.x / 2) / 100;
				break;
			case Back:
				pos = { doorPos.x - info.enterDistance, doorPos.y - info.size.y / 2, doorPos.z };
				x = (pos.x - info.size.x / 2) / 100;
				y = (pos.y - info.size.y / 2) / 100 - 1;
				break;
			case Left:
				pos = { doorPos.x - info.size.x / 2, doorPos.y - info.enterDistance, doorPos.z };
				x = (pos.x - info.size.y / 2) / 100 + 1;
				y = (pos.y - info.size.x / 2) / 100;
				break;
			}

			// 방을 배치할 자리가 있는지 확인
			//x += (pos.x + info.leftTopPos[dir].x) / 100;
			//y += (pos.y + info.leftTopPos[dir].y) / 100;

			bool isCreate = true;

			// STL로 변경할 것
			switch (dir)
			{
			case Front:
			case Back:
				for (int i = 0; i < (info.size.y / 100); i++)
				{
					for (int j = 0; j < (info.size.x / 100); j++)
					{
						// 배치할 공간이 없음, 방 종류 변경 나중에 처리
						if (_map[y][x++] != '0')
						{
							isCreate = false;
							break;
						}
					}

					y++;
					x = (pos.x - info.size.x / 2) / 100;
				}
				break;
			case Right:
			case Left:
				for (int i = 0; i < (info.size.x / 100); i++)
				{
					for (int j = 0; j < (info.size.y / 100); j++)
					{
						// 배치할 공간이 없음, 방 종류 변경 나중에 처리
						if (_map[y][x++] != '0')
						{
							isCreate = false;
							break;
						}
					}

					y++;
					x = (pos.x - info.size.y / 2) / 100;

					if (dir == Right)
						x += -1;
					else if (dir == Left)
						x += 1;
				}
				break;
			}

			// 배치 가능하면 방 생성 후 배치 기록
			if (isCreate)
			{
				GameRoomRef gameRoom = std::make_shared<GameRoom>();
				gameRoom->SetGameRoomInfo(info);
				gameRoom->SetPos(pos);
				gameRoom->SetDir(dir);

				// 방과 연결된 문은 제외
				door->SetConnectable(false);
				_connectableDoors[connectDir].erase(std::remove(_connectableDoors[connectDir].begin(), _connectableDoors[connectDir].end(), door), _connectableDoors[connectDir].end());

				//x = (pos.x + info.leftTopPos[dir].x) / 100;
				//y = (pos.y + info.leftTopPos[dir].y) / 100;

				switch (dir)
				{
				case Front:
					x = (pos.x - info.size.x / 2) / 100;
					y = (pos.y - info.size.y / 2) / 100 + 1;
					break;
				case Right:
					x = (pos.x - info.size.y / 2) / 100 - 1;
					y = (pos.y - info.size.x / 2) / 100;
					break;
				case Back:
					x = (pos.x - info.size.x / 2) / 100;
					y = (pos.y - info.size.y / 2) / 100 - 1;
					break;
				case Left:
					x = (pos.x - info.size.y / 2) / 100 + 1;
					y = (pos.y - info.size.x / 2) / 100;
					break;
				}

				switch (dir)
				{
				case Front:
				case Back:
					for (int i = 0; i < (info.size.y / 100); i++)
					{
						for (int j = 0; j < (info.size.x / 100); j++)
							_map[y][x++] = '0' + (static_cast<int>(type) + 1);
						y++;
						x = (pos.x - info.size.x / 2) / 100;
					}
					break;
				case Right:
				case Left:
					for (int i = 0; i < (info.size.x / 100); i++)
					{
						for (int j = 0; j < (info.size.y / 100); j++)
							_map[y][x++] = '0' + (static_cast<int>(type) + 1);
						y++;
						x = (pos.x - info.size.y / 2) / 100;

						if (dir == Right)
							x += -1;
						else if (dir == Left)
							x += 1;
					}
					break;
				}

				_gameRooms.push_back(gameRoom);

				// 문 생성
				std::vector<DoorRef>& doors = gameRoom->CreateDoors();
				for (const DoorRef door : doors)
					_connectableDoors[door->GetDir()].push_back(door);
			
				// 방 배치 임시 확인용 출력 (추후 삭제 예정)
				for (int i = 0; i < Height; i++)
				{
					for (int j = 0; j < Width; j++)
						std::cout << _map[i][j];
					std::cout << std::endl;
				}
			}
		}

		// 그 외
	}

	// 아이템 생성

	// 추후 다시 사용할 예정
	//g_framework->SendCreateGameRoomPacket(_gameRooms, true);
}

GameObjectRef Room::AddObject(ObjectType type)
{
	GameObjectRef object;

	switch (type)
	{
	case ObjectType::Player:
		_players[_generatePlayerID] = std::make_shared<Player>();
		object = _players[_generatePlayerID];
		// temp
		Vector pos = object->GetPos();
		pos.x += _playerCount * 100;
		object->SetPos(pos);
		_playerCount++;
		break;
	}

	object->SetID(_generatePlayerID++);

	g_framework->SendAddObjectPacket(object, true);

	return object;
}