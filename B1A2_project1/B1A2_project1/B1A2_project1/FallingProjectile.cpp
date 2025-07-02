#include "pch.h"
#include "FallingProjectile.h"
#include "GameScene.h"
#include "Creature.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Sound.h"

FallingProjectile1::FallingProjectile1()
{
	_flipbookMove = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FallingProjectile1");

	// Collider Component
	{
		// Projectile Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 54, 142 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(ObjectState::Move);
}

FallingProjectile1::~FallingProjectile1()
{
}

void FallingProjectile1::BeginPlay()
{
	Super::BeginPlay();
}

void FallingProjectile1::Tick()
{
	Super::Tick();
}

void FallingProjectile1::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FallingProjectile1::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_isHitPlayer)
	{
		_sumTime += deltaTime;

		if (_sumTime >= _playerHitFallingProjectileDuration)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			scene->RemoveActor(this);
			return;
		}
	}

	if (_isArriveGround)
	{
		_sumTime += deltaTime;

		if (_sumTime >= _landedFallingProjectileDuration)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			scene->RemoveActor(this);
			return;
		}
		return;	
	}

	_pos.y += _speed * deltaTime;

	if (_pos.y >= 560)
	{
		_isArriveGround = true;
	}
}

void FallingProjectile1::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookMove);
		break;
	}
}

float FallingProjectile1::GetSpeed()
{
	return _speed;
}

void FallingProjectile1::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		_isHitPlayer = true;

		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"FallingProjectile1");
		sound->Play(false);
	}
}

void FallingProjectile1::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////

FallingProjectile2::FallingProjectile2()
{
	_flipbookMove = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FallingProjectile2");

	// Collider Component
	{
		// Projectile Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 54, 122 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(ObjectState::Move);
}

FallingProjectile2::~FallingProjectile2()
{
}

void FallingProjectile2::BeginPlay()
{
	Super::BeginPlay();
}

void FallingProjectile2::Tick()
{
	Super::Tick();
}

void FallingProjectile2::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FallingProjectile2::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_isHitPlayer)
	{
		_sumTime += deltaTime;

		if (_sumTime >= _playerHitFallingProjectileDuration)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			scene->RemoveActor(this);
			return;
		}
	}

	if (_isArriveGround)
	{
		_sumTime += deltaTime;

		if (_sumTime >= _landedFallingProjectileDuration)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
			scene->RemoveActor(this);
			return;
		}
		return;
	}

	_pos.y += _speed * deltaTime;

	if (_pos.y >= 560)
	{
		_isArriveGround = true;
	}
}

void FallingProjectile2::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookMove);
		break;
	}
}

float FallingProjectile2::GetSpeed()
{
	return _speed;
}

void FallingProjectile2::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		_isHitPlayer = true;

		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"FallingProjectile2");
		sound->Play(false);
	}
}

void FallingProjectile2::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}