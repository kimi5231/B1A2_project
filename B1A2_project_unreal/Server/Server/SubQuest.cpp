#include "pch.h"
#include "SubQuest.h"
#include "Global.h"

SubQuest::SubQuest(int currentStage)
{
	ChangeQuest(currentStage);
}

SubQuest::~SubQuest()
{
}

void SubQuest::ChangeQuest(int currentStage)
{
	_startStage = currentStage;

	// 랜덤으로 선택
	std::uniform_int_distribution<int> selectQuest(0, 0);
	_id = selectQuest(gen);

	SubQuestInfo info = g_dataManager->GetSubQuestInfo(_id);
	_goalCollectCount = info.targetAmount;
	_collectItemType = info.targetItemType;
	_rewardItemType = info.rewardItemType;
	_rewardAmount = info.rewardAmount;
	_rewardType = info.rewardType;
	_deadLine = info.deadLine;
}