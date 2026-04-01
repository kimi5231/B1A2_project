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
	std::deque<CubeRef> FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms);
	std::deque<VectorInt> FindPath(VectorInt goal, const CubeRef ccurrentCubeube);

	VectorInt WorldToLocalIndex(VectorInt wp, CubeRef cube);

	bool IsWalkable(CubeRef cube, VectorInt localIdx);

	CubeRef FindCubeAtWorldPos(VectorInt wp, CubeRef currentCube);

	bool IsPointInCube(VectorInt wp, CubeRef cube);
	std::deque<VectorInt> ReconstructPath(TileNode* goalNode);
	
	float GetDistance(VectorInt a, VectorInt b);

public:
	virtual void SetState(ObjectState state) override;

protected:
	FSM* _fsm;
	VectorInt* _targetPos;
	std::deque<CubeRef> _cubePath;
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