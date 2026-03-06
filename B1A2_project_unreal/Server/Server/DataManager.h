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
	const GameRoomConditionInfo& GetGameRoomConditionInfo(Difficulty current, Difficulty detail) { return _gameRoomconditionInfos[{current, detail}]; }
	const GameRoomInfo& GetGameRoomInfo(GameRoomType type) { return _gameRoomInfos[type]; }
	const std::vector<std::vector<std::vector<short>>>& GetTilemap(GameRoomType type) { return _gameRoomTilemaps[type]; }

private:
	std::filesystem::path _dataPath;

	std::map<std::pair<Difficulty, Difficulty>, GameRoomConditionInfo> _gameRoomconditionInfos;
	std::unordered_map<GameRoomType, GameRoomInfo> _gameRoomInfos;
	std::unordered_map<GameRoomType, std::vector<std::vector<std::vector<short>>>> _gameRoomTilemaps;
};