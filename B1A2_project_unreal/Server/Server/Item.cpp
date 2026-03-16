#include "pch.h"
#include "Item.h"

Item::Item(ItemType itemType)
	: _itemType(itemType)
{
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Item;
	_weight = 0.1;
}

Item::~Item()
{
}

void Item::Update()
{
}