#pragma once
#include "FlipbookActor.h"

class GameObject : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	GameObject();
	virtual ~GameObject() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickDuckDown() {};
	virtual void TickDuckDownMove() {};
	virtual void TickJump() {};
	virtual void TickCloseAttack() {};
	virtual void TickLongAttack() {};
	virtual void TickThrust() {};
	virtual void TickBackStep() {};
	virtual void TickSlashWave() {};
	virtual void TickSkillReady() {};
	virtual void TickSkillWaiting() {};
	virtual void TickSkillEnd() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickDead() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickDash() {};
	virtual void TickReturn() {};
	virtual void TickRETURN_IDLE() {};
	virtual void TickOn() {};
	virtual void TickOn2() {};
	virtual void TickReady() {};
	virtual void TickOff() {};
	virtual void UpdateAnimation() {};

protected:
	void TickGravity();

public:
	virtual float GetSpeed() = 0;

public:
	void SetState(ObjectState state);
	ObjectState GetState() { return _info.state(); }

	void SetDir(Dir dir);
	Dir GetDir() { return _info.dir(); }

protected:
	Protocol::ObjectInfo _info{};

	int32 _gravity = 1000;
	float _ySpeed{};

	bool _isGround = true;
	bool _isAir = false;
};