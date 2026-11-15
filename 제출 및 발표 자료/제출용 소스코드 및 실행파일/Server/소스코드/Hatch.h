#pragma once
#include "Door.h"

class Hatch : public Door
{
public:
	Hatch(Vector pos, Dir dir, int roomID, Dir roomDir);
	~Hatch() {};

public:
	void Update() override;

public:
	virtual bool SetState(ObjectState state, bool isSend = true);

private:
	float _sumTime;

	float _changeStateTime;
};