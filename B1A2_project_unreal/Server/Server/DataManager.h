#pragma once
class DataManager
{
public:
	DataManager();
	~DataManager() {}

public:
	void LoadGameRoomInfos();

public:
	const GameRoomInfo& GetGameRoomInfo(GameRoomType type) { return _gameRoomInfos[type]; }

private:
	std::filesystem::path _dataPath;

	std::unordered_map<GameRoomType, GameRoomInfo> _gameRoomInfos;
};