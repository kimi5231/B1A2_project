#pragma once
#include "Monster.h"

class BoxCollider;

struct LongAtkMonsterStat
{
	int32 hp = 100;	
	float speed = 50.f;
	float healtemDropRate = 0.2f;	
	int32 attackRange = 480;	
	float projectileSpeed = 7.f;	
	int32 projectileAttack = 5;
	int32 projectileCount = 9;	
	float attackCoolTime = 3.0f;	
};

class LongAtkMonster : public Monster
{
	using Super = Monster;
public:
	LongAtkMonster();
	virtual ~LongAtkMonster() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickLongAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetSpawnPos(Vec2 pos);
	void SetSpawnDir(Dir dir);
	void SetMoveDistance(float distance);
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

public:
	virtual float GetSpeed() override;
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual Vec2Int GetPlayerDetection() { return { 0, 0 }; };

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
	LongAtkMonsterStat* _stat;
	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;
	float _creationTime = 0.f;
	float _changeDirTime = 0.f;

	BoxCollider* _collider;
};

