#include "pch.h"
#include "EmotionGame.h"

EmotionGame::EmotionGame(MonsterType monsterType)
	: Monster(monsterType)
{
	// Status √ ±‚»≠
	_hp = 10000;
	_speed = 2.f;
	_chaseSpeed = 3.5f;
	_idleTime = 15.f;
	_roamingTime = 2.f;
	_chaseTime = 4.f;
	_attackDelay = 2.f;
	_damage = 25;

	// State Table
	_stateTable[IDLE] = ROAMING;
	_stateTable[ROAMING] = IDLE;
	_stateTable[CHASE] = RETURN;
	_stateTable[RETURN] = IDLE;
	_stateTable[ATTACK] = CHASE;
	_stateTable[HIT] = CHASE;
}