#include "pch.h"
#include "TilemapScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "TilemapActor.h"
#include "SpriteActor.h"
#include "CameraActor.h"

TilemapScene::TilemapScene()
{
}

TilemapScene::~TilemapScene()
{
}

void TilemapScene::Init()
{
	// Texture
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage1", L"Sprite\\Map\\Stage1.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\Map\\Tile.bmp", RGB(55, 255, 0));

	// Sprite
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stage1");
		Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
		GET_SINGLE(ResourceManager)->CreateSprite(L"Stage1", texture, 0, 0, mapSize.x, mapSize.y);
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Tile");
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileO", texture, 0, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileX", texture, 48, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileG", texture, 96, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileW", texture, 144, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileS", texture, 192, 0, 48, 48);
		GET_SINGLE(ResourceManager)->CreateSprite(L"TileD", texture, 240, 0, 48, 48);
	}

	// Tilemap
	GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap");
	
	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage1");
		SpriteActor* map = new SpriteActor();
		const Vec2Int size = sprite->GetSize();
		map->SetPos(Vec2(size.x / 2, size.y / 2));
		map->SetSprite(sprite);
		map->SetLayer(LAYER_BACKGROUND);

		_actors.push_back(map);
	}

	// TilemapActor
	{
		Tilemap* tilemap = GET_SINGLE(ResourceManager)->GetTilemap(L"Tilemap");
		tilemap->SetMapSize({ 155, 36 });
		TilemapActor* actor = new TilemapActor();
		actor->SetPos({ 0, 0 });
		actor->SetShowDebug(true);
		actor->SetTilemap(tilemap);

		_actors.push_back(actor);
	}
	
	// CameraActor
	{
		CameraActor* actor = new CameraActor();
		actor->SetPos({ 100, 100 });

		_actors.push_back(actor);
	}
	
	Super::Init();
}

void TilemapScene::Update()
{
	Super::Update();

	for (Actor* actor : _actors)
		actor->Tick();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap", L"Tilemap\\Tilemap.txt");
	}
}

void TilemapScene::Render(HDC hdc)
{
	Super::Render(hdc);

	for (Actor* actor : _actors)
		actor->Render(hdc);
}