#pragma once

class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadGameRoomConditionInfos();
	void LoadGameRoomInfos();
	void LoadGameRoomTilemaps();

public:
	const CubeConditionInfo& GetGameRoomConditionInfo(Difficulty current, Difficulty detail) { return _gameRoomconditionInfos[{current, detail}]; }
	const CubeInfo& GetCubeInfo(CubeType type) { return _gameRoomInfos[type]; }
	const std::vector<std::vector<std::vector<short>>>& GetTilemap(CubeType type) { return _gameRoomTilemaps[type]; }

private:
	std::filesystem::path _dataPath;

	std::map<std::pair<Difficulty, Difficulty>, CubeConditionInfo> _gameRoomconditionInfos;
	std::unordered_map<CubeType, CubeInfo> _gameRoomInfos;
	std::unordered_map<CubeType, std::vector<std::vector<std::vector<short>>>> _gameRoomTilemaps;
};