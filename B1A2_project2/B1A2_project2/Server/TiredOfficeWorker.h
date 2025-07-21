#pragma once
#include "Monster.h"

class TiredOfficeWorker : public Monster
{
	using Super = Monster;
public:
	TiredOfficeWorker();
	virtual ~TiredOfficeWorker();

	virtual void Update();

public:
	virtual void UpdateIdle() override;
	virtual void UpdateCloseAttack() override;
	virtual void UpdateHit() override;
	virtual void UpdateDead() override;
	virtual void UpdateChase() override;
	virtual void UpdateRoaming() override;
	virtual void UpdateReturn() override;
	virtual void UpdateReturnIdle() override;

public:
	void SetTiredOfficeWorkerStat(TiredOfficeWorkerStat* stat) { _stat = stat; }
	void SetMovingDistance(float dis) { _moveDistance = dis; }
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

private:
	TiredOfficeWorkerStat* _stat;
	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;

	std::weak_ptr<Player> _target;

	float _sumTime = 0.f;
};