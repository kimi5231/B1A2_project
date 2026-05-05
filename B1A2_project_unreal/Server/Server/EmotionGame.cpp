#include "pch.h"
#include "EmotionGame.h"
#include "FSM.h"
#include "State.h"

EmotionGame::EmotionGame(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status ÃÊ±âÈ­
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

bool EmotionGame::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _sumTime > _idleTime;
	}
}

bool EmotionGame::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::TELEPORT:
		_fsm->ChangeState(g_teleportState, dynamic_pointer_cast<Monster>(shared_from_this()));
		break;
	}

	return true;
}