#pragma once
#include "Component.h"

class Item;
class Flipbook;
class Player;

class Inventory : public Component
{
	using Super = Component;

public:
	Inventory();
	virtual ~Inventory() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

public:
	InventoryState GetInventoryState() { return _inventoryState; }
	void SetInventoryState(InventoryState state) { _inventoryState = state; }

	Player* GetOwner() { return _owner; }
	void SetOwner(Player* owner) { _owner = owner; }

	// _items�� Player�� ȹ���� ������ ����
	void SaveAcquireItems();
	
private:
	Player* _owner = {};

	// Inventory â 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook (ȿ���� ����..)
	Flipbook* _flipbookKey = {};	
	Flipbook* _flipbookPencil = {};
	Flipbook* _flipbookMatch = {};

	std::unordered_map<int32, int32> _acquiredItems;
};

