#include "pch.h"
#include "MainQuest.h"
#include "Global.h"

MainQuest::MainQuest()
{
	MainQuestInfo info = g_dataManager->GetMainQuestInfo(0);
	_id = 0;
	_goalCollectCount = info.targetAmount;
	_collectItemType = info.targetItemType;
	_rewardItemType = info.rewardItemType;
	_rewardAmount = info.rewardAmount;
	_rewardType = info.rewardType;
}

MainQuest::~MainQuest()
{
}

void MainQuest::ChangeNextQuest()
{
	_id++;

	MainQuestInfo info = g_dataManager->GetMainQuestInfo(_id);
	_goalCollectCount = info.targetAmount;
	_currentCollectCount = 0;
	_collectItemType = info.targetItemType;
	_rewardItemType = info.rewardItemType;
	_rewardType = info.rewardType;
}