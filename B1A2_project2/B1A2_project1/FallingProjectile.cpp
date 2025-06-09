#include "pch.h"
#include "FallingProjectile.h"
#include "DevScene.h"
#include "Creature.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

FallingProjectile::FallingProjectile()
{
	_flipbookMove = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FallingProjectile");

	// Collider Component
	{
		// Projectile Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 40, 40 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(MOVE);
}

FallingProjectile::~FallingProjectile()
{
}

void FallingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void FallingProjectile::Tick()
{
	Super::Tick();
}

void FallingProjectile::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FallingProjectile::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_pos.y += _speed * deltaTime;

	if (_pos.y >= 300)
	{
		// 추후 GameScene으로 변경
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		// 투사체 삭제
		scene->RemoveActor(this);
	}
}

void FallingProjectile::UpdateAnimation()
{
}

float FallingProjectile::GetSpeed()
{
	return 0.0f;
}

void FallingProjectile::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void FallingProjectile::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
