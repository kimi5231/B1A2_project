#include "pch.h"
#include "GameRoom.h"
#include "Door.h"
#include "Global.h"

GameRoom::GameRoom(Vector pos, Dir dir, GameRoomInfo info)
	: _pos(pos), _dir(dir), _info(info)
{
	Vector min{}, max{};

	switch (_dir)
	{
	case Front:
	case Back:
		min = { _pos.x - _info.size.x / 2,  _pos.y - _info.size.y / 2,  _pos.z};
		max = { _pos.x + _info.size.x / 2,  _pos.y + _info.size.y / 2, _pos.z + _info.size.z};
		break;
	case Right:
	case Left:
		min = { _pos.x - _info.size.y / 2,  _pos.y - _info.size.x / 2,  _pos.z };
		max = { _pos.x + _info.size.y / 2,  _pos.y + _info.size.x / 2, _pos.z + _info.size.z };
		break;
	}

	_box.SetRanges(min, max);
}

GameRoom::~GameRoom()
{
}

void GameRoom::Update()
{

}

// 추후 비상구 생성 여부도 따질 것
std::vector<DoorRef>& GameRoom::CreateDoors()
{
	std::bernoulli_distribution isCreateDoor(0.5);

	// 1층 문 생성
	if (_info.f1DoorPos.size())
	{
		std::uniform_int_distribution<int> selectF1DoorCount(_info.f1DoorCount.first, _info.f1DoorCount.second);
		int f1GoalDoorCount = selectF1DoorCount(gen);

		for (int i = 0; i < _info.f1DoorCount.second; i++)
		{
			Vector doorPos{};
			switch (_dir)
			{
			case Front:
				doorPos.x = _pos.x + _info.f1DoorPos[i].x;
				doorPos.y = _pos.y + _info.f1DoorPos[i].y;
				break;
			case Right:
				doorPos.x = _pos.x - _info.f1DoorPos[i].y;
				doorPos.y = _pos.y + _info.f1DoorPos[i].x;
				break;
			case Back:
				doorPos.x = _pos.x - _info.f1DoorPos[i].x;
				doorPos.y = _pos.y - _info.f1DoorPos[i].y;
				break;
			case Left:
				doorPos.x = _pos.x + _info.f1DoorPos[i].y;
				doorPos.y = _pos.y - _info.f1DoorPos[i].x;
				break;
			}

			DoorRef door = std::make_shared<Door>(doorPos, _info.doorDir[i], _id, _dir);

			// 남은 목표 문 개수가 남은 생성 시도 횟수와 같으면 계속 문 생성 
			if (isCreateDoor(gen) || (f1GoalDoorCount - _doors.size() == _info.f1DoorCount.second - i))
			{
				_doors.push_back(door);
				continue;
			}

			// 문을 생성하지 않았다면 벽 생성
			_walls.push_back(door);
		}
	}
	
	// 2층 문 생성
	if (_info.f2DoorPos.size())
	{
		std::uniform_int_distribution<int> selectF2DoorCount(_info.f2DoorCount.first, _info.f2DoorCount.second);
		int f2GoalDoorCount = selectF2DoorCount(gen);
	
		// 남은 목표 문 개수가 남은 생성 시도 횟수와 같으면 계속 문 생성
		for (int i = 0; i < _info.f2DoorCount.second; i++)
		{
			Vector doorPos{};
			switch (_dir)
			{
			case Front:
				doorPos.x = _pos.x + _info.f2DoorPos[i].x;
				doorPos.y = _pos.y + _info.f2DoorPos[i].y;
				break;
			case Right:
				doorPos.x = _pos.x - _info.f2DoorPos[i].y;
				doorPos.y = _pos.y + _info.f2DoorPos[i].x;
				break;
			case Back:
				doorPos.x = _pos.x - _info.f2DoorPos[i].x;
				doorPos.y = _pos.y - _info.f2DoorPos[i].y;
				break;
			case Left:
				doorPos.x = _pos.x + _info.f2DoorPos[i].y;
				doorPos.y = _pos.y - _info.f2DoorPos[i].x;
				break;
			}

			DoorRef door = std::make_shared<Door>(doorPos, _info.doorDir[i], _id, _dir);

			// 남은 목표 문 개수가 남은 생성 시도 횟수와 같으면 계속 문 생성 
			if (isCreateDoor(gen) || (f2GoalDoorCount - _doors.size() == _info.f2DoorCount.second - i))
			{
				_doors.push_back(door);
				continue;
			}

			// 문을 생성하지 않았다면 벽 생성
			_walls.push_back(door);
		}
	}
	
	return _doors;
}