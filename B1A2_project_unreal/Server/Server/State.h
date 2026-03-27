#pragma once
class State
{
public:
	State() {};
	virtual ~State() {};

public:
	virtual void Enter() = 0;
	virtual void Tick() = 0;
	virtual void Exit() = 0;
};

// Common State
class IdleState : public State
{
public:
	IdleState() {};
	virtual ~IdleState() {};

public:
	virtual void Enter() override;
	virtual void Tick() override;
	virtual void Exit() override;
};

class RoamingState : public State
{
public:
	RoamingState() {};
	virtual ~RoamingState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class OpenDoorState : public State
{
public:
	OpenDoorState() {};
	virtual ~OpenDoorState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class ChaseState : public State
{
public:
	ChaseState() {};
	virtual ~ChaseState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class AttackState : public State
{
public:
	AttackState() {};
	virtual ~AttackState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class HitState : public State
{
public:
	HitState() {};
	virtual ~HitState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class DeadState : public State
{
public:
	DeadState() {};
	virtual ~DeadState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

// Spider State
class PauseState : public State
{
public:
	PauseState() {};
	virtual ~PauseState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class MakeWebState : public State
{
public:
	MakeWebState() {};
	virtual ~MakeWebState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};

class ReturnState : public State
{
public:
	ReturnState() {};
	virtual ~ReturnState() {};

public:
	virtual void Enter() override {};
	virtual void Tick() override {};
	virtual void Exit() override {};
};