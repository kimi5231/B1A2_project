#include "pch.h"
#include "LockedDoorAndKey.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "Texture.h"
#include "SceneManager.h"
#include "DevScene.h"
#include "ItemActor.h"

LockedDoorAndKey::LockedDoorAndKey()
{
	// Flipbook
	_flipbookLockedDoor = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_LockedDoor");
	_flipbookUnlockedDoor = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_UnlockedDoor");

	// Collider
	{
		// Detect
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE_DETECT);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 160, 240 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
		
		// Structure
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_STRUCTURE);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 80, 240 });

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}


	SetState(ObjectState::Off);
}

LockedDoorAndKey::~LockedDoorAndKey()
{
}

void LockedDoorAndKey::BeginPlay()
{
	Super::BeginPlay();
}

void LockedDoorAndKey::Tick()
{
	Super::Tick();

	if (_isKeyAcquired)
		SetState(ObjectState::On);
}

void LockedDoorAndKey::Render(HDC hdc)
{
	Super::Render(hdc);
}

void LockedDoorAndKey::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookUnlockedDoor);
		break;
	case ObjectState::Off:
		SetFlipbook(_flipbookLockedDoor);
	}
}

void LockedDoorAndKey::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (_isOperateKey)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		// 추후 GameScene로 변경할 예정
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		
		// Key 생성
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		ItemActor* Item = scene->SpawnObject<ItemActor>({ float(_itemPos.x), float(_itemPos.y) }, LAYER_ITEM, 310100, itemData->GetItems());

		_isOperateKey = true;
	}
}

void LockedDoorAndKey::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
