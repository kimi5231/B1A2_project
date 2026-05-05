#pragma once

class State;
class Room;

class FSM
{
public:
	FSM();
	virtual ~FSM();

public:
	virtual void Update(MonsterRef monster, Room* room);
	void ChangeState(State* state, MonsterRef monster);

public:
	State* GetCurrentState() { return _currentState; }

private:
	State* _currentState;
};