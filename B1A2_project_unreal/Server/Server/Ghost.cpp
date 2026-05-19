#include "pch.h"
#include "Ghost.h"
#include "Player.h"
#include "FSM.h"
#include "State.h"

Ghost::Ghost(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	_hp = 10000;
	_chaseSpeed = 4.5f;
	_idleTime = 15.f;
	_chaseTime = 20.f;
	_waitTime = 180.f;
	_absentTime = 4.f;
	_staringTime = 15.f;
	_power = 8;
	_lookCount = 0;
	_unlookCount = 0;
	_checkLooking = false;

	// State Table
	_stateTable[IDLE] = ABSENT;
	_stateTable[ABSENT] = STARING;
	_stateTable[STARING] = VANISHING;
	_stateTable[CHASE] = VANISHING;
}

Ghost::~Ghost()
{
}

void Ghost::Update(Room* room)
{
	// Target Player가 죽었다면, 대기 후 Target 재설정
	if (_target && _target->GetState() == DEAD && _sumTime < _waitTime)
		return;
}

bool Ghost::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _sumTime > _idleTime;
	case ObjectState::ABSENT:
		return _targetPos.has_value();
	case ObjectState::STARING:
		return _sumTime > _staringTime || (_lookCount <= 1 && 200 < (_target->GetPos() - _pos).Length() && (_target->GetPos() - _pos).Length() <= 250) || 1000 < (_target->GetPos() - _pos).Length();
	case ObjectState::CHASE:
		return _sumTime > _chaseTime || 3000 <= (_target->GetPos() - _pos).Length() || _target->CheckCollision(_box);
	case ObjectState::VANISHING:
		return true;
	}
}

bool Ghost::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::ABSENT:
		_fsm->ChangeState(g_absentState, this);
		break;
	case ObjectState::STARING:
		_fsm->ChangeState(g_staringState, this);
		break;
	case ObjectState::VANISHING:
		_fsm->ChangeState(g_vanishingState, this);
		break;
	case ObjectState::CHASE:
		_fsm->ChangeState(g_chaseState, this);
		break;
	}

	return true;
}