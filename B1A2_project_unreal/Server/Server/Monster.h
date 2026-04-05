#pragma once
#include "Creature.h"
#include "State.h"

class FSM;

class Monster : public Creature
{
public:
	Monster(MonsterType monsterType);
	~Monster();

public:
	void Update(const std::vector<CubeRef>& cubes, const std::vector<DoorRef>& doors);

public:
	std::deque<CubeRef> FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms);
	std::deque<VectorInt> FindPath(Vector goal, const CubeRef ccurrentCubeube);
	
	VectorInt WorldToLocalIndex(Vector wp, CubeRef cube);
	Vector IndexToPos(VectorInt index, const CubeRef cube);

	bool IsCanGo(VectorInt index, const CubeRef cube);

	CubeRef FindCubeAtWorldPos(VectorInt wp, CubeRef currentCube);
	CubeRef FindCubeAtIndex(VectorInt index, CubeRef currentCube);

	bool IsPointInCube(VectorInt wp, CubeRef cube);
	virtual bool GetDamage(int damage) override;

public:
	virtual void SetState(ObjectState state) override;
	MonsterType GetMonsterType() { return _monsterType; };
	void SetMonsterType(MonsterType monsterType) { _monsterType = monsterType; };

protected:
	MonsterType _monsterType;

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