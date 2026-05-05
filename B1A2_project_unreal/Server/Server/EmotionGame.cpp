#include "pch.h"
#include "EmotionGame.h"

EmotionGame::EmotionGame(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status √ ±‚»≠
	_hp = 10000;
	_idleTime = 15.f;
	_damage = 25;

	// State Table
	_stateTable[IDLE] = TELEPORT;
	_stateTable[TELEPORT] = IDLE;
	_stateTable[GRAB] = PLAY;
	_stateTable[WIN] = RELEASE;
	_stateTable[LOSE] = RELEASE;
	_stateTable[DRAW] = RELEASE;
}

EmotionGame::~EmotionGame()
{
}

void EmotionGame::Update(Room* room)
{
	Monster::Update(room);
}