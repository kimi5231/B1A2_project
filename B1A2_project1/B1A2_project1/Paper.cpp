#include "pch.h"
#include "Paper.h"
#include "DevScene.h"
#include "Creature.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

Paper::Paper()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Paper");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Paper");

	SetState(ObjectState::Move);
}

Paper::~Paper()
{
}

void Paper::BeginPlay()
{
	Super::BeginPlay();
}

void Paper::Tick()
{
	Super::Tick();
}

void Paper::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Paper::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		// ���� GameScene���� ����
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		// ����ü ����
		scene->RemoveActor(this);
	}
}

void Paper::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}
}