#pragma once
#include "GameObject.h"

class Door : public GameObject
{
public:
	Door(Vector pos);
	~Door() {};

public:
	void Update() {};

private:
	Vector _pos{};
	Dir _dir{};
	bool _isConnectable;
};