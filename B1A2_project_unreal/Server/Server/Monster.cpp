#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Room.h"
#include "GameRoom.h"
#include "DataManager.h"

Monster::Monster()
{
	_pos = {0, 200, 100};
	_size = { 80, 80, 80 };
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Monster;
	// 나중에 방향 조절하기
	_box.SetBounds(_pos, _size, Front);
} 

Monster::~Monster()
{
}

void Monster::Update(const std::vector<GameRoomRef>& gameRooms)
{
	// 현재 위치한 방이 어디인지 확인
	GameRoomRef currentCube;
	for (const GameRoomRef gameRoom : gameRooms)
	{
		if (gameRoom->CheckInclude(_box))
		{
			currentCube = gameRoom;
			break;
		}
	}

	// 현재 위치한 방의 타일맵 가져오기
	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetGameRoomType());
	// 
	Vector cubePos = currentCube->GetPos();
	Vector cubeSize = currentCube->GetSize();
	// CubeType에 따라 계산 다를수도
	// FrontLeftButtom
	Vector start{ cubePos.x - cubeSize.x / 2, cubePos.y - cubeSize.y / 2, cubePos.z };

	// 일단은 랜덤한 방향으로 이동하도록, 추후 수정
	std::uniform_int_distribution<int> selectDir(static_cast<int>(Front), static_cast<int>(Left));
	Dir dir = static_cast<Dir>(selectDir(gen));

	// 이동할 좌표 계산
	Vector pos = _pos;
	// 타일 한칸씩 이동
	switch (dir)
	{
	case Front:
		_pos.y -= 25;
		break;
	case Right:
		_pos.x += 25;
		break;
	case Back:
		_pos.y += 25;
		break;
	case Left:
		_pos.x -= 25;
		break;
	}

	_box.SetOwnerPos(_pos, Front);

	// 해당 타일로 이동이 가능한지 확인
	// 몬스터 바운딩 박스 꼭짓점 인덱스 계산 및 확인
	const std::array<Vector, ConerCount>& coners = _box.GetConers();
	for (const auto& coner : coners)
	{
		Vector index = (coner - start) / 25;
		if (tilemap[index.z][index.y][index.x] == 0)
		{
			_pos = pos;
			return;
		}
	}

	g_framework->SendMovePacket(shared_from_this(), true);

	// 다른 방으로 넘어가는 거 고려할 것
}