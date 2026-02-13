#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item(ItemType itemType);
	virtual ~Item();

public:
	virtual void Update();

public:
	ItemType GetItemType() { return _itemType; }

private:
	ItemType _itemType;
};