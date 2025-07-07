#pragma once
#include "Monster.h"

class TiredOfficeWorker : public Monster
{
public:
	void SetTiredOfficeWorkerStat(Protocol::TiredOfficeWorkerStat& stat) { _stat = stat; }
	void SetMovingDistance(float dis) { _stat.set_movingdistance(dis); }
	void SetMovementLimitX(float limit) { _stat.set_movementlimitx(limit); }
	void SetMovementLimitY(float limit) { _stat.set_movementlimity(limit); }

private:
	Protocol::TiredOfficeWorkerStat _stat;
};