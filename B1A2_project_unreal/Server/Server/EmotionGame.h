#pragma once
#include "Monster.h"

class Room;

class EmotionGame : public Monster
{
public:
	EmotionGame(MonsterType monsterType, Room* ownerRoom);
	virtual ~EmotionGame();

	virtual void Update(Room* room) override;

public:
	virtual bool IsReadyNextState() override;

	Emotion SelectEmotion();
	void AddLoseCount() { _loseCount++; }

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	int GetHealValue() { return _healValue; }
	void SetResult(EmotionGameResult result) { _result = result; }
	EmotionGameResult GetResult() { return _result; }

private:
	float _playTime;
	float _releaseTime;
	int _loseCount;
	int _healValue;
	int _aggroRange;

	EmotionGameResult _result;
};