#pragma once
#include "GameObject.h"

class SellingMachine : public GameObject
{
public:
	SellingMachine(Dir dir, bool isSpecial, int creditLimit);
	~SellingMachine();

public:
	void AddItem(int itemID) { _sellItems.push_back(itemID); }
	bool RemoveItem(int itemID);
	void ClearSellItems() { _sellItems.clear(); }
	int SellItem(Room* room);

public:
	Dir GetDir() { return _dir; }
	int GetCreditLimit() { return _creditLimit; }
	int GetRemainCreditLimit() { return _remainCreditLimit; }
	std::vector<int>& GetSellItems() { return _sellItems; }

private:
	Dir _dir{};
	bool _isSpecial{};
	int _creditLimit;
	int _remainCreditLimit;
	std::vector<int> _sellItems;
};