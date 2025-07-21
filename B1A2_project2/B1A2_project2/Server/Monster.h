#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	virtual void UpdateIdle() {};
	virtual void UpdateCloseAttack() {};
	virtual void UpdateHit() {};
	virtual void UpdateDead() {};
	virtual void UpdateChase() {};
	virtual void UpdateRoaming() {};
	virtual void UpdateReturn() {};
	virtual void UpdateReturnIdle() {};
};