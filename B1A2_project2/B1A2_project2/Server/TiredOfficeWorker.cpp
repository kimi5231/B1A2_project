#include "pch.h"
#include "TiredOfficeWorker.h"
#include "TimeManager.h"

TiredOfficeWorker::TiredOfficeWorker()
{
}

TiredOfficeWorker::~TiredOfficeWorker()
{
}

void TiredOfficeWorker::Update()
{
}

void TiredOfficeWorker::UpdateIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->idleTime)
	{
		_currentMoveDistance = _moveDistance;
		SetState(ROAMING);
	}
}

void TiredOfficeWorker::UpdateCloseAttack()
{
}

void TiredOfficeWorker::UpdateHit()
{
}

void TiredOfficeWorker::UpdateDead()
{
}

void TiredOfficeWorker::UpdateChase()
{
}

void TiredOfficeWorker::UpdateRoaming()
{
}

void TiredOfficeWorker::UpdateReturn()
{
}

void TiredOfficeWorker::UpdateReturnIdle()
{
}