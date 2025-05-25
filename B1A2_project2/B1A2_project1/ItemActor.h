#pragma once
#include <unordered_map>
#include "ItemActor.h"
#include "FlipbookActor.h"
#include "Item.h"

class Player;
class Collider;

class ItemActor : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	ItemActor(int32 itemID, const std::unordered_map<int32, ItemInfo*>& items);
	virtual ~ItemActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	int32 GetItemID() { return _itemInfo->ID; }
	void SetItemID(int32 id) { _itemInfo->ID = id; }

	Player* GetOwner() { return _owner; }
	void SetOwner(Player* player) { _owner = player; }

	ItemInfo* GetItemInfo() { return _itemInfo; }

public:
	void SetFKeyState(FKeyState state) { _FkeyState = state; }
	FKeyState GetFKeyState() { return _FkeyState; }

	void SetItemState(ItemState state) { _itemState = state; }
	ItemState GetItemState() { return _itemState; }

	int32 GetItemId() { return _itemInfo->ID; }

	// 아이템 삭제 위해
	Collider* GetCollider() const;
protected:
	Player* _owner = nullptr;

private:
	ItemInfo* _itemInfo = nullptr;

	Flipbook* _flipbookItemInMap = {};
	Flipbook* _flipbookFKey = {};

private:
	FKeyState _FkeyState = FKeyState::Hidden;
	ItemState _itemState = ItemState::Show;
};

