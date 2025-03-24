#include "pch.h"
#include "ZipLine.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "ResourceManager.h"
#include "Texture.h"

// 1. ¤���� - ��ư�� �ִ� ������ ��ư ���� ¤���θ� �ִ� ����
// 2. ¤���� ��ư - Player�� �浹 ó���Ǹ� ��ȣ�ۿ� �Է��� �޾� ¤���� Ȱ��ȭ
// 3. ¤���� ������ - ��ư Ȱ��ȭ�Ǹ� Render

ZipLine::ZipLine()
{
	_flipbookZipLine = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLine");
	// _flipbookZipLineGrip = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineGrip");

	SetState(ObjectState::Off);
}

ZipLine::~ZipLine()
{
}

void ZipLine::BeginPlay()
{
	Super::BeginPlay();
}

void ZipLine::Tick()
{
	Super::Tick();
}

void ZipLine::Render(HDC hdc)
{
	Super::Render(hdc);
}

void ZipLine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void ZipLine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

//////////////////////////////////////////////////////////////////////////////////

ZipLineButton::ZipLineButton()
{
	_flipbookButtonOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineButtonOff");
	_flipbookButtonOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineButtonOn");
	_flipbookDisplayOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineDisplayOff");
	_flipbookDisplayOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineDisplayOn");

	// ButtonCollider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_ZIPLINE_BUTTON);

		collider->SetSize({ 120, 150 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Off);
}

ZipLineButton::~ZipLineButton()
{
}

void ZipLineButton::BeginPlay()
{
	Super::BeginPlay();
}

void ZipLineButton::Tick()
{
	Super::Tick();
}

void ZipLineButton::Render(HDC hdc)
{
	Super::Render(hdc);
}

void ZipLineButton::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::On:
		SetFlipbook(_flipbookButtonOn);
		break;
	case ObjectState::Off:
		SetFlipbook(_flipbookButtonOff);
		break;
	}
}

void ZipLineButton::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b1->GetCollisionLayer() == CLT_ZIPLINE_BUTTON)
	{
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ObjectState::On);
		}
	}
}

void ZipLineButton::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b1->GetCollisionLayer() == CLT_ZIPLINE_BUTTON)
	{
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ObjectState::Off);
		}
	}
}
