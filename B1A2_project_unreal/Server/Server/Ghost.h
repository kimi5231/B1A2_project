#pragma once
#include "Monster.h"

class Ghost : public Monster
{
public:
	Ghost(MonsterType monsterType, Room* ownerRoom);
	~Ghost();

	virtual void Update(Room* room) override;

public:
	virtual bool IsReadyNextState() override;
	void AddLookCount() { _lookCount++; }
	void AddUnlookCount() { _unlookCount++; }

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	float GetAbsentTime() { return _absentTime; }

private:
	float _waitTime;
	float _absentTime;
	float _staringTime;

	unsigned char _lookCount;
	unsigned char _unlookCount;
};