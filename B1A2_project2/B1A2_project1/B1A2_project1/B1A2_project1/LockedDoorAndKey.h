#pragma once
#include "Structure.h"

class LockedDoorAndKey : public Structure
{
	using Super = Structure;
public:
	LockedDoorAndKey();
	virtual ~LockedDoorAndKey() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetDoorPos(Vec2 pos) { _doorPos = pos; }
	Vec2 GetDoorPos() { return _doorPos; }
	void SetItemPos(Vec2 pos) { _itemPos = pos; }
	Vec2 GetItemPos() { return _itemPos; }

private:
	Flipbook* _flipbookLockedDoor = nullptr;
	Flipbook* _flipbookUnlockedDoor = nullptr;
	Flipbook* _flipbookKey = nullptr;

	Vec2 _doorPos;
	Vec2 _itemPos;

public:
	bool _isKeyAcquired = false;
	bool _isOperateKey = false;
};

