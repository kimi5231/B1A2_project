#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"

ServerFramework::ServerFramework()
{
	// Room 미리 생성
	for (int i = 0; i < MAX_ROOM; ++i)
	{
		_rooms[i] = new Room();
		_rooms[i]->Init();
	}
}

ServerFramework::~ServerFramework()
{
	for (int i = 0; i < MAX_ROOM; ++i)
		delete _rooms[i];
}

void ServerFramework::Update()
{
	for (int i = 0; i < MAX_ROOM; ++i)
	{
		if (_rooms[i]->GetRoomState() != RoomState::Reusable)
			_rooms[i]->Update();
	}
}

Room* ServerFramework::AddRoom(std::vector<char>& title)
{
	for (int i = 0; i < MAX_ROOM; ++i)
	{
		if (_rooms[i]->GetRoomState() == RoomState::Reusable)
		{
			_rooms[i]->SetRoomState(RoomState::Wait);
			_rooms[i]->SetTitle(title);
			return _rooms[i];
		}
	}

	return nullptr;
}

void ServerFramework::RemoveRoom(int id)
{
	// 초기화 및 RoomState 변경
	_rooms[id]->SetCollectCredit(0);
	_rooms[id]->EndStage();
	_rooms[id]->SetRoomState(RoomState::Reusable);
}