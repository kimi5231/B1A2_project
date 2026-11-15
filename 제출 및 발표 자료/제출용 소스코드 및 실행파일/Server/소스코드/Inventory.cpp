#include "pch.h"
#include "Inventory.h"

Inventory::Inventory()
{
	_maxScrapCount = 25;
	_maxToolCount = 4;
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{
	_scraps.clear();
	_tools.clear();
}

bool Inventory::AddItem(bool isTool, int id)
{
	if (isTool && _tools.size() < _maxToolCount)
	{
		auto result = _tools.insert(id);
		return result.second;
	}

	if (!isTool && _scraps.size() < _maxScrapCount)
	{
		auto result = _scraps.insert(id);
		return result.second;
	}
}

bool Inventory::RemoveItem(bool isTool, int id)
{
	if (isTool)
		return _tools.erase(id);
	else
		return _scraps.erase(id);
}

bool Inventory::ExistItem(bool isTool, int id)
{
	if (isTool)
		return _tools.count(id);
	else
		return _scraps.count(id);
}