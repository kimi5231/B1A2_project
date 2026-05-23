#pragma once
#include "Monster.h"

class TrashCollector : public Monster
{
public:
	TrashCollector(MonsterType monsterType, Room* ownerRoom);
	~TrashCollector();

	virtual void Update(Room* room) override;

public:
	virtual bool IsReadyNextState() override;

	void AddScrap(int scrapID) { _currentScrap.push_back(scrapID); }

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	Item* GetTargetScrap() { return _targetScrap; }
	void SetTargetScrap(Item* scrap) { _targetScrap = scrap; }
	int GetEscapeDistance() { return _escapeDistance; }

private:
	int _aggroRange;
	int _aggroHeight;
	int _attackWidth;
	int _attackLength;
	int _attackHeight;

	float _moveSpeed;
	float _escapeSpeed;

	int _escapeDistance;

	int _maxScrapCount;
	std::vector<int> _currentScrap;

	Item* _targetScrap;
};