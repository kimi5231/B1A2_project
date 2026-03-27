#include "pch.h"
#include "Spider.h"
#include "FSM.h"

Spider::Spider()
{
	// State 생성
	_pause = new PauseState();
	_makeWeb = new MakeWebState();
	_openDoor = new OpenDoorState();

	// 초기 상태 설정
	SetState(ObjectState::IDLE);

	// Status 초기화

}

Spider::~Spider()
{

}

void Spider::Update()
{
	
}

void Spider::SetState(ObjectState state)
{
	Monster::SetState(state);

	switch (state)
	{
	case ObjectState::PAUSE:
		_fsm->ChangeState(_pause);
		break;
	case ObjectState::MAKE_WEB:
		_fsm->ChangeState(_makeWeb);
		break;
	case ObjectState::RETURN:
		_fsm->ChangeState(_return);
		break;
	}
}