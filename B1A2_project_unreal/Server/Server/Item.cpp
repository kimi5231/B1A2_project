#include "pch.h"
#include "Item.h"

Item::Item(ItemType itemType)
	: _itemType(itemType)
{
	_pos = { 0, -100, 10};
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Item;
}

Item::~Item()
{
}

void Item::Update()
{
}