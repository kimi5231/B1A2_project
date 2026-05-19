#pragma once
#include "Monster.h"

class PollutionMonitor : public Monster
{
public:
	PollutionMonitor(MonsterType monsterType, Room* ownerRoom);
	virtual ~PollutionMonitor();

	virtual void Update(Room* room) override;

public:
	virtual bool IsReadyNextState() override;

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	float GetCheckTime() { return _checkTime; }
	int GetFearCount() { return _fearCount; }
	int GetSurpriseCount() { return _surpriseCount; }

private:
	float _checkTime;
	float _spawnTime;
	int _surpriseCount;
	int _fearCount;
};