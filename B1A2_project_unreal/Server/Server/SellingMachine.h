#pragma once
#include "GameObject.h"

class SellingMachine : public GameObject
{
public:
	SellingMachine(Dir dir, bool isSpecial);
	~SellingMachine();

public:
	void AddItem(int itemID) { _sellItem.push_back(itemID); }
	bool RemoveItem(int itemID);

public:
	Dir GetDir() { return _dir; }

private:
	Dir _dir{};
	bool _isSpecial{};
	std::vector<int> _sellItem;
};