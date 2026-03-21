#include "pch.h"
#include "Item.h"

Item::Item(ItemType itemType)
{
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Item;
	SetItemType(itemType);
}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::SetItemType(ItemType type)
{
	_itemType = type;

	// 타입에 맞춰서 무게 설정하기
	_weight = 0.1;
}