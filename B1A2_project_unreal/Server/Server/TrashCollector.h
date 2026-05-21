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

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

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
	int _currentScrapCount;
};