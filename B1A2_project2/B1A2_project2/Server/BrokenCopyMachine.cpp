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
		CreateProjectile();
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
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 Idle로 변경
	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(IDLE);
	}
}

void BrokenCopyMachine::UpdateDead()
{
}

void BrokenCopyMachine::CreateProjectile()
{
	/*GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y }, LAYER_PROJECTILE);
	paper->SetDir(GetDir());
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);*/

	_currentProjectileCount++;
}