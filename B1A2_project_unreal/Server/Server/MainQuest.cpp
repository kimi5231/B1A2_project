#include "pch.h"
#include "MainQuest.h"
#include "Global.h"

MainQuest::MainQuest()
{
}

MainQuest::~MainQuest()
{
}

void MainQuest::UpdateQuest()
{
	MainQuestInfo info = g_dataManager->GetMainQuestInfo(++_id);
	_goalCollectCount = info.targetAmount;
	_currentCollectCount = 0;
	_collectItemType = info.targetItemType;
	_rewardItemType = info.rewardItemType;
	_rewardType = info.rewardType;
}