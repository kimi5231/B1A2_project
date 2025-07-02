#include "pch.h"
#include "GameObject.h"
#include "DialogueManager.h"
#include "TimeManager.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::BeginPlay()
{
	Super::BeginPlay();

	// 처음 상태 지정
	SetState(ObjectState::Dead);
	SetState(ObjectState::Idle);
}

void GameObject::Tick()
{
	Super::Tick();

	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;

	switch (_state)
	{
	case ObjectState::Idle:
		TickIdle();
		break;
	case ObjectState::Move:
		TickMove();
		break;
	case ObjectState::DuckDown:
		TickDuckDown();
		break;
	case ObjectState::DuckDownMove:
		TickDuckDownMove();
		break;
	case ObjectState::Jump:
		TickJump();
		break;
	case ObjectState::CloseAttack:
		TickCloseAttack();
		break;
	case ObjectState::LongAttack:
		TickLongAttack();
		break;
	case ObjectState::Thrust:
		TickThrust();
		break;
	case ObjectState::BackStep:
		TickBackStep();
		break;
	case ObjectState::SlashWave:
		TickSlashWave();
		break;
	case ObjectState::SkillReady:
		TickSkillReady();
		break;
	case ObjectState::SkillWaiting:
		TickSkillWaiting();
		break;
	case ObjectState::SkillEnd:
		TickSkillEnd();
		break;
	case ObjectState::Hang:
		TickHang();
		break;
	case ObjectState::Release:
		TickRelease();
		break;
	case ObjectState::Hit:
		TickHit();
		break;
	case ObjectState::Dead:
		TickDead();
		break;
	case ObjectState::Chase:
		TickChase();
		break;
	case ObjectState::Roaming:
		TickRoaming();
		break;
	case ObjectState::Dash:
		TickDash();
		break;
	case ObjectState::Return:
		TickReturn();
		break;
	case ObjectState::ReturnIdle:
		TickReturnIdle();
		break;
	case ObjectState::On:
		TickOn();
		break;
	case ObjectState::On2:
		TickOn2();
	case ObjectState::Ready:
		TickReady();
		break;
	case ObjectState::Off:
		TickOff();
		break;
	}
}

void GameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameObject::TickGravity()
{
	// 땅에 닿아있으면 중력 적용 X
	if (_isGround)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (deltaTime > 0.1f)
		return;

	// v = at
	// s = vt

	_ySpeed += _gravity * deltaTime;
	_pos.y += _ySpeed * deltaTime;
}

void GameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void GameObject::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}