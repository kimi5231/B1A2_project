#include "pch.h"
#include "Door.h"

Door::Door(Vector pos, Dir dir, int ownerCubeID, Dir cubeDir)
	: _ownerCubeID(ownerCubeID), _isConnectable(true)
{
	_pos = pos;
	_dir = static_cast<Dir>((cubeDir + dir) % DirCount);
	_doorType = DoorType::Door;
	_type = ObjectType::Door;
	_state = ObjectState::CLOSE;
}