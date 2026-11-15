#include "pch.h"
#include "Item.h"
#include "Global.h"

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

	ItemInfo info = g_dataManager->GetItemInfo(type);

	_size = info.size;
	_weight = info.weight;
	_cost = info.cost;
}