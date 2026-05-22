#include "pch.h"
#include "TrashCollector.h"
#include "FSM.h"
#include "State.h"
#include "Item.h"

TrashCollector::TrashCollector(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status ÃÊ±âÈ­
	_maxHP = 80;
	_hp = _maxHP;

	_moveSpeed = 400.f;
	_roamingSpeed = 300.f;
	_chaseSpeed = 460.f;
	_escapeSpeed = 520.f;
	_idleTime = 2.f;
	_roamingTime = 40.f;
	_chaseTime = 7.f;

	_escapeDistance = 2500;

	_aggroRange = 600;
	_aggroHeight = 300;

	_attackWidth = 70;
	_attackLength = 140;
	_attackHeight = 140;

	_attackDelay = 3.f;
	_damage = 20;

	_power = 2;

	_maxScrapCount = 3;
	_currentScrap.reserve(_maxScrapCount);

	_targetScrap = nullptr;

	// State Table
	_stateTable[IDLE] = ROAMING;
	_stateTable[ROAMING] = IDLE;
	_stateTable[CHASE] = IDLE;
	_stateTable[ESCAPE] = IDLE;
	_stateTable[MOVE] = COLLECT;
	_stateTable[COLLECT] = ROAMING;
	_stateTable[ATTACK] = ESCAPE;
	_stateTable[HIT] = ESCAPE;
}

TrashCollector::~TrashCollector()
{
}

void TrashCollector::Update(Room* room)
{
	Monster::Update(room);
}

bool TrashCollector::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _sumTime > _idleTime;
	case ObjectState::ROAMING:
		return _sumTime > _roamingTime;
	case ObjectState::CHASE:
		return _sumTime > _chaseTime;
	case ObjectState::MOVE:
		return _targetScrap->GetObjectPoolState() == ObjectPoolState::InInventory || _targetScrap->GetPos() == _pos;
	case ObjectState::COLLECT:
		return true;
	case ObjectState::ESCAPE:
		return _cubePath.size() <= 1;
	case ObjectState::ATTACK:
		return true;
	case ObjectState::HIT:
		return true;
	}
}

bool TrashCollector::SetState(ObjectState state, bool isSend)
{
	return false;
}