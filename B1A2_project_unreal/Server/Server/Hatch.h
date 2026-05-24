#pragma once
#include "Door.h"

class Hatch : public Door
{
public:
	Hatch(Vector pos, Dir dir, int roomID, Dir roomDir);
	~Hatch() {};

public:
	void Update() override;
};