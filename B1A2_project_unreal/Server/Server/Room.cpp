#include "pch.h"
#include "Room.h"
#include "Global.h"
#include "GameRoom.h"

Room::Room()
{
	_generatePlayerID = 1;
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

	for (int i = 0; i < _gameRooms.size(); i++)
	{
		GameRoomRef gameRoom = std::make_shared<GameRoom>();
		gameRoom->SetGameRoomType(static_cast<GameRoomType>(dist1(gen)));

		// 방 위치 계산
		if (i == 0)
			gameRoom->SetPos({ 0, 0, 300 });
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

		_gameRooms[i] = gameRoom;
	}

	g_framework->SendCreateGameRoomPacket(_gameRooms, true);
}

GameObjectRef Room::AddObject(ObjectType type)
{
	GameObjectRef object;

	switch (type)
	{
	case ObjectType::Player:
		_players[_generatePlayerID] = std::make_shared<Player>();
		object = _players[_generatePlayerID];
		break;
	}

	object->SetID(_generatePlayerID++);

	g_framework->SendAddObjectPacket(object, true);

	CreateGameRoom();

	return object;
}