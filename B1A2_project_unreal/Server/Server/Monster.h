#pragma once
#include "Creature.h"

class FSM;
class Room;

class Monster : public Creature
{
public:
	Monster(MonsterType monsterType, Room* ownerRoom);
	~Monster();

public:
	virtual void Update(Room* room);

public: 
	virtual bool IsReadyNextState() { return false; };

	void UpdatePath(Vector currentGoal, CubeRef goalCube);
	void Move(float speed, ObjectState state);

	const CubeRef SelectRandomConnectedCube(); 
	Vector SelectRandomPosInCube(const CubeRef cube); 

	std::deque<CubeRef> FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms);
	std::deque<VectorInt> FindPath(Vector goal, const CubeRef currentCubeube);
	void ClearPath() { _cubePath.clear(); _path.clear(); }

	VectorInt RotateIndexByDir(VectorInt index, VectorInt max, Dir dir);
	VectorInt PosToIndex(Vector pos, CubeRef cube);
	Vector IndexToPos(VectorInt index, const CubeRef cube);

	bool IsCanGo(VectorInt index, const CubeRef cube);

	CubeRef FindCubeAtWorldPos(VectorInt wp, CubeRef currentCube);
	CubeRef FindCubeAtIndex(VectorInt index, CubeRef currentCube);

	bool IsPointInCube(VectorInt wp, CubeRef cube);

	void AddDeltaTime(float deltaTime) { _sumTime += deltaTime; }
	void InitSumTime() { _sumTime = 0.f; }

	void UpdateNextAttackTime();

public:
	virtual bool SetState(ObjectState state, bool isSend = true) override;
	MonsterType GetMonsterType() { return _monsterType; };
	void SetMonsterType(MonsterType monsterType) { _monsterType = monsterType; };
	std::optional<VectorInt> GetTargetPos() { return _targetPos; }
	void SetTargetPos(std::optional<VectorInt> pos) { _targetPos = pos; }
	Player* GetTarget() { return _target; }
	void SetTarget(Player* target) { _target = target; }
	std::deque<CubeRef>& GetCubePath() { return _cubePath; }
	std::deque<VectorInt>& GetPath() { return _path; }
	unsigned char GetDamage() { return _damage; }
	const std::unordered_map<ObjectState, ObjectState>& GetStateTable() { return _stateTable; }
	int GetReturnCubeID() { return _returnCubeID; }
	void SetReturnCubeID(int id) { _returnCubeID = id; }
	Vector GetReturnPos() { return _returnPos; }
	void SetReturnPos(Vector pos) { _returnPos = pos; }
	Room* GetOwnerRoom() { return _ownerRoom; }
	float GetSumTime() { return _sumTime; }
	float GetReturnSpeed() { return _returnSpeed; }
	float GetRoamingSpeed() { return _roamingSpeed; }
	float GetChaseSpeed() { return _chaseSpeed; }
	int GetPower() { return _power; }
	bool GetIsNeedDoorOpen() { return _isNeedDoorOpen; }
	void SetIsNeedDoorOpen(bool isNeed) { _isNeedDoorOpen = isNeed; }
	Door* GetTargetDoor() { return _targetDoor; }
	void SetTargetDoor(Door* door) { _targetDoor = door; }

protected:
	MonsterType _monsterType;

	FSM* _fsm;
	std::optional<Vector> _targetPos;
	Player* _target;
	Vector _returnPos;
	int _returnCubeID;
	std::deque<CubeRef> _cubePath;
	std::deque<VectorInt> _path;
	bool _isNeedDoorOpen;
	Door* _targetDoor;

	std::unordered_map<ObjectState, ObjectState> _stateTable;

	float _sumTime;
	std::chrono::steady_clock::time_point _nextAttackTime;
	float _attackDelay;

	// Status
	float _returnSpeed;
	float _roamingSpeed;
	float _chaseSpeed;
	float _chaseTime;
	float _idleTime;
	float _roamingTime;
	unsigned char _damage;
	int _power;
};