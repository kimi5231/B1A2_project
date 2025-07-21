#include "pch.h"
#include "BrokenCopyMachine.h"
#include "TimeManager.h"

BrokenCopyMachine::BrokenCopyMachine()
{

}

BrokenCopyMachine::~BrokenCopyMachine()
{

}

void BrokenCopyMachine::Update()
{
	Super::Update();
}

void BrokenCopyMachine::UpdateIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->attackCoolTime)
	{
		_sumTime = 0.f;
		SetState(LONG_ATTACK);
	}
}

void BrokenCopyMachine::UpdateLongAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 투사체 생성
	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		//CreateProjectile();
	}

	if (_currentProjectileCount == _stat->projectileCount)
	{
		_sumTime = 0.f;
		SetState(IDLE);
		_currentProjectileCount = 0;
	}
}

void BrokenCopyMachine::UpdateHit()
{
}

void BrokenCopyMachine::UpdateDead()
{
}