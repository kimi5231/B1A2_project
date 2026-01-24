#pragma once
#include "GameObject.h"

class Door : public GameObject
{
public:
	Door(Vector pos, Dir dir, Dir roomDir);
	~Door() {};

public:
	void Update() {};

public:
	Dir GetDir() { return _dir; }
	void SetConnectable(bool isConnectable) { _isConnectable = isConnectable; }

private:
	Dir _dir{};
	bool _isConnectable;
};