#pragma once

class Stat;

class DataManager
{
public:
	DECLARE_SINGLE(DataManager);

	~DataManager();

public:
	void Init(std::filesystem::path dataPath);
	void Clear();

	const Stat* GetStat() { return _stat; }
	Stat* LoadStat();

private:
	std::filesystem::path _dataPath;

	Stat* _stat;
};