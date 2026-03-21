#include "pch.h"
#include "Player.h"
#include "Item.h"
#include "Inventory.h"

Player::Player()
{
	_pos = { 0, 0, 25 };
	_rotation = {0, 0, 0};
	_type = ObjectType::Player;
	_box.SetBounds(_pos, {60, 30, 180}, Front);
	_inventory = new Inventory();
}

Player::~Player()
{
}

void Player::Update()
{

}

bool Player::AddItemToInventory(bool isTool, uint id)
{
	return _inventory->AddItem(isTool, id);
}

bool Player::RemoveItemFromInventory(bool isTool, uint id)
{
	return _inventory->RemoveItem(isTool, id);
}