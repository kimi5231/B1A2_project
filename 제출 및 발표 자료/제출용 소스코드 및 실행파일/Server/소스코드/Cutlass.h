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
	float GetHeight() { return _height; }
	int GetDamage() { return _damage; }

private:
	float _angle;
	float _range;
	float _height;
	int _damage;
};