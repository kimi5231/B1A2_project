#pragma once
class Quest
{
public:
	Quest();
	virtual ~Quest();

public:
	virtual void UpdateQuest(int currentStage) {};
	bool IsNeed(ItemType itemType);
	bool IsClear() const { return _currentCollectCount == _goalCollectCount; }

	void AddCollectCount() { _currentCollectCount++; }

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