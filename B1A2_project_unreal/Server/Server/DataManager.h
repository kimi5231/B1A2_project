#pragma once
class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadCubeConditionInfos();
	void LoadCubeInfos();
	void LoadCubeTilemaps();
	void LoadMainQuestInfos();
	void LoadItemInfos();
	void LoadPlayerStat();

public:
	const CubeConditionInfo& GetCubeConditionInfo(Difficulty current, Difficulty detail) { return _cubeConditionInfos[{current, detail}]; }
	const CubeInfo& GetCubeInfo(CubeType type) { return _cubeInfos[type]; }
	const std::vector<std::vector<std::vector<short>>>& GetTilemap(CubeType type) { return _cubeTilemaps[type]; }
	const MainQuestInfo& GetMainQuestInfo(int id) { return _mainQuestInfos[id]; }
	const ItemInfo& GetItemInfo(ItemType type) { return _itemInfos[type]; }
	const PlayerStat& GetPlayerStat() { return _playerStat; }

private:
	std::filesystem::path _dataPath;

	std::map<std::pair<Difficulty, Difficulty>, CubeConditionInfo> _cubeConditionInfos;
	std::unordered_map<CubeType, CubeInfo> _cubeInfos;
	std::unordered_map<CubeType, std::vector<std::vector<std::vector<short>>>> _cubeTilemaps;
	std::vector<MainQuestInfo> _mainQuestInfos;
	std::unordered_map<ItemType, ItemInfo> _itemInfos;

	PlayerStat _playerStat;
};