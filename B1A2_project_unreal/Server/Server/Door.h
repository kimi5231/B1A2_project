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
	void SetDoorType(DoorType doorType) { _doorType = doorType;  }
	DoorType GetDoorType() { return _doorType;  }
	void SetConnectable(bool isConnectable) { _isConnectable = isConnectable; }

private:
	uint _roomID{};
	Dir _dir{};
	DoorType _doorType;
	bool _isConnectable;
};