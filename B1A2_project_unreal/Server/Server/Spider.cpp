#include "pch.h"
#include "Spider.h"
#include "FSM.h"
#include "State.h"
#include "Room.h"

Spider::Spider(MonsterType monsterType)
	: Monster(monsterType)
{
	// Status 초기화
	_speed = 2.5f;
	_chaseSpeed = 4.f;
	_idleTime = 1.5f;
	_roamingTime = 2.5f;

	_aggroRange = 400.f;
	_aggroAngle = 120.f;
	_aggroHeight = 400.f;

	_makeWebTime = 1.5f;
	_maxWebCount = 8;
	_currentWebCount = 0;
}

Spider::~Spider()
{

}

void Spider::Update(Room* room)
{
	Monster::Update(room);

	// 인식 범위 안에 플레이어가 있는지 확인
	const std::unordered_map<uint, PlayerRef>& players = room->GetPlayers();
	for (auto& [id, player] : players)
	{
		/*if (player->GetObjectPoolState() == ObjectPoolState::Reusable)
			continue;*/

		// 플레이어가 있으면, 플레이어 위치를 타겟으로 설정
		if (CheckInclude(player->GetPos(), _aggroRange, _aggroAngle, _aggroHeight))
		{
			_target = player;
			SetState(ObjectState::CHASE);
		}
	}

	if (_state == ObjectState::IDLE && _currentWebCount < _maxWebCount && _sumTime > _idleTime)
	{
		SetState(ObjectState::ROAMING);
		return;
	}

	if (_state == ObjectState::ROAMING && _sumTime > _roamingTime)
	{
		SetState(ObjectState::MAKE_WEB);
		return;
	}

	if (_state == ObjectState::MAKE_WEB && _sumTime > _makeWebTime)
	{
		SetState(ObjectState::IDLE);
		return;
	}
}

void Spider::CreateWeb(Room* room)
{
	room->AddObstacle(ObstacleType::Web, _pos, true);
	_currentWebCount++;
}

 bool Spider::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::MAKE_WEB:
		_fsm->ChangeState(g_makeWebState, dynamic_pointer_cast<Monster>(shared_from_this()));
		break;
	case ObjectState::RETURN:
		//_fsm->ChangeState(_return, this);
		break;
	}

	return true;
}