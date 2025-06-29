#include "pch.h"
#include "DataManager.h"
#include "Stat.h"

DataManager::~DataManager()
{
}

void DataManager::Init(std::filesystem::path dataPath)
{
	_dataPath = dataPath;

	LoadStat();
}

void DataManager::Clear()
{

}

Stat* DataManager::LoadStat()
{
	Stat* stat = new Stat();

	// 필요한 Stat 전부 Load
	stat->LoadPlayerStatFile(_dataPath);

	_stat = stat;

	return stat;
}