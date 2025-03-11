#include "pch.h"
#include "TilemapActor.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "CollisionManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "BoxCollider.h"

TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();

	Vec2Int mapSize = _tilemap->GetMapSize();

	std::vector<std::vector<Tile>>& tiles = _tilemap->GetTiles();

	for (int32 y = 0; y < mapSize.y; ++y)
	{
		for (int32 x = 0; x < mapSize.x; ++x)
		{
			if (tiles[y][x].value == 0)
				continue;

			BoxCollider* collider = new BoxCollider();
			collider->SetSize({ MAP_TILE_SIZEX, MAP_TILE_SIZEY });
			collider->SetPos({ (float)(x * MAP_TILE_SIZEX + MAP_TILE_SIZEX / 2),(float)(y * MAP_TILE_SIZEY + MAP_TILE_SIZEY / 2) });
			
			// flag reset
			collider->ResetCollisionFlag();

			switch (tiles[y][x].value)
			{
			case 1:		// ������ �״� ��
				break;
			case 2:
				collider->SetCollisionLayer(CLT_GROUND); break;
			case 3:
				collider->SetCollisionLayer(CLT_WALL); break;
			case 4:		// ���̺� ����Ʈ
				break;
			}
			
			// �浹�� ��ü
			collider->AddCollisionFlagLayer(CLT_PLAYER);
			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

void TilemapActor::Tick()
{
	Super::Tick();

	if (!_showDebug)
		return;

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
	Sprite* spriteG = GET_SINGLE(ResourceManager)->GetSprite(L"TileG");
	Sprite* spriteW = GET_SINGLE(ResourceManager)->GetSprite(L"TileW");
	Sprite* spriteS = GET_SINGLE(ResourceManager)->GetSprite(L"TileS");

	Vec2 cameraPosAdjustment = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	// �ø�
	// ī�޶� ��ǥ�� ���۰� ���� ���ϱ�
	int32 leftX = (int32)cameraPos.x - winSize.x / 2;
	int32 leftY = (int32)cameraPos.y - winSize.y / 2;
	int32 rightX = (int32)cameraPos.x + winSize.x / 2;
	int32 rightY = (int32)cameraPos.y + winSize.y / 2;

	// ī�޶� ��ǥ�� ���۰� ���� ���� ��ǥ�� ��ȯ�� �� ī�޶� ���̴� Ÿ�� �ε��� ���� ���ϱ�
	int32 startX = (leftX - _pos.x) / MAP_TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / MAP_TILE_SIZEY;
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
					(_pos.x + x * MAP_TILE_SIZEX) * winSizeAdjustment.x - cameraPosAdjustment.x,
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteO->GetDC(),
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent());
				break;
			case 1:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2),
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteX->GetDC(),
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent());
				break;
			case 2:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2),
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteG->GetDC(),
					spriteG->GetPos().x,
					spriteG->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteG->GetTransparent());
				break;
			case 3:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2),
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteW->GetDC(),
					spriteW->GetPos().x,
					spriteW->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteW->GetTransparent());
				break;
			case 4:
				::TransparentBlt(hdc,
					(_pos.x + x * MAP_TILE_SIZEX) * ((float)winSize.x / (float)DefaultWinSizeX) - ((int32)cameraPos.x - winSize.x / 2),
					(_pos.y + y * MAP_TILE_SIZEY) * ((float)winSize.y / (float)DefaultWinSizeY) - ((int32)cameraPos.y - winSize.y / 2),
					MAP_TILE_SIZEX * ((float)winSize.x / (float)DefaultWinSizeX),
					MAP_TILE_SIZEY * ((float)winSize.y / (float)DefaultWinSizeY),
					spriteS->GetDC(),
					spriteS->GetPos().x,
					spriteS->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteS->GetTransparent());
				break;
			}
		}
	}
}

Tile* TilemapActor::GetTile()
{
	// ���� ��ǥ�迡���� ���콺 ��ǥ
	Vec2 pos = GET_SINGLE(ValueManager)->GetMousePosInWorld();

	// �ε����� ��ȯ
	int32 x = (int32)pos.x / MAP_TILE_SIZEX;
	int32 y = (int32)pos.y / MAP_TILE_SIZEY;

	Tile* tile = _tilemap->GetTileAt({ x, y });

	return tile;
}

void TilemapActor::TickPicking()
{
	// �巡�� ����
	if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftAlt))
	{	
		// LeftAlt + LeftMouse => X
		// LeftAlt + RightMouse => O
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
		{
			if (GetTile())
				GetTile()->value = TILE_X;
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::RightMouse))
		{
			if (GetTile())
				GetTile()->value = TILE_O;
		}
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftCtrl))
	{
		// LeftAlt + LeftMouse => S
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
		{
			if (GetTile())
				GetTile()->value = TILE_S;
		}
	}
	else
	{
		// LeftMouse => W
		// RightMouse => G
		if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftMouse))
		{
			if (GetTile())
				GetTile()->value = TILE_W;
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::RightMouse))
		{
			if (GetTile())
				GetTile()->value = TILE_G;
		}
	}
}