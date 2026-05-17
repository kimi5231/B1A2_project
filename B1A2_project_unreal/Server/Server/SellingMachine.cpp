#include "pch.h"
#include "SellingMachine.h"

SellingMachine::SellingMachine(Dir dir, bool isSpecial)
	: _dir(dir), _isSpecial(isSpecial)
{
	_type = ObjectType::SellingMachine;
}

SellingMachine::~SellingMachine()
{
}

bool SellingMachine::RemoveItem(int itemID)
{
	auto it = std::find(_sellItem.begin(), _sellItem.end(), itemID);
	if (it != _sellItem.end())
	{
		_sellItem.erase(it);
		return true;
	}

	return false;
}