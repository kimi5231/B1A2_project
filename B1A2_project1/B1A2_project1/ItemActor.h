#pragma once
#include "ItemActor.h"
#include "FlipbookActor.h"

class Player;
class Item;

class ItemActor : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	ItemActor(ItemType itemType);
	virtual ~ItemActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	// Collider - ������ ���� ���� ������ FŰ ���� (ƨ��� X)
	virtual void OnConponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

protected:
	Player* _owner = nullptr;

private:
	// Item ���ҽ�
	Flipbook* _flipbookItemInMap = {};
	Flipbook* _flipbookItemInInven = {};
	Flipbook* _flipbookItemInInvenEffect = {};
};

