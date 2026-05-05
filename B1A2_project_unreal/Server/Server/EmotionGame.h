#pragma once
#include "Monster.h"

class EmotionGame : public Monster
{
public:
	EmotionGame(MonsterType monsterType);
	virtual ~EmotionGame();

	virtual void Update(Room* room) override;

public:

private:

};