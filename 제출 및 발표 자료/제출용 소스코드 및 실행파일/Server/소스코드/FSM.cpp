#include "pch.h"
#include "FSM.h"
#include "State.h"

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::Update(Monster* monster)
{
	if (_currentState)
		_currentState->Tick(monster);
}

void FSM::ChangeState(State* state, Monster* monster)
{
	if (_currentState == state || state == nullptr)
		return;

	if(_currentState)
		_currentState->Exit(monster);
	_currentState = state;
	_currentState->Enter(monster);
}