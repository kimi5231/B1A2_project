#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "Flipbook.h"
#include "Sound.h"
#include "Tilemap.h"
#include "Dialogue.h"
#include "SoundManager.h"
#include "Player.h"

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, std::filesystem::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);

	_sprites.clear();

	for (auto& item : _flipbooks)
		SAFE_DELETE(item.second);

	_flipbooks.clear();
}

Texture* ResourceManager::LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	std::filesystem::path fullpath = _resourcePath / path;		// /�� ��� ���� ������

	Texture* texture = new Texture();
	texture->LoadBMP(_hwnd, fullpath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const std::wstring& key, Texture* texture, int32 x, int32 y, int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];

	if (cx == 0)
		cx = texture->GetSize().x;
	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Flipbook* ResourceManager::CreateFlipbook(const std::wstring& key)
{
	if (_flipbooks.find(key) != _flipbooks.end())	// �̹� ������ ����
		return _flipbooks[key];

	Flipbook* fb = new Flipbook();
	_flipbooks[key] = fb;

	return fb;
}

Sound* ResourceManager::LoadSound(const std::wstring& key, const std::wstring& path)
{
	if (_sounds.find(key) != _sounds.end())
		return _sounds[key];

	std::filesystem::path fullPath = _resourcePath / path;

	Sound* sound = new Sound();
	sound->Load(fullPath, GET_SINGLE(SoundManager)->GetSystem(), SoundType::BGM);
	_sounds[key] = sound;

	return sound;
}

Tilemap* ResourceManager::CreateTilemap(const std::wstring& key)
{
	if (_tilemaps.find(key) != _tilemaps.end())
		return _tilemaps[key];

	Tilemap* tilemap = new Tilemap();
	_tilemaps[key] = tilemap;

	return tilemap;
}

Tilemap* ResourceManager::LoadTilemap(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tilemap = nullptr;

	if (_tilemaps.find(key) == _tilemaps.end())
		_tilemaps[key] = new Tilemap();

	tilemap = _tilemaps[key];

	std::filesystem::path fullPath = _resourcePath / path;
	tilemap->LoadFile(fullPath);
	
	return tilemap;
}

void ResourceManager::SaveTilemap(const std::wstring& key, const std::wstring& path)
{
	Tilemap* tilemap = GetTilemap(key);

	std::filesystem::path fullPath = _resourcePath / path;

	_tilemaps[key]->SaveFile(fullPath);
}

Dialogue* ResourceManager::LoadDialogue(const std::wstring& key, const std::wstring& path)
{
	if (_dialogues.find(key) != _dialogues.end())
		return _dialogues[key];

	std::filesystem::path fullPath = _resourcePath / path;

	Dialogue* dialogue = new Dialogue();
	dialogue->LoadFile(fullPath);
	_dialogues[key] = dialogue;

	return dialogue;
}

PlayerStat* ResourceManager::LoadPlayerStat(const std::wstring& path)
{
	if (_playerStat)
		return _playerStat;

	std::filesystem::path fullpath = _resourcePath / path;

	PlayerStat* playerStat = new PlayerStat();
	playerStat->LoadFile(fullpath);
	_playerStat = playerStat;

	return playerStat; 
}
