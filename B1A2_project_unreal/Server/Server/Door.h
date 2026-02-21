#pragma once
#include "GameObject.h"

class Door : public GameObject
{
public:
	Door(Vector pos, Dir dir, uint roomID, Dir roomDir);
	~Door() {};

public:
	void Update() {};

public:
	Dir GetDir() { return _dir; }
	uint GetRoomID() { return _roomID; }
	void SetConnectable(bool isConnectable) { _isConnectable = isConnectable; }

private:
	uint _roomID{};
	Dir _dir{};
	bool _isConnectable;
};