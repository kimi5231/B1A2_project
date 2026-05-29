#pragma once
class Quest
{
public:
	Quest();
	virtual ~Quest();

public:
	bool IsClear() { return _currentCollectCount == _goalCollectCount; }

public:
	int GetID() { return _id; }
	int GetGoalCollectCount() { return _goalCollectCount; }
	int GetCurrentCollectCount() { return _currentCollectCount; }
	ItemType GetCollectItemType() { return _collectItemType; }
	ItemType GetRewardItemType() { return _rewardItemType; }
	int GetRewardAmount() { return _rewardAmount; }
	RewardType GetRewardType() { return _rewardType; }

protected:
	int _id;
	int _goalCollectCount;
	int _currentCollectCount;
	ItemType _collectItemType;
	ItemType _rewardItemType;
	int _rewardAmount;
	RewardType _rewardType;
};