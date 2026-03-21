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

private:
	Inventory* _inventory;
};