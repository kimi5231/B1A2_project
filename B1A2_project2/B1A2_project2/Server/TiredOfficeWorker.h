#pragma once
#include "Monster.h"

class TiredOfficeWorker : public Monster
{
public:
	TiredOfficeWorker();
	virtual ~TiredOfficeWorker();

public:
	void SetTiredOfficeWorkerStat(TiredOfficeWorkerStat* stat) { _stat = stat; }
	void SetMovingDistance(float dis) { _movingDistance = dis; }
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

private:
	TiredOfficeWorkerStat* _stat;
	float _movingDistance;
	Vec2 _movementLimit;
};