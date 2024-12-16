#pragma once
#include "Component.h"

class Item;
class Flipbook;

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

	void GetPlayerOwnItems();	// _items�� ����
	
private:
	// Inventory â 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook (ȿ���� ����..)
	Flipbook* _flipbookKey = {};	
	Flipbook* _flipbookPencil = {};
	Flipbook* _flipbookMatch = {};

	std::vector<std::wstring> _items;	// Player�� ������ �ִ� �������� ���� ����
};

