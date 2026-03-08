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
		if (gameRoom->GetBoundingBox().CheckInclude(_pos))
		{
			currentCube = gameRoom;
			break;
		}
	}

	// 현재 위치한 방의 타일맵 가져오기
	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetGameRoomType());
	
	// 타일맵의 시작점 계산(FrontLeftButtom)
	// CubeType에 따라 계산 다를수도
	Vector cubePos = currentCube->GetPos();
	Vector cubeSize = currentCube->GetSize();
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

	SetPos(_pos);

	// 해당 타일로 이동이 가능한지 확인
	// 몬스터 바운딩 박스 꼭짓점 인덱스 계산 및 확인
	const std::array<Vector, CornerCount>& corners = _box.GetCorners();
	for (const auto& corner : corners)
	{
		Vector max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };
		Vector index = (corner - start) / 25;
		if (index < Vector{0, 0, 0} || index > max)
		{
			SetPos(pos);
			return;
		}

		if (tilemap[index.z][index.y][index.x] == 0)
		{
			SetPos(pos);
			return;
		}
	}

	g_framework->SendMovePacket(shared_from_this(), true);

	// 다른 방으로 넘어가는 거 고려할 것
}