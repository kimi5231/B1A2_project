#include "pch.h"
#include "Door.h"

Door::Door(Vector pos, Dir dir, uint roomID, Dir roomDir)
	: _roomID(roomID), _isConnectable(true)
{
	_pos = pos;
	_dir = static_cast<Dir>((roomDir + dir) % DirCount);
}