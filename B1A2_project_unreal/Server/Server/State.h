#pragma once
class State
{
public:
	State() {};
	virtual ~State() {};

public:
	virtual void Enter(MonsterRef monster) = 0;
	virtual void Tick(MonsterRef monster, Room* room);
	virtual void Exit(MonsterRef monster) = 0;
};

extern class IdleState* g_idleState;
extern class RoamingState* g_roamingState;
extern class MakeWebState* g_makeWebState;
extern class ChaseState* g_chaseState;
extern class ReturnState* g_returnState;
extern class AttackState* g_attackState;
extern class HitState* g_hitState;
extern class DeadState* g_deadState;

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

class ChaseState : public State
{
public:
	ChaseState() {};
	virtual ~ChaseState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};

class ReturnState : public State
{
public:
	ReturnState() {};
	virtual ~ReturnState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};

class AttackState : public State
{
public:
	AttackState() {};
	virtual ~AttackState() {};

public:
	virtual void Enter(MonsterRef monster) override;
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

class HitState : public State
{
public:
	HitState() {};
	virtual ~HitState() {};

public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override {};
};

class DeadState : public State
{
public:
	DeadState() {};
	virtual ~DeadState() {};

public:
	virtual void Enter(MonsterRef monster) override;
	virtual void Tick(MonsterRef monster, Room* room) override {};
	virtual void Exit(MonsterRef monster) override {};
};

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

// EmotionGame State
class Teleport : public State
{
public:
	Teleport() {};
	virtual ~Teleport() {};
public:
	virtual void Enter(MonsterRef monster) override {};
	virtual void Tick(MonsterRef monster, Room* room) override;
	virtual void Exit(MonsterRef monster) override;
};