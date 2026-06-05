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

std::vector<Room*>& ServerFramework::GetWaitingRooms()
{
	std::vector<Room*> runningRooms;
	for (int i = 0; i < MAX_ROOM; ++i)
	{
		if (_rooms[i]->GetRoomState() == RoomState::Wait)
			runningRooms.push_back(_rooms[i]);
	}

	return runningRooms;
}