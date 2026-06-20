#include "pch.h"
#include "TrashCollector.h"
#include "FSM.h"
#include "State.h"
#include "Item.h"
#include "Room.h"

TrashCollector::TrashCollector(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status 초기화
	_maxHP = 80;
	_hp = _maxHP;
	_isInvincible = false;

	_moveSpeed = 400.f;
	_roamingSpeed = 300.f;
	_chaseSpeed = 460.f;
	_escapeSpeed = 520.f;
	_idleTime = 2.f;
	_roamingTime = 40.f;
	_chaseTime = 7.f;

	_escapeDistance = 2500;

	_aggroRange = {600, 600, 300};
	_attackRange = {70, 140, 140};

	_attackDelay = 3.f;
	_damage = 20;

	_power = 2;

	_size = { 62, 75, 119 };

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
	_stateTable[HIT] = CHASE;
}

TrashCollector::~TrashCollector()
{
}

void TrashCollector::Update(Room* room)
{
	Monster::Update(room);

	if (_state != ObjectState::ESCAPE)
	{
		const std::array<Player*, MAX_PLAYER>& players = room->GetPlayers();

		// 공격 범위 안에 플레이어가 있는지 확인
		if (std::chrono::steady_clock::now() > _nextAttackTime)
		{
			for (auto& player : players)
			{
				if (player->GetObjectPoolState() == ObjectPoolState::Reusable || player->GetState() == ObjectState::DEAD)
					continue;

				// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
				if (CheckInclude(player->GetPos(), _attackRange))
				{
					_target = player;
					SetState(ObjectState::ATTACK);
					return;
				}
			}
		}

		// 인식 범위 안에 플레이어가 있는지 확인
		for (auto& player : players)
		{
			if (player->GetObjectPoolState() == ObjectPoolState::Reusable || player->GetState() == ObjectState::DEAD)
				continue;

			// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
			if (CheckInclude(player->GetPos(), _aggroRange) && 0 < _currentScrap.size() && _currentScrap.size() < _maxScrapCount)
			{
				_target = player;
				SetState(ObjectState::CHASE);
				return;
			}

			// 플레이어가 있으면서 Angry면 Escape
			if (CheckInclude(player->GetPos(), _aggroRange) && player->GetCurrentEmotion() == Emotion::Angry)
			{
				SetState(ObjectState::ESCAPE);
				return;
			}
		}
	
		// 인식 범위 안에 아이템이 있는지 확인
		if (_currentScrap.size() != _maxScrapCount && _state != ObjectState::COLLECT)
		{
			const std::array<Item*, MAX_ITEM>& items = room->GetItems();

			for (auto& item : items)
			{
				if (item->GetObjectPoolState() == ObjectPoolState::Reusable || item->GetObjectPoolState() == ObjectPoolState::InInventory)
					continue;

				// 아이템이 있으면, 아이템 위치를 타겟으로 설정
				if (CheckInclude(item->GetPos(), _aggroRange))
				{
					_targetScrap = item;
					SetState(ObjectState::MOVE);
					return;
				}
			}
		}
	}
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
		return (_targetScrap->GetPos() - _pos).Length() < TileSize * 2 || _targetScrap->GetObjectPoolState() == ObjectPoolState::InInventory || _targetScrap->GetObjectPoolState() == ObjectPoolState::Reusable;
	case ObjectState::COLLECT:
		return true;
	case ObjectState::ESCAPE:
		return _cubePath.size() <= 1;
	case ObjectState::ATTACK:
		return true;
	case ObjectState::HIT:
		if (_currentScrap.size() == _maxScrapCount)
		{
			SetState(ObjectState::ESCAPE, true);
			return false;
		}

		return true;
	}
}

bool TrashCollector::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::MOVE:
		_fsm->ChangeState(g_moveState, this);
		break;
	case ObjectState::COLLECT:
		_fsm->ChangeState(g_collectState, this);
		break;
	case ObjectState::ESCAPE:
		_fsm->ChangeState(g_escapeState, this);
		break;
	}

	return true;
}