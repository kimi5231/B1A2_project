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
	virtual void Update(Room* room);

public: 
	const CubeRef SelectRandomConnectedCube(Room* room); 
	VectorInt SelectRandomPosInCube(const CubeRef currentCube); 

	std::deque<CubeRef> FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms);
	std::deque<VectorInt> FindPath(Vector goal, const CubeRef ccurrentCubeube);
	
	VectorInt GetRotationIndex(VectorInt index, VectorInt max, Dir dir);
	VectorInt PosToIndex(Vector pos, CubeRef cube);
	Vector IndexToPos(VectorInt index, const CubeRef cube);

	bool IsCanGo(VectorInt index, const CubeRef cube);

	CubeRef FindCubeAtWorldPos(VectorInt wp, CubeRef currentCube);
	CubeRef FindCubeAtIndex(VectorInt index, CubeRef currentCube);

	bool IsPointInCube(VectorInt wp, CubeRef cube);
	virtual bool GetDamage(int damage) override;

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	MonsterType GetMonsterType() { return _monsterType; };
	void SetMonsterType(MonsterType monsterType) { _monsterType = monsterType; };
	VectorInt* GetTargetPos() { return _targetPos; }
	void SetTargetPos(VectorInt* pos) { _targetPos = pos; }

protected:
	MonsterType _monsterType;

	FSM* _fsm;
	VectorInt* _targetPos;
	std::queue<CubeRef> _cubePath;
	std::queue<VectorInt> _path;

	// °øÅë State
	IdleState* _idle;
	RoamingState* _roaming;
	/*OpenDoorState* _openDoor;
	ChaseState* _chase;
	AttackState* _attack;
	HitState* _hit;
	DeadState* _dead;*/
};