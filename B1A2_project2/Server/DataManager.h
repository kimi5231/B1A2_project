#pragma once
#include "Stat.h"

class DataManager
{
public:
	DECLARE_SINGLE(DataManager);

	~DataManager();

public:
	void Init(std::filesystem::path dataPath);
	void Clear();

	Stat& GetStat() { return _stat; }
	Stat& LoadStat();

private:
	std::filesystem::path _dataPath;

	Stat _stat;
};