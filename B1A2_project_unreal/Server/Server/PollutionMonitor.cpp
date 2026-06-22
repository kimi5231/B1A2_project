#include "pch.h"
#include "PollutionMonitor.h"
#include "FSM.h"
#include "State.h"
#include "Global.h"

PollutionMonitor::PollutionMonitor(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status ÃÊ±âÈ­
	PollutionMonitorStat stat = g_dataManager->GetPollutionMonitorStat();
	_maxHP = stat.hp;
	_hp = _maxHP;
	_isInvincible = stat.isInvincible;
	
	_idleTime = stat.idleTime;
	_checkTime = stat.checkTime;
	_spawnTime = stat.spawnTime;
	
	_damage = stat.damage;
	_power = stat.power;

	_emotionCount = stat.emotionCount;

	_size = g_dataManager->GetMonsterSize(MonsterType::PollutionMonitor);

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

void PollutionMonitor::Update()
{
	Monster::Update();
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