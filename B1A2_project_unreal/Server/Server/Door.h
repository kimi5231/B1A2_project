#pragma once
#include "GameObject.h"

class Door : public GameObject
{
public:
	Door(Vector pos, Dir dir, int roomID, Dir roomDir);
	~Door() {};

public:
	Dir GetDir() { return _dir; }
	int GetOwnerCubeID() { return _ownerCubeID; }
	void SetConnectedCubeID(int connectedCubeID) { _connectedCubeID = connectedCubeID; }
	int GetConnectedCubeID() { return _connectedCubeID; }
	void SetDoorType(DoorType doorType) { _doorType = doorType;  }
	DoorType GetDoorType() { return _doorType;  }
	void SetConnectable(bool isConnectable) { _isConnectable = isConnectable; }

private:
	int _ownerCubeID{};
	int _connectedCubeID;
	Dir _dir{};
	DoorType _doorType;
	bool _isConnectable;
};