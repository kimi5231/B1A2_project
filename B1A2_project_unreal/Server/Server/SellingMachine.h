#pragma once
#include "GameObject.h"

class SellingMachine : public GameObject
{
public:
	SellingMachine(Dir dir, bool isSpecial);
	~SellingMachine();

public:
	Dir GetDir() { return _dir; }

private:
	Dir _dir{};
	bool _isSpecial{};
};