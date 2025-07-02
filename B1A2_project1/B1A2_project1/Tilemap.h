#pragma once
#include "ResourceBase.h"

enum TILE_TYPE
{
	TILE_O,		// �� �� �ִ� ��
	TILE_X,		// ������ �״� ��
	TILE_G,		// Ground
	TILE_W,		// Wall
	TILE_S,		// Save Point
	TILE_D,		// Stair
	TILE_N,		// Next
};

struct Tile
{
	int32 value = TILE_O;
};

enum TILE_SIZE
{
	MAP_TILE_SIZEX = 40,
	MAP_TILE_SIZEY = 40,
	TILE_SIZEX = 48,
	TILE_SIZEY = 48,
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

public:
	virtual void LoadFile(const std::wstring& path) override;
	virtual void SaveFile(const std::wstring& path) override;

public:
	Vec2Int GetMapSize() { return _mapSize; }
	Tile* GetTileAt(Vec2Int pos);
	std::vector<std::vector<Tile>>& GetTiles() { return _tiles; }

	void SetMapSize(Vec2Int size);

private:
	// �ʿ� ���� Ÿ�� ��
	Vec2Int _mapSize{};
	std::vector<std::vector<Tile>> _tiles;
};

