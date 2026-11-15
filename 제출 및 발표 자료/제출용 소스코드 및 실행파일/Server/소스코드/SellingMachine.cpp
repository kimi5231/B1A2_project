#include "pch.h"
#include "SellingMachine.h"
#include "Room.h"
#include "Item.h"

SellingMachine::SellingMachine(Dir dir, bool isSpecial, int creditLimit)
	: _dir(dir), _isSpecial(isSpecial), _creditLimit(creditLimit), _remainCreditLimit(creditLimit)
{
	_type = ObjectType::SellingMachine;
}

SellingMachine::~SellingMachine()
{
}

bool SellingMachine::RemoveItem(int itemID)
{
	auto it = std::find(_sellItems.begin(), _sellItems.end(), itemID);
	if (it != _sellItems.end())
	{
		_sellItems.erase(it);
		return true;
	}

	return false;
}

bool SellingMachine::ExistItem(int itemID)
{
	auto it = std::find(_sellItems.begin(), _sellItems.end(), itemID);
	return it != _sellItems.end();
}

int SellingMachine::SellItem(Room* room)
{
	const std::array<Item*, MAX_ITEM>& items = room->GetItems();

	// 판매기에 올려져 있는 아이템의 총 가격 계산
	int credit = 0;
	for (auto& sellItem : _sellItems)
		credit += items[sellItem]->GetCost();
	
	if (credit >= _remainCreditLimit)
	{
		_remainCreditLimit = 0;
		room->PlusCredit(_remainCreditLimit);
		_state = ObjectState::CLOSE;
		return _remainCreditLimit;
	}
		
	room->PlusCredit(credit);
	_remainCreditLimit -= credit;
	return _remainCreditLimit;
}