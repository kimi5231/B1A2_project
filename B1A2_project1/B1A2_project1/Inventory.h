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

	void SavePlayerOwnItems();	// _items�� ����
	
private:
	// Inventory â 
	InventoryState _inventoryState = InventoryState::Hidden;

	// Item Flipbook
	Flipbook* _flipbookKey[2] = {};		// [�⺻, ȿ��]
	Flipbook* _flipbookPencil[2] = {};
	Flipbook* _flipbookMatch[2] = {};

	std::vector<std::wstring> _items;	// Player�� ������ �ִ� �������� ���� ����
};

