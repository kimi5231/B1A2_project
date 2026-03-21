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
	void SetItemType(ItemType type);
	ItemType GetItemType() { return _itemType; }
	float GetWeight() { return _weight; }

protected:
	ItemType _itemType;
	float _weight;
};