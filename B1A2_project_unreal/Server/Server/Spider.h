#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType);
	~Spider();

public:
	virtual void Update(Room* room) override;

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:
	PauseState* _pause;
	/*MakeWebState* _makeWeb;
	ReturnState* _return;*/

	unsigned char _currentWebCount;

	SpiderStatus _status;
};