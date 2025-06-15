#include "pch.h"
#include "DataManager.h"
#include "Stat.h"

DataManager::~DataManager()
{
}

void DataManager::Init(std::filesystem::path dataPath)
{
	_dataPath = dataPath;
}

void DataManager::Clear()
{

}

Stat* DataManager::LoadStat()
{
	Stat* stat = new Stat();

	stat->LoadFile(_dataPath);

	_stat = stat;

	return stat;
}