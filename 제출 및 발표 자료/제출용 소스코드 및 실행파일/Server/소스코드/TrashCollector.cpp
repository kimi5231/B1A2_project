#include "pch.h"
#include "TrashCollector.h"
#include "FSM.h"
#include "State.h"
#include "Item.h"
#include "Room.h"
#include "Global.h"

TrashCollector::TrashCollector(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status 초기화
	TrashCollectorStat stat = g_dataManager->GetTrashCollectorStat();
	_maxHP = stat.hp;
	_hp = _maxHP;
	_isInvincible = stat.isInvincible;

	_moveSpeed = stat.moveSpeed;
	_roamingSpeed = stat.roamingSpeed;
	_chaseSpeed = stat.chaseSpeed;
	_escapeSpeed = stat.escapeDistance;

	_idleTime = stat.idleTime;
	_roamingTime = stat.roamingTime;
	_chaseTime = stat.chaseTime;

	_escapeDistance = stat.escapeDistance;

	_aggroRange = stat.aggroRange;
	_attackRange = stat.attackRange;

	_attackDelay = stat.attackDelay;
	_damage = stat.damage;

	_power = stat.power;

	_size = g_dataManager->GetMonsterSize(MonsterType::TrashCollector);

	_maxScrapCount = stat.maxScrapCount;
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

void TrashCollector::Update()
{
	Monster::Update();

	if (_state != ObjectState::ESCAPE)
	{
		const std::array<Player*, MAX_PLAYER>& players = _ownerRoom->GetPlayers();

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
			const std::array<Item*, MAX_ITEM>& items = _ownerRoom->GetItems();

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