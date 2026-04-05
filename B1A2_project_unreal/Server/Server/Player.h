#pragma once
#include "Creature.h"

class Inventory;
class Room;

class Player : public Creature
{
public: 
	Player();
	virtual ~Player();

public:
	virtual void Update();

public:
	bool AddItemToInventory(bool isTool, int id);
	bool RemoveItemFromInventory(bool isTool, int id);
	bool ExistItem(bool isTool, int id);

	void Attack(Room* room);

public:
	int GetCurrentTool() { return _currentTool; }
	void SetCurrentTool(int toolID) { _currentTool = toolID; }

private:
	Inventory* _inventory{};
	int _currentTool{};
};