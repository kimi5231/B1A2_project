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
	void SetOwnerID(int id) { _ownerID = id; }
	int GetOwnerID() { return _ownerID; }

protected:
	ItemType _itemType;
	float _weight;
	int _ownerID;
};