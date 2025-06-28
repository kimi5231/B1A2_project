#pragma once
class ResourceBase;
class Texture;
class Sprite;
class Flipbook;
class Sound;
class Tilemap;
class Dialogue;
class Item;
class Stage;
class ItemStage;
class StructureStage;
struct StageInfo;
struct PlayerStat;
struct TiredOfficeWorkerStat;
struct BrokenCopyMachineStat;
struct AmateurFencerStat;
struct FinalBossStat;

class ResourceManager
{
public:
	DECLARE_SINGLE(ResourceManager);

	~ResourceManager();

public:
	void Init(HWND hwnd, std::filesystem::path resourcePath);
	void Clear();

	const std::filesystem::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const std::wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const std::wstring& key, const std::wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const std::wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const std::wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Flipbook* GetFlipbook(const std::wstring& key) { return _flipbooks[key]; }
	Flipbook* CreateFlipbook(const std::wstring& key);

	Sound* GetSound(const std::wstring& key) { return _sounds[key]; }
	Sound* LoadSound(const std::wstring& key, const std::wstring& path);

	Tilemap* GetTilemap(const std::wstring& key) { return _tilemaps[key]; }
	Tilemap* CreateTilemap(const std::wstring& key);
	Tilemap* LoadTilemap(const std::wstring& key, const std::wstring& path);
	void SaveTilemap(const std::wstring& key, const std::wstring& path);

	Dialogue* GetDialogue(const std::wstring& key) { return _dialogues[key]; }
	Dialogue* LoadDialogue(const std::wstring& key, const std::wstring& path);

	Item* GetItem(const std::wstring& key) { return _items[key]; }
	Item* LoadItem(const std::wstring& key, const std::wstring& path);

	Stage* GetStage(const std::wstring& key) { return _stages[key]; }
	Stage* LoadStage(const std::wstring& key, const std::wstring& path);

	ItemStage* GetItemStage(const std::wstring& key) { return _itemStages[key]; }
	ItemStage* LoadItemStage(const std::wstring& key, const std::wstring& path);

	StructureStage* GetStructureStage(const std::wstring& key) { return _structureStages[key]; }
	StructureStage* LoadStructureStage(const std::wstring& key, const std::wstring& path);

	PlayerStat* GetPlayerStat() { return _playerStat; }
	PlayerStat* LoadPlayerStat(const std::wstring& path);

	TiredOfficeWorkerStat* GetTiredOfficeWorkerStat() { return _tiredOfficeWorkerStat; }
	TiredOfficeWorkerStat* LoadTiredOfficeWorkerStat(const std::wstring& path);

	BrokenCopyMachineStat* GetBrokenCopyMachineStat() { return _brokenCopyMachineStat; }
	BrokenCopyMachineStat* LoadBrokenCopyMachineStat(const std::wstring& path);

	AmateurFencerStat* GetAmateurFencerStat() { return _amateurFencerStat; }
	AmateurFencerStat* LoadAmateurFencerStat(const std::wstring& path);

	FinalBossStat* GetFinalBossStat() { return _finalBossStat; }
	FinalBossStat* LoadFinalBossStat(const std::wstring& path);

private:
	HWND _hwnd;
	std::filesystem::path _resourcePath;

	// Resources
	std::unordered_map<std::wstring, Texture*> _textures;
	std::unordered_map<std::wstring, Sprite*> _sprites;
	std::unordered_map<std::wstring, Flipbook*> _flipbooks;
	std::unordered_map<std::wstring, Sound*> _sounds;
	std::unordered_map<std::wstring, Tilemap*> _tilemaps;
	std::unordered_map<std::wstring, Dialogue*> _dialogues;
	std::unordered_map<std::wstring, Item*> _items;
	std::unordered_map<std::wstring, Stage*> _stages;
	std::unordered_map<std::wstring, ItemStage*> _itemStages;
	std::unordered_map<std::wstring, StructureStage*> _structureStages;
	PlayerStat* _playerStat;
	TiredOfficeWorkerStat* _tiredOfficeWorkerStat;
	BrokenCopyMachineStat* _brokenCopyMachineStat;
	AmateurFencerStat* _amateurFencerStat;
	FinalBossStat* _finalBossStat;
};

