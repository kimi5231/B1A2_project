#include "pch.h"
#include "Door.h"

Door::Door(Vector pos, Dir dir, Dir roomDir)
	: _pos(pos), _isConnectable(true)
{
	// 이게 맞나?
	_dir = static_cast<Dir>((roomDir + dir) % DirCount);
}