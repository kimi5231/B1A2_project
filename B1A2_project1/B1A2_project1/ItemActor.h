#pragma once
#include "ItemActor.h"
#include "SpriteActor.h"

class Sprite;
class Player;
class Item;

class ItemActor : public SpriteActor
{
	using Super = SpriteActor;

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
	//Sprite* _spriteItemInInven = {};
	//Sprite* _spriteItemInInvenEffect = {};
};

