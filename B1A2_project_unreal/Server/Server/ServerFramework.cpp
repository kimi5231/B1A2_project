#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"
#include "Global.h"
#include "Session.h"

ServerFramework::ServerFramework()
{
	_updateLobbyTime = 0.f;

	// Room 미리 생성
	for (int i = 0; i < MAX_ROOM; ++i)
	{
		_rooms[i] = new Room();
		_rooms[i]->SetID(i);
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
	// 5초에 한 번씩 RoomList Update
	_updateLobbyTime += g_timer->GetDeltaTime();
	if (_updateLobbyTime > 5)
	{
		_updateLobbyTime = 0;
		for (const auto& [id, client] : _lobbyClients)
			g_network->SendCurrentRoomListPacket(client);
	}

	for (int i = 0; i < MAX_ROOM; ++i)
	{
		if (_rooms[i]->GetRoomState() == RoomState::Play)
			_rooms[i]->Update();
	}
}

void ServerFramework::AddLobbyClient(Session* session)
{
	_lobbyClients[session->_id] = session;
}

void ServerFramework::RemoveLobbyClient(int id)
{
	_lobbyClients.erase(id);
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