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

void Cube::Update()
{

}

// 추후 비상구 생성 여부도 따질 것
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
	
	//// 2층 문 생성
	//if (_info.f2DoorPos.size())
	//{
	//	std::uniform_int_distribution<int> selectF2DoorCount(_info.f2DoorCount.first, _info.f2DoorCount.second);
	//	int f2GoalDoorCount = selectF2DoorCount(gen);
	//
	//	// 남은 목표 문 개수가 남은 생성 시도 횟수와 같으면 계속 문 생성
	//	for (int i = 0; i < _info.f2DoorCount.second; i++)
	//	{
	//		Vector doorPos{};
	//		switch (_dir)
	//		{
	//		case Front:
	//			doorPos.x = _pos.x + _info.f2DoorPos[i].x;
	//			doorPos.y = _pos.y + _info.f2DoorPos[i].y;
	//			break;
	//		case Right:
	//			doorPos.x = _pos.x - _info.f2DoorPos[i].y;
	//			doorPos.y = _pos.y + _info.f2DoorPos[i].x;
	//			break;
	//		case Back:
	//			doorPos.x = _pos.x - _info.f2DoorPos[i].x;
	//			doorPos.y = _pos.y - _info.f2DoorPos[i].y;
	//			break;
	//		case Left:
	//			doorPos.x = _pos.x + _info.f2DoorPos[i].y;
	//			doorPos.y = _pos.y - _info.f2DoorPos[i].x;
	//			break;
	//		}

	//		DoorRef door = std::make_shared<Door>(doorPos, _info.doorDir[i], _id, _dir);

	//		// 남은 목표 문 개수가 남은 생성 시도 횟수와 같으면 계속 문 생성 
	//		if (isCreateDoor(gen) || (f2GoalDoorCount - _doors.size() == _info.f2DoorCount.second - i))
	//		{
	//			_doors.push_back(door);
	//			continue;
	//		}

	//		// 문을 생성하지 않았다면 벽 생성
	//		_walls.push_back(door);
	//	}
	//}
}