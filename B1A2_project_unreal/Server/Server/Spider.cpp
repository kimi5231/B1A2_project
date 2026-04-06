#include "pch.h"
#include "Spider.h"
#include "FSM.h"
#include "State.h"

Spider::Spider(MonsterType monsterType)
	: Monster(monsterType)
{
	// State 생성
	_pause = new PauseState();
	/*_makeWeb = new MakeWebState();
	_openDoor = new OpenDoorState();*/

	// Status 초기화
	_status.maxWebCount = 15;
	_status.pauseTime = 1.5;
	_status.roamingTime = 2.5;
	_currentWebCount = 0;
}

Spider::~Spider()
{

}

void Spider::Update(Room* room)
{
	Monster::Update(room);

	if (_state == ObjectState::IDLE && _currentWebCount < _status.maxWebCount)
	{
		SetState(ObjectState::PAUSE);
		return;
	}
	
	if (_state == ObjectState::PAUSE)
	{
		PauseState* state = dynamic_cast<PauseState*>(_fsm->GetCurrentState());
		auto duration = std::chrono::steady_clock::now() - state->GetStart();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
		if (seconds > _status.pauseTime)
		{
			SetState(ObjectState::ROAMING);
			return;
		}
	}

	if (_state == ObjectState::ROAMING)
	{
		RoamingState* state = dynamic_cast<RoamingState*>(_fsm->GetCurrentState());
		auto duration = std::chrono::steady_clock::now() - state->GetStart();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
		if (seconds > _status.roamingTime)
		{
			SetState(ObjectState::MAKE_WEB);
			return;
		}
	}
}

 bool Spider::SetState(ObjectState state, bool isSend)
{
	if (!Monster::SetState(state, isSend))
		return false;

	switch (state)
	{
	case ObjectState::PAUSE:
		_fsm->ChangeState(_pause, dynamic_pointer_cast<Monster>(shared_from_this()));
		break;
	/*case ObjectState::MAKE_WEB:
		_fsm->ChangeState(_makeWeb, this);
		break;
	case ObjectState::RETURN:
		_fsm->ChangeState(_return, this);
		break;*/
	}

	return true;
}