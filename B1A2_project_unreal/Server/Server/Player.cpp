#include "pch.h"
#include "Player.h"

Player::Player()
{
	_pos = { 0, 0, 100 };
	_rotation = {0, 0, 0};
	_type = ObjectType::Player;
	_box.SetBounds(_pos, {60, 30, 180}, Front);
}

Player::~Player()
{
}

void Player::Update()
{

}