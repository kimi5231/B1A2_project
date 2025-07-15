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
}

void GameObject::Tick()
{
	//
	_dirtyFlag = false;

	Super::Tick();

	if (GET_SINGLE(DialogueManager)->GetIsDialouge())
		return;

	switch (_info.state())
	{
	case IDLE:
		TickIdle();
		break;
	case MOVE:
		TickMove();
		break;
	case DUCK_DOWN:
		TickDuckDown();
		break;
	case DUCK_DOWN_MOVE:
		TickDuckDownMove();
		break;
	case JUMP:
		TickJump();
		break;
	case CLOSE_ATTACK:
		TickCloseAttack();
		break;
	case LONG_ATTACK:
		TickLongAttack();
		break;
	case THRUST:
		TickThrust();
		break;
	case BACK_STEP:
		TickBackStep();
		break;
	case SLASH_WAVE:
		TickSlashWave();
		break;
	case SKILL_READY:
		TickSkillReady();
		break;
	case SKILL_WAITING:
		TickSkillWaiting();
		break;
	case SKILL_END:
		TickSkillEnd();
		break;
	case HANG:
		TickHang();
		break;
	case RELEASE:
		TickRelease();
		break;
	case HIT:
		TickHit();
		break;
	case DEAD:
		TickDead();
		break;
	case CHASE:
		TickChase();
		break;
	case ROAMING:
		TickRoaming();
		break;
	case DASH:
		TickDash();
		break;
	case RETURN:
		TickReturn();
		break;
	case RETURN_IDLE:
		TickReturnIdle();
		break;
	case ON:
		TickOn();
		break;
	case ON2:
		TickOn2();
	case READY:
		TickReady();
		break;
	case OFF:
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
	if (_info.state() == state)
		return;

	_info.set_state(state);
	UpdateAnimation();

	// 상태가 변경되었으므로 업데이트 필요
	_dirtyFlag = true;
}

void GameObject::SetDir(Dir dir)
{
	_info.set_dir(dir);
	UpdateAnimation();

	// 방향이 변경되었으므로 업데이트 필요
	_dirtyFlag = true;
}