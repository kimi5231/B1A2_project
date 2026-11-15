#include "pch.h"
#include "Ghost.h"
#include "Player.h"
#include "FSM.h"
#include "State.h"
#include "Global.h"

Ghost::Ghost(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	GhostStat stat = g_dataManager->GetGhostStat();
	_isInvincible = stat.isInvincible;
	_chaseSpeed = stat.chaseSpeed;
	_idleTime = stat.idleTime;
	_chaseTime = stat.chaseTime;
	_waitTime = stat.waitTime;
	_absentTime = stat.absentTime;
	_staringTime = stat.staringTime;
	_damage = stat.damage;
	_power = stat.power;

	_lookCount = 0;
	_unlookCount = 0;
	_checkLooking = false;

	_size = g_dataManager->GetMonsterSize(MonsterType::Ghost);
	_box.SetBounds(_pos, _size, Front);

	// State Table
	_stateTable[IDLE] = ABSENT;
	_stateTable[ABSENT] = STARING;
	_stateTable[STARING] = VANISHING;
	_stateTable[CHASE] = VANISHING;
	_stateTable[VANISHING] = IDLE;
}

Ghost::~Ghost()
{
}

void Ghost::Update()
{
	Monster::Update();

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
		if (_target->CheckCollision(_box))
		{
			_target->TackDamage(_damage);
			g_network->SendUpdateHpPacket(_target->GetID(), _target->GetHP(), _target->GetClient());
			return true;
		}

		return _sumTime > _chaseTime || 3000 <= (_target->GetPos() - _pos).Length();
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
	}

	return true;
}