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

	// _acquiredItens에 Player가 획득한 아이템 저장
	void SaveAcquireItems();

	// Render
	void InventoryBackgroundRender(HDC hdc);
	void InventoryItemRender(HDC hdc);
	void ClickedItemPhotoRender(HDC hdc);
	void ClickedItemExplainRender(HDC hdc);


public:
	// 마우스 입력
	std::vector<RECT> _itemBoxes;	// 클릭 영역 확인
	void MouseClick(POINT mousePos);
	int32 _clickedItemID = 0;

private:
	Player* _owner = {};

	// Inventory 창 
	InventoryState _inventoryState = InventoryState::Hidden;

	// 획득한 아이템
	std::unordered_map<int32, int32> _acquiredItems;

	// csv에서 읽어온 정보
	Item* _itemList;
	// [ID, itemInfo]
	std::unordered_map<int32, ItemInfo*> _itemInfo;
};

