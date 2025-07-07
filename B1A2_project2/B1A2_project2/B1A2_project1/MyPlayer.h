#pragma once
#include "Player.h"

class MyPlayer : public Player
{
	using Super = Player;
public:
	MyPlayer();
	virtual ~MyPlayer() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickDuckDown() override;
	virtual void TickDuckDownMove() override;
	virtual void TickJump() override;
	virtual void TickCloseAttack() override;
	virtual void TickLongAttack() override;
	virtual void TickSkillReady() override;
	virtual void TickSkillWaiting() override;
	virtual void TickSkillEnd() override;
	virtual void TickHang() override;
	virtual void TickRelease() override;
	virtual void TickHit() override;
	virtual void TickDead() override;

private:
	bool _keyPressed = false;
};