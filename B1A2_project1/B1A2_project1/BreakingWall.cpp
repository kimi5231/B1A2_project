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

void BreakingWall::SetWallType(BreakingWallType type)
{
	// Flipbook
	switch (type)
	{
	case BreakingWallType::Normal:
		_flipbookWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Wall");
		_flipbookBreakingWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BreakingWall");
		break;
	case BreakingWallType::Short:
		_flipbookWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WallShort");
		_flipbookBreakingWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BreakingWallShort");
		break;
	case BreakingWallType::Long:
		_flipbookWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_WallLong");
		_flipbookBreakingWall = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BreakingWallLong");
		break;
	}
	
	// Collider
	{
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE_COLLISION);

			collider->AddCollisionFlagLayer(CLT_PLAYER);
			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			if (type == BreakingWallType::Normal)
				collider->SetSize({ 80, 240 });
			else if (type == BreakingWallType::Short)
				collider->SetSize({ 80, 160 });
			else
				collider->SetSize({ 80, 280 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

void BreakingWall::TickOn()
{
}

void BreakingWall::TickDead()
{
	if (GetIdx() == 2)
	{	
		_player->SetIsCloseAtk(false);

		// ��ü ����
		// ���� GameScene���� ������ ����
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
