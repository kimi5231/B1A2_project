#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
public:
	Creature();
	virtual ~Creature() {};

public:
	virtual bool GetDamage(int damage);

public:
	virtual bool SetState(ObjectState state) override;

protected:
	int _hp;
};