#include "pch.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

bool Inventory::AddItem(bool isTool, uint id)
{
	// 나중에 인벤 최대 크기 + 무게 고려하기
	if (isTool)
	{
		_tools.push_back(id);
		return true;
	}
	else
	{
		_scraps.push_back(id);
		return true;
	}

	return false;
}

bool Inventory::RemoveItem(bool isTool, uint id)
{
	if (isTool)
	{
		// 해당 아이템이 존재하는지 확인 후, 존재하면 삭제
		auto it = std::find(_tools.begin(), _tools.end(), id);
		if (it != _tools.end())
		{
			_tools.erase(it);
			return true;
		}
	}
	else
	{
		auto it = std::find(_scraps.begin(), _scraps.end(), id);
		if (it != _scraps.end())
		{
			_scraps.erase(it);
			return true;
		}
	}

	return false;
}

bool Inventory::ExistItem(bool isTool, uint id)
{
	if (isTool)
	{
		auto it = std::find(_tools.begin(), _tools.end(), id);
		return it != _tools.end();
	}
	else
	{
		auto it = std::find(_scraps.begin(), _scraps.end(), id);
		return it != _tools.end();
	}
}