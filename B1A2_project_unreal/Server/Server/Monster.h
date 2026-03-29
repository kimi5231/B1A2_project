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
	void Update(const std::vector<CubeRef>& cubes, const std::vector<DoorRef>& doors);

public:
	std::vector<CubeRef> FindCubePath(Vector goal, const std::vector<CubeRef>& gameRooms);
	std::deque<VectorInt> FindPath(VectorInt goal, const CubeRef cube);

public:
	virtual void SetState(ObjectState state) override;

protected:
	FSM* _fsm;
	std::deque<VectorInt> _path;

	// °øÅë State
	IdleState* _idle;
	RoamingState* _roaming;
	OpenDoorState* _openDoor;
	ChaseState* _chase;
	AttackState* _attack;
	HitState* _hit;
	DeadState* _dead;
};