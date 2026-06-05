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
extern class TeleportState* g_teleportState;
extern class GrabState* g_grabState;
extern class PlayState* g_playState;
extern class ReleaseState* g_releaseState;
extern class AbsentState* g_absentState;
extern class StaringState* g_staringState;
extern class VanishingState* g_vanishingState;
extern class CheckState* g_checkState;
extern class SpawnState* g_spawnState;
extern class AllAttackState* g_allAttackState;
extern class MoveState* g_moveState;
extern class CollectState* g_collectState;
extern class EscapeState* g_escapeState;

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
	virtual void Enter(Monster* monster) override {};
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
class TeleportState : public State
{
public:
	TeleportState() {};
	virtual ~TeleportState() {};
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class GrabState : public State
{
public:
	GrabState() {};
	virtual ~GrabState() {};
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class PlayState : public State
{
public:
	PlayState() {};
	virtual ~PlayState(){}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class ReleaseState : public State
{
public:
	ReleaseState() {};
	virtual ~ReleaseState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

// Ghost State
class AbsentState : public State
{
public:
	AbsentState() {};
	virtual ~AbsentState() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class StaringState : public State
{
public:
	StaringState() {};
	virtual ~StaringState() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class VanishingState : public State
{
public:
	VanishingState() {};
	virtual ~VanishingState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override {};
};

// PollutionMonitor State
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

// TrashCollector State
class MoveState : public State
{
public:
	MoveState() {};
	virtual ~MoveState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class CollectState : public State
{
public:
	CollectState() {};
	virtual ~CollectState() {}
public:
	virtual void Enter(Monster* monster) override {};
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};

class EscapeState : public State
{
public:
	EscapeState() {};
	virtual ~EscapeState() {}
public:
	virtual void Enter(Monster* monster) override;
	virtual void Tick(Monster* monster) override;
	virtual void Exit(Monster* monster) override;
};