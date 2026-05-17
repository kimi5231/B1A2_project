#include "pch.h"
#include "Door.h"

Door::Door(Vector pos, Dir dir, int roomID, Dir roomDir)
	: _ownerCubeID(roomID), _isConnectable(true)
{
	_pos = pos;
	_dir = static_cast<Dir>((roomDir + dir) % DirCount);
	_doorType = DoorType::Door;
	_type = ObjectType::Door;
	_state = ObjectState::CLOSE;
}