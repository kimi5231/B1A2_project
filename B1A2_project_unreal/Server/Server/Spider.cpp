#include "pch.h"
#include "Spider.h"
#include "FSM.h"
#include "State.h"

Spider::Spider(MonsterType monsterType)
	: Monster(monsterType)
{
	// Status √ ±‚»≠
	_speed = 2.5f;
	_chaseSpeed = 4.f;
	_idleTime = 1.5f;
	_roamingTime = 2.5f;

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

	std::cout << _sumTime << std::endl;

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

 bool Spider::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	/*case ObjectState::MAKE_WEB:
		_fsm->ChangeState(_makeWeb, this);
		break;
	case ObjectState::RETURN:
		_fsm->ChangeState(_return, this);
		break;*/
	}

	return true;
}