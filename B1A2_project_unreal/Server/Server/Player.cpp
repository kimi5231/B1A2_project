#include "pch.h"
#include "Player.h"

Player::Player()
{
	_pos = { Width / 2 * 10, Height / 2 * 10, 100 };
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Player;
}

Player::~Player()
{
}

void Player::Update()
{

}