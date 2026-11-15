#include "pch.h"
#include "Spider.h"
#include "FSM.h"
#include "State.h"
#include "Room.h"
#include "Global.h"

Spider::Spider(MonsterType monsterType, Room* ownerRoom)
	: Monster(monsterType, ownerRoom)
{
	// Status 초기화
	SpiderStat stat = g_dataManager->GetSpiderStat();
	_maxHP = stat.hp;
	_hp = _maxHP;
	_isInvincible = stat.isInvincible;

	_returnSpeed = stat.returnSpeed;
	_roamingSpeed = stat.roamingSpeed;
	_chaseSpeed = stat.chaseSpeed;

	_idleTime = stat.idleTime;
	_roamingTime = stat.roamingTime;
	_chaseTime = stat.chaseTime;

	_aggroRange = stat.aggroRange;
	_aggroAngle = stat.aggroAngle;
	_aggroHeight = stat.aggroHeight;
	_attackRange = stat.attackRange;
	_attackAngle = stat.attackAngle;
	_attackHeight = stat.attackHeight;

	_attackDelay = stat.attackDelay;

	_damage = stat.damage;

	_makeWebTime = stat.makeWebTime;
	_maxWebCount = stat.maxWebCount;
	_currentWebCount = 0;

	_power = stat.power;

	_size = g_dataManager->GetMonsterSize(MonsterType::Spider);

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

void Spider::Update()
{
	Monster::Update();

	// 공격 범위 안에 플레이어가 있는지 확인
	const std::array<Player*, MAX_PLAYER>& players = _ownerRoom->GetPlayers();
	if (std::chrono::steady_clock::now() > _nextAttackTime)
	{
		for (auto& player : players)
		{
			if (player->GetObjectPoolState() == ObjectPoolState::Reusable || player->GetState() == ObjectState::DEAD)
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
		if (player->GetObjectPoolState() == ObjectPoolState::Reusable || player->GetState() == ObjectState::DEAD)
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
		return _sumTime > _roamingTime && _path.empty();
	case ObjectState::MAKE_WEB:
		return _sumTime > _makeWebTime;
	case ObjectState::CHASE:
		//return false;
		return _sumTime > _chaseTime;
	case ObjectState::RETURN:
		return (_returnPos - _pos).Length() < TileSize * 2;
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
	//std::cout << "Spider " << _id << " created a web. Current web count: " << _currentWebCount << " Pos: (" << _pos.x << ", " << _pos.y << ", " << _pos.z << ")" << std::endl;
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