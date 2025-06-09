#include "pch.h"
#include "SlashWave.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "AmateurFencer.h"

Slashwave::Slashwave()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveLRight");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveLLeft");
	
	// Collider Component
	{
		// Projectile
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 20, 88 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(MOVE);
}

Slashwave::~Slashwave()
{
}

void Slashwave::BeginPlay()
{
	Super::BeginPlay();
}

void Slashwave::Tick()
{
	Super::Tick();
}

void Slashwave::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Slashwave::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void Slashwave::UpdateAnimation()
{
	switch (_state)
	{
	case MOVE:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}
}

float Slashwave::GetSpeed()
{
	return 0.0f;
}

void Slashwave::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void Slashwave::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
