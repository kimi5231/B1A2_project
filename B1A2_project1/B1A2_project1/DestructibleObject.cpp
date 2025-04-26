#include "pch.h"
#include "DestructibleObject.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "TimeManager.h"
#include "DevScene.h"
#include "SceneManager.h"
#include "ItemActor.h"

DestructibleObject::DestructibleObject()
{
	// Flipbook
	_flipbookObject = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_DestructibleObject");
	_flipbookBreakingObject = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BreakingDestructibleObject");

	// Collider
	{
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE); 
			
			collider->AddCollisionFlagLayer(CLT_PLAYER);
			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 120, 100 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
	
}

DestructibleObject::~DestructibleObject()
{
}

void DestructibleObject::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::On);
}

void DestructibleObject::Tick()
{
	Super::Tick();
}

void DestructibleObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void DestructibleObject::TickOn()
{
}

void DestructibleObject::TickDead()
{	
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	if (GetIdx() == 2)
	{
		_player->SetIsCloseAtk(false);


		// ������ 
		std::random_device rd;
		std::mt19937 gen(rd()); // �õ� ������
		std::uniform_int_distribution<> dist(0, 1);

		if (dist(gen) == 1)
		{
			Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");

			ItemActor* item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 310100, itemData->GetItems());
		}

		// ��ü ����
		// ���� GameScene���� ������ ����
		scene->RemoveActor(this);
	}
}

void DestructibleObject::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookObject);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookBreakingObject);
		break;
	}
}

void DestructibleObject::OnComponentBeginOverlap(Collider* collider, Collider* other)
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

void DestructibleObject::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
