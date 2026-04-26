#pragma once
class State
{
public:
	State() {};
	virtual ~State() {};

public:
	virtual void Enter(MonsterRef monster) = 0;
	virtual void Tick(MonsterRef monster, Room* room) = 0;
	virtual void Exit(MonsterRef monster) = 0;
};

extern class IdleState* g_idleState;
extern class RoamingState* g_roamingState;

// Common State
class IdleState : public State
{
public:
	IdleState() {};
	virtual ~IdleState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};

class RoamingState : public State
{
public:
	RoamingState() {};
	virtual ~RoamingState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};

//class OpenDoorState : public State
//{
//public:
//	OpenDoorState() {};
//	virtual ~OpenDoorState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};
//
//class ChaseState : public State
//{
//public:
//	ChaseState() {};
//	virtual ~ChaseState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};
//
//class AttackState : public State
//{
//public:
//	AttackState() {};
//	virtual ~AttackState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};
//
//class HitState : public State
//{
//public:
//	HitState() {};
//	virtual ~HitState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};
//
//class DeadState : public State
//{
//public:
//	DeadState() {};
//	virtual ~DeadState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};

// Spider State
class MakeWebState : public State
{
public:
	MakeWebState() {};
	virtual ~MakeWebState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};

//class ReturnState : public State
//{
//public:
//	ReturnState() {};
//	virtual ~ReturnState() {};
//
//public:
//	virtual void Enter() override {};
//	virtual void Tick() override {};
//	virtual void Exit() override {};
//};