#include "pch.h"
#include "BreakingWall.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "SceneManager.h"

BreakingWall::BreakingWall()
{
	// Flipbook
	_flipbookWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Wall");
	_flipbookBreakingWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BreakingWall");

	// Collider
	{
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);
			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 80, 240 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

BreakingWall::~BreakingWall()
{
}

void BreakingWall::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::On);
}

void BreakingWall::Tick()
{
	Super::Tick();
}

void BreakingWall::Render(HDC hdc)
{
	Super::Render(hdc);
}


void BreakingWall::TickOn()
{
}

void BreakingWall::TickDead()
{
	if (GetIdx() == 2)
	{	
		_player->SetIsCloseAtk(false);

		// 객체 제거
		// 추후 GameScene으로 변경할 예정
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void BreakingWall::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookWall);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookBreakingWall);
		break;
	}
}

void BreakingWall::OnComponentBeginOverlap(Collider* collider, Collider* other)
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
			SetState(ObjectState::Dead);
			return;
		}
	}
}

void BreakingWall::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
