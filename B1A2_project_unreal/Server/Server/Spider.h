#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType);
	~Spider();

	virtual void Update(Room* room) override;

public:
	virtual bool IsReadyNextState() override;
	void CreateWeb(Room* room);

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:
	unsigned short _aggroRange;
	float _aggroAngle;
	unsigned short _aggroHeight;
	unsigned short _attackRange;
	float _attackAngle;
	unsigned short _attackHeight;

	float _attackDelay;

	float _makeWebTime;
	unsigned char _maxWebCount;
	unsigned char _currentWebCount;
};