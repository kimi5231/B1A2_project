#include "pch.h"
#include "PollutionMonitor.h"
#include "FSM.h"
#include "State.h"

PollutionMonitor::PollutionMonitor(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status ÃÊ±âÈ­
	_maxHP = 200;
	_hp = _maxHP;
	_idleTime = 120.f;
	_checkTime = 40.f;
	_spawnTime = 30.f;
	_damage = 40;
	_power = 5;

	_emotionCount = 5;

	// State Table
	_stateTable[IDLE] = CHECK;
	_stateTable[CHECK] = SPAWN;
	_stateTable[SPAWN] = ALL_ATTACK;
	_stateTable[ALL_ATTACK] = DEAD;
	_stateTable[HIT] = SPAWN;
}

PollutionMonitor::~PollutionMonitor()
{
}

void PollutionMonitor::Update(Room* room)
{
	Monster::Update(room);
}

bool PollutionMonitor::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _sumTime > _idleTime;
	case ObjectState::SPAWN:
		return _sumTime > _spawnTime;
	case ObjectState::ALL_ATTACK:
		return true;
	case ObjectState::HIT:
		return true;
	}
}

bool PollutionMonitor::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::CHECK:
		_fsm->ChangeState(g_checkState, this);
		break;
	case ObjectState::SPAWN:
		_fsm->ChangeState(g_spawnState, this);
		break;
	case ObjectState::ALL_ATTACK:
		_fsm->ChangeState(g_allAttackState, this);
		break;
	}

	return true;
}