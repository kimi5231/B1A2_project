#pragma once

class State;
class Room;

class FSM
{
public:
	FSM();
	virtual ~FSM();

public:
	virtual void Update(Monster* monster);
	void ChangeState(State* state, Monster* monster);

public:
	State* GetCurrentState() { return _currentState; }

private:
	State* _currentState;
};