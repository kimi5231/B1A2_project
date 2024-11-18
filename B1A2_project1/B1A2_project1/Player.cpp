#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "CameraComponent.h"

Player::Player()
{
	// ����
	_flipbookPlayerRunRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
	_flipbookPlayerRunLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunLeft");

	// ī�޶� ������Ʈ
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	// ó�� ���� ����
	SetFlipbook(_flipbookPlayerRunRight);

	Super::BeginPlay();
}

void Player::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// *�ӵ� ��ȹ ���� �����ϱ�
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunLeft);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	
	// Ÿ�ϸ� ��� ���� ���Ʒ� ������ �߰�
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += 200 * deltaTime;
		SetFlipbook(_flipbookPlayerRunRight);
	}
	//
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
}

void Player::TickMove()
{
}

void Player::TickSkill()
{
}

void Player::SetState(PlayerState)
{
}

void Player::UpdateAnimation()
{
}
