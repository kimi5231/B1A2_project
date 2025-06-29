#pragma once
class Stat
{
public:
	void LoadPlayerStatFile(std::filesystem::path dataPath);

public:
	Protocol::PlayerStat& GetPlayerStat() { return _playerStat; }

private:
	Protocol::PlayerStat _playerStat;
};