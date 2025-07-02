#pragma once
#include "Creature.h"

class Player;

class Monster : public Creature
{
	using Super = Creature;
public:
	Monster();
	virtual ~Monster() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickJump() override {};
	virtual void TickCloseAttack() override {};
	virtual void TickLongAttack() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void TickReturn() override {};
	virtual void TickReturnIdle() override {};
	virtual void UpdateAnimation() override {};


public:
	virtual int32 GetAttack() = 0;
	virtual int32& GetHp() = 0;
	virtual float GetSpeed() = 0;
	virtual Vec2Int GetPlayerDetection() = 0;

	void SetTarget(Player* player) { _target = player; }

	void SetMonsterId(int32 id) { _id = id; }

protected:
	Player* _target = nullptr;
	
	int32 _id = 0;
};