#pragma once
#include "Monster.h"
#include "Stat.h"

class BrokenCopyMachine : public Monster
{
	using Super = Monster;
public:
	BrokenCopyMachine();
	virtual ~BrokenCopyMachine();

	void Update();

public:
	virtual void UpdateIdle() override;
	virtual void UpdateLongAttack() override;
	virtual void UpdateHit() override;
	virtual void UpdateDead() override;

public:
	void SetBrokenCopyMachineStat(BrokenCopyMachineStat* stat) { _stat = stat; }

private:
	//void CalPixelPerSecond();

private:
	void CreateProjectile();

private:
	BrokenCopyMachineStat* _stat;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;
};