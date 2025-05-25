#include "pch.h"
#include "Blanket.h"
#include "DevScene.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Blanket::Blanket()
{
	_flipbookBlanket = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Blanket");

	// Collider Component
	{
		// Projectile
		{
			BoxCollider* collider = new BoxCollider();
			_collider = collider;

			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 200, 80 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	// 공격력 수정 필요
	SetAttack(5);

	SetState(ObjectState::On);
}

Blanket::~Blanket()
{
}

void Blanket::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::On);
}

void Blanket::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 5.f)
	{	
		_sumTime - 0.f;

		GET_SINGLE(CollisionManager)->RemoveCollider(_collider);

		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void Blanket::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Blanket::TickMove()
{
}

void Blanket::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookBlanket);
		break;
	}
}

float Blanket::GetSpeed()
{
	return 0.0f;
}

void Blanket::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void Blanket::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
