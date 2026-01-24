#include "pch.h"
#include "Door.h"

Door::Door(Vector pos, Dir dir, Dir roomDir)
	: _isConnectable(true)
{
	_pos = pos;
	_dir = static_cast<Dir>((roomDir + dir) % DirCount);
}