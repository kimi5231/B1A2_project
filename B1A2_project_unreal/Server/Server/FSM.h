#pragma once

class State;

class FSM
{
public:
	FSM();
	virtual ~FSM();

public:
	virtual void Update();
	void ChangeState(State* state);

private:
	State* _currentState;
};