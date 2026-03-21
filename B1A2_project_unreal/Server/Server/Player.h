#pragma once
#include "GameObject.h"

class Inventory;

class Player : public GameObject
{
public: 
	Player();
	virtual ~Player();

public:
	virtual void Update();

public:
	bool AddItemToInventory(bool isTool, uint id);
	bool RemoveItemFromInventory(bool isTool, uint id);
	bool ExistItem(bool isTool, uint id);

public:
	void SetCurrentTool(uint toolID) { _currentTool = toolID; }
	uint GetCurrentTool() { return _currentTool; }

private:
	Inventory* _inventory{};
	uint _currentTool{};
};