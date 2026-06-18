#pragma once
class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadQuota();
	void LoadCubeConditionInfos();
	void LoadCubeInfos();
	void LoadCubeTilemaps();
	void LoadMainQuestInfos();
	void LoadSubQuestInfos();
	void LoadItemInfos();
	void LoadPlayerStat();
	void LoadSpiderStat();
	void LoadEmotionGameStat();
	void LoadGhostStat();
	void LoadPollutionMonitorStat();
	void LoadTrashCollectorStat();

public:
	const Quota& GetQuota() { return _quota; }
	const CubeConditionInfo& GetCubeConditionInfo(Difficulty current, Difficulty detail) { return _cubeConditionInfos[{current, detail}]; }
	const CubeInfo& GetCubeInfo(CubeType type) { return _cubeInfos[type]; }
	const std::vector<std::vector<std::vector<short>>>& GetTilemap(CubeType type) { return _cubeTilemaps[type]; }
	const MainQuestInfo& GetMainQuestInfo(int id) { return _mainQuestInfos[id]; }
	const SubQuestInfo& GetSubQuestInfo(int id) { return _subQuestInfos[id]; }
	const ItemInfo& GetItemInfo(ItemType type) { return _itemInfos[type]; }
	const PlayerStat& GetPlayerStat() { return _playerStat; }
	const SpiderStat& GetSpiderStat() { return _spiderStat; }
	const EmotionGameStat& GetEmotionGameStat() { return _emotionGameStat; }
	const GhostStat& GetGhostStat() { return _ghostStat; }
	const PollutionMonitorStat& GetPollutionMonitorStat() { return _pollutionMonitorStat; }
	const TrashCollectorStat& GetTrashCollectorStat() { return _trashCollectorStat; }
	const VectorInt& GetMonsterSize(MonsterType type) { return _monsterSizes[type]; }

private:
	std::filesystem::path _dataPath;

	Quota _quota;
	std::map<std::pair<Difficulty, Difficulty>, CubeConditionInfo> _cubeConditionInfos;
	std::unordered_map<CubeType, CubeInfo> _cubeInfos;
	std::unordered_map<CubeType, std::vector<std::vector<std::vector<short>>>> _cubeTilemaps;
	std::vector<MainQuestInfo> _mainQuestInfos;
	std::vector<SubQuestInfo> _subQuestInfos;
	std::unordered_map<ItemType, ItemInfo> _itemInfos;

	PlayerStat _playerStat;
	SpiderStat _spiderStat;
	EmotionGameStat _emotionGameStat;
	GhostStat _ghostStat;
	PollutionMonitorStat _pollutionMonitorStat;
	TrashCollectorStat _trashCollectorStat;

	std::unordered_map<MonsterType, VectorInt> _monsterSizes;
};