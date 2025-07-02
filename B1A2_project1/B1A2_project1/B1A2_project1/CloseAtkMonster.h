#pragma once
#include "Monster.h"

class BoxCollider;

struct CloseAtkMonsterStat
{
	int32 hp = 100;
	float healtemDropRate = 0.3f;
	float speed = 10.f;
	float chaseSpeed = 15.f;
	Vec2Int playerDetection = { 240, 80 };
	int32 knockBackDistance = 65;
	Vec2Int attackRange = {45, 80};
	int32 attack = 20;
	float idleTime = 1.f;
};

class CloseAtkMonster : public Monster
{
	using Super = Monster;
public:
	CloseAtkMonster();
	virtual ~CloseAtkMonster() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickCloseAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void TickChase() override;
	virtual void TickRoaming() override;
	virtual void TickReturn() override;
	virtual void TickReturnIdle() override;
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
	virtual Vec2Int GetPlayerDetection() override { return _stat->playerDetection; };

private:
	void CalPixelPerSecond();

private:
	// Flipbook
	Flipbook* _flipbookIdle[2];
	Flipbook* _flipbookCloseAttack[2];
	Flipbook* _flipbookHit[2];
	Flipbook* _flipbookDead[2];
	Flipbook* _flipbookChase[2];
	Flipbook* _flipbookRoaming[2];
	Flipbook* _flipbookReturn[2];
	Flipbook* _flipbookReturnIdle[2];

private:
	CloseAtkMonsterStat* _stat;
	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;

	BoxCollider* _collider;
	Collider* _detectCollider;
	Collider* _attackCollider = nullptr;

	float _sumTime = 0.f;
	float _creationTime = 0.f;
};

