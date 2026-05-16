#include "pch.h"
#include "ServerFramework.h"
#include "Room.h"

ServerFramework::ServerFramework()
{
	// Room »ý¼º
	_room = new Room();
	_room->Init();
}

ServerFramework::~ServerFramework()
{
	delete _room;
}

void ServerFramework::Update()
{
	_room->Update();
}