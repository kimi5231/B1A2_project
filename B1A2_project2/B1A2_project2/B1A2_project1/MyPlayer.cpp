#include "pch.h"
#include "MyPlayer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "NetworkManager.h"
#include "ClientPacketHandler.h"
#include "DialogueComponent.h"
#include "CameraComponent.h"
#include "ZipLine.h"

MyPlayer::MyPlayer()
{
	// Camera Component
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);

	// Dialogue Component
	DialogueComponent* dialogueComponent = new DialogueComponent();
	AddComponent(dialogueComponent);
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void MyPlayer::Tick()
{
	Super::Tick();
}

void MyPlayer::Render(HDC hdc)
{
	Super::Render(hdc);
}

void MyPlayer::TickIdle()
{
	_keyPressed = true;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(JUMP);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(DUCK_DOWN);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		if (_isCloseAtk)
			SetState(CLOSE_ATTACK);
		else
			SetState(LONG_ATTACK);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		if (GetSkillPoint() >= 3)
		{
			SubtractSkillPoint(3);

			_skillTimer = 0.f;

			_leftInputCount = 0;
			_rightInputCount = 0;

			SetState(SKILL_READY);
		}
	}
	else
	{
		_keyPressed = false;

		if (_info.state() == IDLE)
			UpdateAnimation();
	}
}

void MyPlayer::TickMove()
{
	Super::TickMove();

	/*if (GetDialogue()->GetState() == DialogueState::Running || GetDialogue()->GetState() == DialogueState::Wait)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.0f;

	sumTime += deltaTime;*/

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
	}
	else
	{
		// 이동 키를 뗐을 때 Idle 상태로 변경
		SetState(IDLE); 
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		// 이미 점프 중이면 리턴
		if (!_isGround && _isAir)
			return;

		_isGround = false;
		_isAir = true;

		SetState(JUMP);

		_ySpeed = -_playerStat->jumpSpeed;
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))	// Normal Attack
	{
		if (_isCloseAtk)
			SetState(CLOSE_ATTACK);
		else
			SetState(LONG_ATTACK);

	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))	// Skill
	{
		SetState(SKILL_READY);
	}
}

void MyPlayer::TickDuckDown()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A))
	{
		SetDir(DIR_LEFT);
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		SetDir(DIR_RIGHT);
		SetState(DUCK_DOWN_MOVE);
	}
	else if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))
	{
		// S키를 뗐을 때 Idle 상태로 변경
		SetState(IDLE);
	}
}

void MyPlayer::TickDuckDownMove()
{
	Super::TickDuckDownMove();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		SetDir(DIR_LEFT);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		SetDir(DIR_RIGHT);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::A) || GET_SINGLE(InputManager)->GetButtonUp(KeyType::D))
	{
		SetState(DUCK_DOWN);
	}

	if (GET_SINGLE(InputManager)->GetButtonUp(KeyType::S))
	{
		SetState(MOVE);
	}
}

void MyPlayer::TickJump()
{
	// 좌우 이동 가능하도록 추가
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		Super::TickJump();
		SetDir(DIR_LEFT);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		Super::TickJump();
		SetDir(DIR_RIGHT);
	}

	// 땅에 닿았을 때
	if (_isGround && !_isAir)
	{
		if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
		{
			SetDir(DIR_LEFT);
			SetState(MOVE);
		}
		else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		{
			SetDir(DIR_RIGHT);
			SetState(MOVE);
		}
		else
			SetState(IDLE);
	}
	else
	{
		// ZipLine 
		if (_nearZipLine)
		{
			if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
			{
				// 바라보는 방향 설정
				SetDir(DIR_RIGHT);

				_currentZipLine = _nearZipLine;
				SetState(HANG);
			}
		}
	}
}

void MyPlayer::TickCloseAttack()
{
	Super::TickCloseAttack();
}

void MyPlayer::TickLongAttack()
{
	Super::TickLongAttack();
}

void MyPlayer::TickSkillReady()
{
	Super::TickSkillReady();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::A) && _leftInputCount < 5)
	{
		_leftInputCount++;
	}
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D) && _rightInputCount < 5)
	{
		_rightInputCount++;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::RightMouse))
	{
		if (_leftInputCount > 0 || _rightInputCount > 0)
		{
			_skillTimer = 0.f;

			if (_leftInputCount == _rightInputCount)
				SetState(IDLE);
			else
			{
				if (_leftInputCount < _rightInputCount)
					SetDir(DIR_RIGHT);
				else
					SetDir(DIR_LEFT);

				SetState(SKILL_WAITING);
			}
		}
	}
}

void MyPlayer::TickSkillWaiting()
{
	Super::TickSkillWaiting();
}

void MyPlayer::TickSkillEnd()
{
	Super::TickSkillEnd();
}

void MyPlayer::TickHang()
{
	Super::TickHang();

	// 이동 중 SpaceBar 입력 시 놓기
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		_isMoving = false;

		_hangTimer = 0.0f;

		_isGround = false;
		_isAir = true;

		_currentZipLine->SetMidPos(_pos);

		SetState(RELEASE);

		return;
	}
}

void MyPlayer::TickRelease()
{
	Super::TickRelease();
}

void MyPlayer::TickHit()
{
	Super::TickHit();
}

void MyPlayer::TickDead()
{
	Super::TickDead();
}