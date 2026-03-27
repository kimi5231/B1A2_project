#pragma once
#include "GameObject.h"
#include "State.h"

class FSM;

class Monster : public GameObject
{
public:
	Monster();
	~Monster();

public:
	void Update(const std::vector<CubeRef>& gameRooms);

public:
	virtual void SetState(ObjectState state) override;

protected:
	FSM* _fsm;

	// °øÅë State
	IdleState* _idle;
	RoamingState* _roaming;
	OpenDoorState* _openDoor;
	ChaseState* _chase;
	AttackState* _attack;
	HitState* _hit;
	DeadState* _dead;
};