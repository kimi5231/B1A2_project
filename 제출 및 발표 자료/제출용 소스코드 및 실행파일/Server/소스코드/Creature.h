#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
public:
	Creature();
	virtual ~Creature() {};

public:
	bool TackDamage(int damage);
	bool TackHeal(int heal);

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	int GetHP() { return _hp; }

protected:
	int _maxHP;
	int _hp;
	bool _isInvincible;
};