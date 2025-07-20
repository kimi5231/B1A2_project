#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void LateUpdate() override;

private:
	float _speed = 100.f;
};

