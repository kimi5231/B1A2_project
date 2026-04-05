#pragma once

class State;

class FSM
{
public:
	FSM();
	virtual ~FSM();

public:
	virtual void Update();
	bool ChangeState(State* state);

private:
	State* _currentState;
};