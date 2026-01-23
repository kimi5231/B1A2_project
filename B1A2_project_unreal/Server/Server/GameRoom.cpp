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
	std::uniform_int_distribution<int> dist1(_info.doorCount.first, _info.doorCount.second);
	int goalDoorCount = dist1(gen);

	std::bernoulli_distribution bern(0.5);

	for (int i : std::views::iota(0u, _info.doorCount.second))
	{
		// 추후 방향 지정 필요
		/*if (goalDoorCount - _doors.size() == _info.doorCount.second - i)
		{
			DoorRef door = std::make_shared<Door>(_pos + _info.doorPos[i], _info.doorDir, _dir);
			_doors.push_back(door);
			break;
		}

		if (bern(gen))
		{
			DoorRef door = std::make_shared<Door>(_pos + _info.doorPos[i], _info.doorDir, _dir);
			_doors.push_back(door);
		}*/
	}

	return _doors;
}