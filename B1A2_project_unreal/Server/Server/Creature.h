#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
public:
	Creature();
	virtual ~Creature() {};

public:
	virtual bool GetDamage(int damage);

protected:
	int _hp;
};