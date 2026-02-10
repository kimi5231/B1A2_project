#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item(ItemType itemType);
	virtual ~Item();

public:
	virtual void Update();

private:
	ItemType _itemType;
};