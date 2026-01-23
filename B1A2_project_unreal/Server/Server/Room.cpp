#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "GameRoom.h"

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

void Room::CreateGameRoom()
{
	// 랜덤으로 방 생성 (일단은 절차적 생성 알고리즘 고려X)
	std::uniform_int_distribution<int> dist1(0, static_cast<int>(GameRoomType::FactoryRoom));
	std::uniform_int_distribution<int> dist2(0, 3);

	for (int i = 0; i < 5; i++)
	{
		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		gameRoom->SetGameRoomType(static_cast<GameRoomType>(dist1(gen)));

		// 방 위치 계산
		if (i == 0)
			gameRoom->SetPos({ 0, 0, 500 });
		else
		{
			Vector prevRoomPos = _gameRooms[i - 1]->GetPos();
			switch (dist2(gen))
			{
			case 0: // 앞
				prevRoomPos.x += 500;
				gameRoom->SetPos(prevRoomPos);
				break;
			case 1: // 뒤
				prevRoomPos.x -= 500;
				gameRoom->SetPos(prevRoomPos);
				break;
			case 2: // 좌
				prevRoomPos.y -= 500;
				gameRoom->SetPos(prevRoomPos);
				break;
			case 3: // 우
				prevRoomPos.y += 500;
				gameRoom->SetPos(prevRoomPos);
				break;
			}
		}

		_gameRooms.push_back(gameRoom);
	}

	// 추후 다시 사용할 예정
	//g_framework->SendCreateGameRoomPacket(_gameRooms, true);
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

	// 방 생성(문은 방 안에서 생성 + 비상구)
	// MainEntranceRoom 생성
	{
		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		gameRoom->SetGameRoomInfo(g_dataManager->GetGameRoomInfo(GameRoomType::MainEntranceRoom));
		Vector size = gameRoom->GetSize();
		// 1층에 배치
		Vector pos{ (Width / 2 * 100) - size.x / 2, 0, 0 };
		gameRoom->SetPos(pos);
		gameRoom->SetDir(Dir::Front);

		// 방 배치 후 차지한 자리 채우기 
		uint x = pos.x / 100;
		uint y = pos.y / 100;
		
		for (int i = 0; i < (size.x/100); i++)
		{
			for (int j = 0; j < (size.y / 100); j++)
				_map[x][y++] = '■';
			x++;
			y = 0;
		}
		//std::iota(_map[x].begin(), _map[x].begin() + size.x, '0');

		std::vector<DoorRef>& doors = gameRoom->CreateDoors();
		_connectableDoors.insert(_connectableDoors.end(), doors.begin(), doors.end());
		_gameRooms.push_back(gameRoom);
	}

	for (int i : std::views::iota(1u, conditions.totalGameRoomCount))
	{
		// 이전 방이 뭔지 확인
		GameRoomRef prevRoom = _gameRooms[i - 1];

		// 이전 방이 계단
		if (prevRoom->GetGameRoomType() == GameRoomType::Staircase)
		{
			break;
		}
		
		// 이전 방이 난간 통로 or 복도 => 모든 방 가능
		if (prevRoom->GetGameRoomType() == GameRoomType::RailCatwalk || prevRoom->GetGameRoomType() == GameRoomType::PipedHallways_Line)
		{
			std::uniform_int_distribution<int> dist1(0, static_cast<int>(GameRoomType::FactoryRoom));
			GameRoomInfo info = g_dataManager->GetGameRoomInfo(static_cast<GameRoomType>(dist1(gen)));
			
			//
			if (_currentGameRoomCount[info.type] < info.maxCreateCount[_currentDifficulty])
			{
				GameRoomRef gameRoom = std::make_shared<GameRoom>();
				gameRoom->SetGameRoomInfo(info);
				gameRoom->SetPos({ 0, 0 });
			}

			break;
		}

		// 그 외
		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		
	}

	// 아이템 생성
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