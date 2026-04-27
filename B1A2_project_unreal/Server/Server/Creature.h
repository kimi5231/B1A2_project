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
	virtual void SetPos(Vector pos) override;
	void SetCurrentCubeID(const std::vector<CubeRef>& cubes);
	int GetCurrentCubeID() { return _currentCubeID; }
	virtual bool SetState(ObjectState state, bool isSend = true) override;

protected:
	int _currentCubeID;

	int _hp;
};