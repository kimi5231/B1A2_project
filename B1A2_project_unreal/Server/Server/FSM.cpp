#include "pch.h"
#include "FSM.h"
#include "State.h"

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::Update()
{
	if (_currentState)
		_currentState->Tick();
}

void FSM::ChangeState(State* state)
{
	if (_currentState == state || state == nullptr)
		return;

	if(_currentState)
		_currentState->Exit();
	_currentState = state;
	_currentState->Enter();
}