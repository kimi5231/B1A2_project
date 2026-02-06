#include "pch.h"
#include "GameRoom.h"
#include "Door.h"
#include "Global.h"

GameRoom::GameRoom()
{
	
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
	std::uniform_int_distribution<int> dist1(_info.f1DoorCount.first, _info.f1DoorCount.second);
	int goalDoorCount = dist1(gen);

	std::bernoulli_distribution bern(0.5);

	// f1 , f2 벡터 사이즈로 문 층수 구별하기
	for (int i : std::views::iota(0u, _info.f1DoorCount.second))
	{
		if (goalDoorCount - _doors.size() == _info.f1DoorCount.second - i)
		{
			//DoorRef door = std::make_shared<Door>(_pos + _info.f1DoorPos[_dir][i], _info.doorDir[i], _dir);
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
			
			DoorRef door = std::make_shared<Door>(doorPos, _info.doorDir[i], _dir);
			_doors.push_back(door);
			continue;
		}

		if (bern(gen))
		{
			//DoorRef door = std::make_shared<Door>(_pos + _info.f1DoorPos[_dir][i], _info.doorDir[i], _dir);
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

			DoorRef door = std::make_shared<Door>(doorPos, _info.doorDir[i], _dir);
			_doors.push_back(door);
		}
	}

	// 문이 최소 수치보다 부족한지 확인

	return _doors;
}