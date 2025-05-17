#pragma once
#include "Component.h"

class Item;
class Flipbook;
class Player;
struct ItemInfo;

enum ITEM_SIZE
{
	ITEM_STARTX = 560,
	ITEM_STARTY = 165,

	ITEM_SIZEX = 128,
	ITEM_SIZEY = 128,
};

enum InventoryItemState
{
	Default,
	Clicked,
};

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

	// _acquiredItens�� Player�� ȹ���� ������ ����
	void SaveAcquireItems();

	// Render
	void InventoryBackgroundRender(HDC hdc);
	void InventoryItemRender(HDC hdc);
	void ClickedItemPhotoRender(HDC hdc);
	void ClickedItemExplainRender(HDC hdc);


public:
	// ���콺 �Է�
	std::vector<RECT> _itemBoxes;	// Ŭ�� ���� Ȯ��
	void MouseClick(POINT mousePos);
	int32 _clickedItemID = 0;

private:
	Player* _owner = {};

	// Inventory â 
	InventoryState _inventoryState = InventoryState::Hidden;

	// ȹ���� ������
	std::unordered_map<int32, int32> _acquiredItems;

	// csv���� �о�� ����
	Item* _itemList;
	// [ID, itemInfo]
	std::unordered_map<int32, ItemInfo*> _itemInfo;
};

