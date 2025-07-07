#pragma once
#include "Monster.h"
#include "Stat.h"

class BoxCollider;

class TiredOfficeWorker : public Monster
{
	using Super = Monster;
public:
	TiredOfficeWorker();
	virtual ~TiredOfficeWorker() override;

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
	virtual void TickRETURN_IDLE() override;
	virtual void UpdateAnimation() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

	void AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2);

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
	Flipbook* _flipbookRETURN_IDLE[2];

private:
	TiredOfficeWorkerStat* _stat;
	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;

	BoxCollider* _collider = nullptr;
	Collider* _detectCollider = nullptr;
	Collider* _attackCollider = nullptr;

	float _sumTime = 0.f;
};