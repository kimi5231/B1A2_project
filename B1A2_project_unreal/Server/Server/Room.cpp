#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "Global.h"
#include "ServerFramework.h"

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

	return object;
}