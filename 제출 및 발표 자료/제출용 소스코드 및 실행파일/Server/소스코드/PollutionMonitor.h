#pragma once
#include "Monster.h"

class PollutionMonitor : public Monster
{
public:
	PollutionMonitor(MonsterType monsterType, Room* ownerRoom);
	virtual ~PollutionMonitor();

	virtual void Update() override;

public:
	virtual bool IsReadyNextState() override;

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	float GetCheckTime() { return _checkTime; }
	int GetEmotionCount() { return _emotionCount; }

private:
	float _checkTime;
	float _spawnTime;
	int _emotionCount;
};