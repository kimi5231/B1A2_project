#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

// *���ҽ� ������ �����ؾ� ��!
Player::Player()
{
	// ����
	_flipbookLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft");
	_flipbookRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight");

	// ����
	_flipbookPlayerRunRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	// ó�� ���� ����
	SetFlipbook(_flipbookRight);
}

void Player::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// *�ӵ� ��ȹ ���� �����ϱ�
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 200 * deltaTime;
		SetFlipbook(_flipbookLeft);
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 200 * deltaTime;
		SetFlipbook(_flipbookRight);
	}

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}
