#pragma once
class Room;

class State
{
public:
	State() {};
	virtual ~State() {};

public:
	virtual void Enter(Monster* monster) = 0;
	virtual void Tick(Monster* monster);
	virtual void Exit(Monster* monster) = 0;
};

extern class IdleState* g_idleState;
extern class RoamingState* g_roamingState;
extern class ChaseState* g_chaseState;
extern class ReturnState* g_returnState;
extern class AttackState* g_attackState;
extern class HitState* g_hitState;
extern class DeadState* g_deadState;
extern class MakeWebState* g_makeWebState;
extern class Teleport* g_teleportState;
extern class Grab* g_grabState;
extern class Play* g_playState;
extern class Release* g_releaseState;
extern class Absent* g_absentState;
extern class Staring* g_staringState;
extern class Vanishing* g_vanishingState;
extern class CheckState* g_checkState;
extern class SpawnState* g_spawnState;
extern class AllAttackState* g_allAttackState;

// Common State
class IdleState : public State
{
public:
	IdleState() {};
	virtual ~IdleState() {};

public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class RoamingState : public State
{
public:
	RoamingState() {};
	virtual ~RoamingState() {};

public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class ChaseState : public State
{
public:
	ChaseState() {};
	virtual ~ChaseState() {};

public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class ReturnState : public State
{
public:
	ReturnState() {};
	virtual ~ReturnState() {};

public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class AttackState : public State
{
public:
	AttackState() {};
	virtual ~AttackState() {};

public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class HitState : public State
{
public:
	HitState() {};
	virtual ~HitState() {};

public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};

class DeadState : public State
{
public:
	DeadState() {};
	virtual ~DeadState() {};

public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override {};
	virtual void Exit(Monster* monster) override {};
};

// Spider State
class MakeWebState : public State
{
public:
	MakeWebState() {};
	virtual ~MakeWebState() {};

public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

// EmotionGame State
class Teleport : public State
{
public:
	Teleport() {};
	virtual ~Teleport() {};
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class Grab : public State
{
public:
	Grab() {};
	virtual ~Grab() {};
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class Play : public State
{
public:
	Play() {};
	virtual ~Play(){}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class Release : public State
{
public:
	Release() {};
	virtual ~Release() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

// Ghost State
class Absent : public State
{
public:
	Absent() {};
	virtual ~Absent() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class Staring : public State
{
public:
	Staring() {};
	virtual ~Staring() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class Vanishing : public State
{
public:
	Vanishing() {};
	virtual ~Vanishing() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};

// PollutionMonitor
class CheckState : public State
{
public:
	CheckState() {};
	virtual ~CheckState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};

class SpawnState : public State
{
public:
	SpawnState() {};
	virtual ~SpawnState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};

class AllAttackState : public State
{
public:
	AllAttackState() {};
	virtual ~AllAttackState() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};