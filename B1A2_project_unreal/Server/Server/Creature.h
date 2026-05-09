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
	virtual void SetPos(Vector pos) override;
	void SetCurrentCubeID(const std::vector<CubeRef>& cubes);
	int GetCurrentCubeID() { return _currentCubeID; }
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	int GetHP() { return _hp; }

protected:
	int _currentCubeID;
	int _maxHP;
	int _hp;
};