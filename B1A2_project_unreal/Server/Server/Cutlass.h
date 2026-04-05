#pragma once
#include "Tool.h"

class Cutlass : public Tool
{
public:
	Cutlass(ItemType itemType);
	virtual ~Cutlass() {};

public:
	float GetAngle() { return _angle; }
	float GetRange() { return _range; }
	int GetDamage() { return _damage; }

private:
	float _angle;
	float _range;
	int _damage;
};