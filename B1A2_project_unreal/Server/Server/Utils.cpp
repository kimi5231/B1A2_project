#include "pch.h"
#include "Utils.h"
#include <cmath>
#include "Types.h"
#include "Global.h"
#include "BoundingBox.h"
#include "Monster.h"
#include "Cube.h"

Vector GetForwardVector(float pitch, float yaw)
{
    float p = pitch * (3.14159265f / 180.0f);
    float y = yaw * (3.14159265f / 180.0f);

    float x = cos(p) * cos(y);
    float y_pos = cos(p) * sin(y);
    float z = sin(p);

    Vector v{ x, y_pos, x };
    v.Normalize();

    return v;
}

Vector SelectRandomPosInCube(const CubeRef cube)
{
	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	Vector cubePos = cube->GetPos();
	VectorInt max{ tilemap.size(), tilemap[0].size(), tilemap[0][0].size() };
	std::uniform_int_distribution<int> selectX(0, max.x - 1);
	std::uniform_int_distribution<int> selectY(0, max.y - 1);

	VectorInt index{};
	while (!IsCanExist(index, cube))
	{
		int x = selectX(gen);
		int y = selectY(gen);

		// 바닥 높이 및 CubeType에 따른 보정
		int z = TileSize;
		switch (cube->GetCubeType())
		{
		case CubeType::GapRoom:
		case CubeType::RailCatwalk:
		case CubeType::StorageRoom_Step:
		case CubeType::CabinetRoom:
		case CubeType::FactoryRoom:
			z += 600;
			break;
		}
		z /= TileSize;

		index = { x, y, z };
	}

	return IndexToPos(index, cube);
}

bool IsCanExist(VectorInt index, const CubeRef cube)
{
	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	// 인덱스가 실제 배열 크기를 벗어나는지 최종 체크
	if (index < Vector{ 0, 0, 0 } || index >= max)
		return false;

	return tilemap[index.z][index.y][index.x] == 1 && (tilemap[index.z - 1][index.y][index.x] == 0 || tilemap[index.z - 1][index.y][index.x] == 2);
}

VectorInt PosToIndex(Vector pos, const CubeRef cube)
{
	Vector cubePos = cube->GetPos();
	Vector cubeSize = cube->GetSize();

	Vector startPos;
	switch (cube->GetDir())
	{
	case Front:
	case Back:
		startPos = { cubePos.x - (cubeSize.x / 2), cubePos.y - (cubeSize.y / 2), cubePos.z };
		break;
	case Right:
	case Left:
		startPos = { cubePos.x - (cubeSize.y / 2), cubePos.y - (cubeSize.x / 2), cubePos.z };
		break;
	}

	switch (cube->GetCubeType())
	{
	case CubeType::GapRoom:
	case CubeType::RailCatwalk:
	case CubeType::StorageRoom_Step:
	case CubeType::CabinetRoom:
	case CubeType::FactoryRoom:
		startPos.z -= 600;
		break;
	}

	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	VectorInt index = (pos - startPos) / TileSize;

	VectorInt result = index;
	switch (cube->GetDir())
	{
	case Right:
		result.x = index.y;
		result.y = (max.y - 1 - index.x);
		break;
	case Back:
		result.x = (max.x - 1 - index.x);
		result.y = (max.y - 1 - index.y);
		break;
	case Left:
		result.x = (max.x - 1 - index.y);
		result.y = index.x;
		break;
	}

	return result;
}

Vector IndexToPos(VectorInt index, const CubeRef cube)
{
	Vector cubePos = cube->GetPos();
	Vector cubeSize = cube->GetSize();

	Vector startPos;
	switch (cube->GetDir())
	{
	case Front:
	case Back:
		startPos = { cubePos.x - (cubeSize.x / 2), cubePos.y - (cubeSize.y / 2), cubePos.z };
		break;
	case Right:
	case Left:
		startPos = { cubePos.x - (cubeSize.y / 2), cubePos.y - (cubeSize.x / 2), cubePos.z };
		break;
	}

	switch (cube->GetCubeType())
	{
	case CubeType::GapRoom:
	case CubeType::RailCatwalk:
	case CubeType::StorageRoom_Step:
	case CubeType::CabinetRoom:
	case CubeType::FactoryRoom:
		startPos.z -= 600;
		break;
	}

	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	Vector pos = index;

	// Cube 방향에 따라 보정
	switch (cube->GetDir())
	{
	case Right:
		pos.x = (float)(max.y - 1 - index.y);
		pos.y = (float)index.x;
		break;
	case Back:
		pos.x = (float)(max.x - 1 - index.x);
		pos.y = (float)(max.y - 1 - index.y);
		break;
	case Left:
		pos.x = (float)index.y;
		pos.y = (float)(max.x - 1 - index.x);
		break;
	}

	pos *= TileSize;

	return startPos + pos;
}
