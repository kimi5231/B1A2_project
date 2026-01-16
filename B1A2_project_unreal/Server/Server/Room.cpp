#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "GameRoom.h"

Room::Room()
{
	_generatePlayerID = 1;

	_currentDifficulty = Difficulty::Easy;
	_detailDifficulty = Difficulty::Easy;

	CreateGameRoom();
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
	std::uniform_int_distribution<int> dist1(0, static_cast<int>(GameRoomType::StorageRoom));
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

void Room::CreateFactoryGameRoom()
{
	// 난이도에 맞춰 조건 설정

	// 방 생성(문은 방 안에서 생성 + 비상구)
	for (int i : std::views::iota(0, _gameRoomCount))
	{

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