#pragma once

class Stat;
class Stage;

class DataManager
{
public:
	DECLARE_SINGLE(DataManager);

	~DataManager();

public:
	void Init(std::filesystem::path dataPath);
	void Clear();

	Stat* GetStat() { return _stat; }
	Stat* LoadStat();

	Stage* GetStage(int32 stageNum) { return _stages[stageNum]; }
	void LoadStages();

private:
	std::filesystem::path _dataPath;

	Stat* _stat;
	std::unordered_map<int32, Stage*> _stages;
};