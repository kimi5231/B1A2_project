#include "pch.h"
#include "Spider.h"
#include "FSM.h"
#include "State.h"
#include "Room.h"

Spider::Spider(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status 초기화
	_maxHP = 60;
	_hp = 60;

	_speed = 250.f;
	_chaseSpeed = 400.f; 
	_idleTime = 1.5f;
	_roamingTime = 2.5f;
	_chaseTime = 5.f;

	_aggroRange = 400;
	_aggroAngle = 120.f;
	_aggroHeight = 400;
	_attackRange = 150;
	_attackAngle = 90.f;
	_attackHeight = 400;

	_attackDelay = 1.f;

	_damage = 15;

	_makeWebTime = 1.5f;
	_maxWebCount = 8;
	_currentWebCount = 0;

	_power = 1;

	_size = { 80, 80, 80 };

	// State Table
	_stateTable[IDLE] = ROAMING;
	_stateTable[ROAMING] = MAKE_WEB;
	_stateTable[MAKE_WEB] = IDLE;
	_stateTable[CHASE] = RETURN;
	_stateTable[RETURN] = IDLE;
	_stateTable[ATTACK] = CHASE;
	_stateTable[HIT] = CHASE;
}

Spider::~Spider()
{

}

void Spider::Update(Room* room)
{
	Monster::Update(room);

	// 공격 범위 안에 플레이어가 있는지 확인
	const std::array<Player*, MAX_PLAYER>& players = room->GetPlayers();
	if (std::chrono::steady_clock::now() > _nextAttackTime)
	{
		for (auto& player : players)
		{
			if (player->GetObjectPoolState() == ObjectPoolState::Reusable)
				continue;

				// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
			if (CheckInclude(player->GetPos(), _attackRange, _attackAngle, _attackHeight))
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
		if (player->GetObjectPoolState() == ObjectPoolState::Reusable)
			continue;

		// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
		if (CheckInclude(player->GetPos(), _aggroRange, _aggroAngle, _aggroHeight))
		{
			_target = player;
			_returnPos = _pos;
			_returnCubeID = _currentCubeID;
			SetState(ObjectState::CHASE);
			return;
		}
	}
}

bool Spider::IsReadyNextState()
{
	switch (_state)
	{
	case ObjectState::IDLE:
		return _currentWebCount < _maxWebCount && _sumTime > _idleTime;
	case ObjectState::ROAMING:
		return _sumTime > _roamingTime;
	case ObjectState::MAKE_WEB:
		return _sumTime > _makeWebTime;
	case ObjectState::CHASE:
		return _sumTime > _chaseTime;
	case ObjectState::RETURN:
		return _returnPos == _pos;
	case ObjectState::ATTACK:
		return true;
	case ObjectState::HIT:
		return true;
	}
}

void Spider::CreateWeb()
{
	_ownerRoom->AddObstacle(ObstacleType::Web, _pos, _rotation);
	_currentWebCount++;
	std::cout << "Spider " << _id << " created a web. Current web count: " << _currentWebCount << " Pos: (" << _pos.x << ", " << _pos.y << ", " << _pos.z << ")" << std::endl;
}

 bool Spider::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::MAKE_WEB:
		_fsm->ChangeState(g_makeWebState, this);
		break;
	case ObjectState::RETURN:
		_fsm->ChangeState(g_returnState, this);
		break;
	}

	return true;
}