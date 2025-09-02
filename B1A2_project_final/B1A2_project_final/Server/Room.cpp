#include "pch.h"
#include "Room.h"
#include "Player.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::Update()
{

}

void Room::AddPlayer()
{
	std::shared_ptr<Player> player = std::make_shared<Player>();
	
	_players[1] = player;
}