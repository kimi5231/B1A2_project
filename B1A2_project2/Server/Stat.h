#pragma once
class Stat
{
public:
	Stat();
	virtual ~Stat();

public:
	void LoadPlayerStatFile(std::filesystem::path dataPath);
	void LoadTiredOfficeWorkerStatFile(std::filesystem::path dataPath);

public:
	Protocol::PlayerStat& GetPlayerStat() { return _playerStat; }
	Protocol::TiredOfficeWorkerStat& GetTiredOfficeWorkerStat() { return _tiredOfficeWorkerStat; }

private:
	Protocol::PlayerStat _playerStat;
	Protocol::TiredOfficeWorkerStat _tiredOfficeWorkerStat;
};