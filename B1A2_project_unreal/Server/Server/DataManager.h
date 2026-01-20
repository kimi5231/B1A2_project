#pragma once

class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadGameRoomConditionInfos();
	void LoadGameRoomInfos();

public:
	const GameRoomConditionInfo& GetGameRoomConditionInfo(Difficulty current, Difficulty detail) { return _gameRoomconditionInfos[{current, detail}]; }
	const GameRoomInfo& GetGameRoomInfo(GameRoomType type) { return _gameRoomInfos[type]; }

private:
	std::filesystem::path _dataPath;

	std::map<std::pair<Difficulty, Difficulty>, GameRoomConditionInfo> _gameRoomconditionInfos;
	std::unordered_map<GameRoomType, GameRoomInfo> _gameRoomInfos;
};