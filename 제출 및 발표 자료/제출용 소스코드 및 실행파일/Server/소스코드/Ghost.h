#pragma once
#include "Monster.h"

class Ghost : public Monster
{
public:
	Ghost(MonsterType monsterType, Room* ownerRoom);
	~Ghost();

	virtual void Update() override;

public:
	virtual bool IsReadyNextState() override;
	void AddLookCount() { _lookCount++; }
	void AddUnlookCount() { _unlookCount++; }

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	float GetAbsentTime() { return _absentTime; }
	int GetLookCount() { return _lookCount; }
	int GetUnlookCount() { return _unlookCount; }
	bool GetCheckLooking() { return _checkLooking; }
	void SetCheckLooking(bool checkLooking) { _checkLooking = checkLooking; }

private:
	float _waitTime;
	float _absentTime;
	float _staringTime;

	int _lookCount;
	int _unlookCount;

	bool _checkLooking;
};