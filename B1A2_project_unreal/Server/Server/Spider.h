#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType, Room* ownerRoom);
	~Spider();

	virtual void Update() override;

public:
	virtual bool IsReadyNextState() override;
	void CreateWeb();

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:
	int _aggroRange;
	float _aggroAngle;
	int _aggroHeight;
	int _attackRange;
	float _attackAngle;
	int _attackHeight;

	float _makeWebTime;
	int _maxWebCount;
	int _currentWebCount;
};