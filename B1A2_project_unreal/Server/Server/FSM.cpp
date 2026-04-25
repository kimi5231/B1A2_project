#include "pch.h"
#include "FSM.h"
#include "State.h"

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::Update(MonsterRef monster, Room* room)
{
	if (_currentState)
		_currentState->Tick(monster, room);
}

void FSM::ChangeState(State* state, MonsterRef monster)
{
	if (_currentState == state || state == nullptr)
		return;

	if(_currentState)
		_currentState->Exit();
	_currentState = state;
	_currentState->Enter(monster);
}