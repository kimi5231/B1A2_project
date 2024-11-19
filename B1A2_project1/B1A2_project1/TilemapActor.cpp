#include "pch.h"
#include "TilemapActor.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Tilemap.h"
#include "Sprite.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();

	TickPicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_showDebug)
		return;

	if (!_tilemap)
		return;

	Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// �ø�
	// ī�޶� ��ǥ�� ���۰� ���� ���ϱ�
	int32 leftX = (int32)cameraPos.x - GWinSizeX / 2;
	int32 leftY = (int32)cameraPos.y - GWinSizeY / 2;
	int32 rightX = (int32)cameraPos.x + GWinSizeX / 2;
	int32 rightY = (int32)cameraPos.y + GWinSizeY / 2;

	// ī�޶� ��ǥ�� ���۰� ���� ���� ��ǥ�� ��ȯ�� �� �ε��� ���ϱ�
	int32 startX = (leftX - _pos.x) / MAP_TILE_SIZEX;
	int32 startY = (leftY - _pos.x) / MAP_TILE_SIZEY;
	int32 endX = (rightX - _pos.x) / MAP_TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / MAP_TILE_SIZEY;

	for (int32 y = startY; y <= endY; ++y)
	{
		for (int32 x = startX; x <= endX; ++x)
		{
			if (x < 0 || x >= mapSize.x)
				continue;
			if (y < 0 || y >= mapSize.y)
				continue;

			switch (tiles[y][x].value)
			{
			case 0:
				::TransparentBlt(hdc,
					_pos.x + x * MAP_TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * MAP_TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					MAP_TILE_SIZEX,
					MAP_TILE_SIZEY,
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
				break;
			case 1:
				::TransparentBlt(hdc,
					_pos.x + x * MAP_TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
					_pos.y + y * MAP_TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
					MAP_TILE_SIZEX,
					MAP_TILE_SIZEY,
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent());
				break;
			}
		}
	}
}

void TilemapActor::TickPicking()
{
	// �巡�� ����
	if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

		// ī�޶� ��ǥ
		int32 screenX = (int32)cameraPos.x - GWinSizeX / 2;
		int32 screenY = (int32)cameraPos.y - GWinSizeY / 2;

		// ���� ��ǥ
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// ���� ��ǥ�� ī�޶� ��ǥ�� ��ȯ
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		// �ε����� ��ȯ
		int32 x = posX / MAP_TILE_SIZEX;
		int32 y = posY / MAP_TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({x, y});

		if (tile)
			tile->value = TILE_X;
	}
}