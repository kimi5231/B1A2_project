#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType);
	~Spider();

	virtual void Update(Room* room) override;

public:
	void CreateWeb(Room* room);

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:
	float _aggroRange;
	float _aggroAngle;
	float _aggroHeight;

	float _makeWebTime;
	unsigned char _maxWebCount;
	unsigned char _currentWebCount;
};