#include "pch.h"
#include "CameraActor.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ValueManager.h"
#include "CameraComponent.h"
#include "Component.h"

CameraActor::CameraActor()
{
	CameraComponent* camera = new CameraComponent();
	AddComponent(camera);
}

CameraActor::~CameraActor()
{
}

void CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void CameraActor::Tick()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += 1000 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += 1000 * deltaTime;
	}

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();

	_pos.x = std::clamp(_pos.x, (float)winSize.x / 2, (float)mapSize.x - (float)winSize.x / 2);
	_pos.y = std::clamp(_pos.y, (float)winSize.y / 2, (float)mapSize.y - (float)winSize.y / 2);

	Super::Tick();
}

void CameraActor::Render(HDC hdc)
{
	Super::Render(hdc);
}