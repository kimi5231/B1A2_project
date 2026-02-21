#include "pch.h"
#include "Player.h"

Player::Player()
{
	_pos = { 0, 0, 100 };
	_rotation = {0, 0, 0};
	_type = ObjectType::Player;
}

Player::~Player()
{
}

void Player::Update()
{

}