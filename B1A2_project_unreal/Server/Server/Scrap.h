#pragma once
#include "Item.h"

class Scrap : public Item
{
public:
	Scrap(ItemType itemType, int cost);
	~Scrap();

public:
	int GetCost() { return _cost; }

private:
	int _cost;
};