#include "pch.h"
#include "Player.h"
#include "Item.h"

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

void Player::AddItemToInventory(ItemRef item, bool isTool)
{
	if (isTool)
	{
		// 도구 인벤토리에 넣기
	}
	else
	{
		// 아이템 인벤토리에 넣기
	}

	SetState(ObjectState::GET_ITEM);
}