#include "pch.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}

void Tilemap::LoadFile(const std::wstring& path)
{
	std::wifstream ifs;

	ifs.open(path);

	// 맵에 들어가는 타일 수 가져오기
	ifs >> _mapSize.x >> _mapSize.y;

	SetMapSize(_mapSize);

	for (int32 y = 0; y < _mapSize.y; ++y)
	{
		std::wstring line;
		ifs >> line;

		for (int32 x = 0; x < _mapSize.x; ++x)
		{
			// line[x]는 문자이므로, 정수값으로 바꾸기 위해 문자 0을 뺌.
			_tiles[y][x].value = line[x] - L'0';
		}
	}

	ifs.close();
}

void Tilemap::SaveFile(const std::wstring& path)
{
	std::wofstream ofs;

	ofs.open(path);

	// 맵에 들어가는 타일 수 저장
	ofs << _mapSize.x << std::endl;
	ofs << _mapSize.y << std::endl;

	// 타일 값 저장
	for (int32 y = 0; y < _mapSize.y; ++y)
	{
		for (int32 x = 0; x < _mapSize.x; ++x)
		{
			ofs << _tiles[y][x].value;
		}
		ofs << std::endl;
	}

	ofs.close();
}

// 특정 좌표의 타일의 정보 얻기
Tile* Tilemap::GetTileAt(Vec2Int pos)
{
	if (pos.x < 0 || pos.x >= _mapSize.x || pos.y < 0 || pos.y > _mapSize.y)
		return nullptr;

	return &_tiles[pos.y][pos.x];
}

void Tilemap::SetMapSize(Vec2Int size)
{
	_mapSize = size;

	_tiles = std::vector(size.y, std::vector<Tile>(size.x));

	for (int32 y = 0; y < size.y; y++)
	{
		for (int32 x = 0; x < size.x; x++)
			_tiles[y][x] = Tile{TILE_O};
	}
}