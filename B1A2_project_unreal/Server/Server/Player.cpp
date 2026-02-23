#include "pch.h"
#include "Player.h"

Player::Player()
{
	_pos = { 0, 0, 100 };
	_rotation = {0, 0, 0};
	_type = ObjectType::Player;
	_box.SetRanges({ _pos.x - 30,  _pos.y - 30,  _pos.z }, { _pos.x + 30,  _pos.y + 30,  _pos.z + 180 });
}

Player::~Player()
{
}

void Player::Update()
{

}