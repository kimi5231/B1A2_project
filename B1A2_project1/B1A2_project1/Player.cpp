#include "pch.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

Player::Player()
{
	// ����
	_flipbookPlayerRunRight = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunRight");
	_flipbookPlayerRunLeft = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_PlayerRunLeft");
}

Player::~Player()
{
}

void Player::BeginPlay()
{
	Super::BeginPlay();

	// ó�� ���� ����
	SetFlipbook(_flipbookPlayerRunRight);
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

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}
