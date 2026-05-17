#include "pch.h"
#include "Scrap.h"

Scrap::Scrap(ItemType itemType, int cost)
	: Item(itemType), _cost(cost)
{
}

Scrap::~Scrap()
{
}