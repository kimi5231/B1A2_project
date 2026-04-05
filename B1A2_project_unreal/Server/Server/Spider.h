#pragma once
#include "Monster.h"

class Spider : public Monster
{
public:
	Spider(MonsterType monsterType);
	~Spider();

public:
	virtual void Update() override;

public:
	virtual bool SetState(ObjectState state) override;

private:
	PauseState* _pause;
	MakeWebState* _makeWeb;
	ReturnState* _return;

	SpiderStatus _status;
};