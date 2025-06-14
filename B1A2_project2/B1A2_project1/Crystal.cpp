#include "pch.h"
#include "Crystal.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "FinalBoss.h"

Crystal::Crystal()
{
	// Flipbook
	_flipbookCrystal = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Crystal");

	// Collider
	{
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);
			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 80, 120 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

Crystal::~Crystal()
{
}

void Crystal::BeginPlay()
{
	Super::BeginPlay();

	SetState(ON);
}

void Crystal::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_creationTime += deltaTime;

	if (_creationTime >= 10.f)
	{
		_finalBoss->SubtractCurrentCrystalCount(1);

		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void Crystal::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Crystal::TickDead()
{
	_finalBoss->SubtractCurrentCrystalCount(1);

	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	scene->RemoveActor(this);
}

void Crystal::UpdateAnimation()
{
	switch (_info.state())
	{
	case ON:
		SetFlipbook(_flipbookCrystal);
		break;
	case DEAD:
		SetFlipbook(_flipbookCrystal);
		break;
	}
}

void Crystal::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		int32 damage = otherOwner->GetAttack();

		if (_hp <= 0)
			return;

		_hp = max(0, _hp - damage);

		if (_hp == 0)
		{
			SetState(DEAD);
			return;
		}
	}
}

void Crystal::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
