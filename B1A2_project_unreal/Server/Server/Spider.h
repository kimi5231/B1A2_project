#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType);
	~Spider();

public:
	virtual void Update(Room* room) override;

	void AddWebCount() { _currentWebCount++; }

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:
	float _makeWebTime;
	unsigned char _maxWebCount;
	unsigned char _currentWebCount;
};