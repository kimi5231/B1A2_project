#pragma once
#include "Monster.h"
#include "Stat.h"

class BoxCollider;

class BrokenCopyMachine : public Monster
{
	using Super = Monster;
public:
	BrokenCopyMachine();
	virtual ~BrokenCopyMachine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickLongAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) {};

	void AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2);

public:
	virtual float GetSpeed() override;
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual Vec2Int GetPlayerDetection() { return {0, 0}; };

private:
	void CalPixelPerSecond();

	void CreateProjectile();

private:
	// Flipbook
	Flipbook* _flipbookIdle[2]{};
	Flipbook* _flipbookLongAttack[2]{};
	Flipbook* _flipbookHit[2]{};
	Flipbook* _flipbookDead[2]{};

private:
	BrokenCopyMachineStat* _stat;

	BoxCollider* _collider;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;
};