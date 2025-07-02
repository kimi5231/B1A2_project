#pragma once
#include "Actor.h"

class Tilemap;
class Tile;

// Tilemap을 출력&&수정하기 위한 클래스
class TilemapActor : public Actor
{
	using Super = Actor;
public:
	TilemapActor();
	virtual ~TilemapActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetTilemap(Tilemap* tilemap) { _tilemap = tilemap; }
	Tilemap* GetTilemap() { return _tilemap; }
	Tile* GetTile();
	void SetShowDebug(bool show) { _showDebug = show; }

	void TickPicking();

private:
	Tilemap* _tilemap = nullptr;
	bool _showDebug = false;
};

