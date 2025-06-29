#include "pch.h"
#include "DataManager.h"
#include "Stat.h"
#include "Stage.h"

DataManager::~DataManager()
{
}

void DataManager::Init(std::filesystem::path dataPath)
{
	_dataPath = dataPath;

	LoadStat();
	LoadStages();
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

void DataManager::LoadStages()
{
	// Stage1
	{
		Stage* stage = new Stage();
		stage->LoadFieldMonster(_dataPath, L"Stage1_FieldMonster.csv");

		_stages[1] = stage;
	}
	
	// Stage2

}