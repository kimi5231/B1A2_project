#include "pch.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"

Cube::Cube(Vector pos, Dir dir, CubeInfo info)
	: _pos(pos), _dir(dir), _info(info)
{
	auto type = info.type;
	Vector Pos = _pos;
	if (type == CubeType::GapRoom || type == CubeType::RailCatwalk ||
		type == CubeType::StorageRoom_Step || type == CubeType::CabinetRoom ||
		type == CubeType::FactoryRoom)
	{
		Pos.z -= 600;
		_box.SetBounds(Pos, info.size, dir);
	}
	else
		_box.SetBounds(_pos, info.size, dir);
}

Cube::~Cube()
{
}

std::vector<Door*> Cube::CreateDoors()
{
	std::vector<Door*> doors;
	for (int i = 0; i < _info.doorPos.size(); i++)
	{
		Vector doorPos{};
		doorPos.z = _pos.z + _info.doorPos[i].z;
		switch (_dir)
		{ 
		case Front:
			doorPos.x = _pos.x + _info.doorPos[i].x;
			doorPos.y = _pos.y + _info.doorPos[i].y;
			break;
		case Right:
			doorPos.x = _pos.x - _info.doorPos[i].y;
			doorPos.y = _pos.y + _info.doorPos[i].x;
			break;
		case Back:
			doorPos.x = _pos.x - _info.doorPos[i].x;
			doorPos.y = _pos.y - _info.doorPos[i].y;
			break;
		case Left:
			doorPos.x = _pos.x + _info.doorPos[i].y;
			doorPos.y = _pos.y - _info.doorPos[i].x;
			break;
		}

		Door* door = new Door(doorPos, _info.doorDir[i], _id, _dir);
		doors.push_back(door);
	}

	return doors;
}