#include "pch.h"
#include "Item.h"

Item::Item(ItemType itemType)
	: _itemType(itemType)
{
	_pos = { Width / 2 * 10 + 200, Height / 2 * 10, 100 };
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Item;
}

Item::~Item()
{
}

void Item::Update()
{
}