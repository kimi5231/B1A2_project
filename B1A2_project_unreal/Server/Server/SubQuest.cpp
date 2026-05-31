#include "pch.h"
#include "SubQuest.h"
#include "Global.h"

SubQuest::SubQuest()
{
}

SubQuest::~SubQuest()
{
}

void SubQuest::UpdateQuest()
{
	// 랜덤으로 선택
	std::uniform_int_distribution<int> selectQuest(0, 0);
	_id = selectQuest(gen);

	SubQuestInfo info = g_dataManager->GetSubQuestInfo(_id);
	_goalCollectCount = info.targetAmount;
	_currentCollectCount = 0;
	_collectItemType = info.targetItemType;
	_rewardItemType = info.rewardItemType;
	_rewardAmount = info.rewardAmount;
	_rewardType = info.rewardType;
	_deadLine = info.deadLine;
}