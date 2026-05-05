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

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;

private:

};