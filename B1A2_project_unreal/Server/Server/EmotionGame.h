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

private:

};