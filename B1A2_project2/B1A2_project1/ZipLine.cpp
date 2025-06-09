#include "pch.h"
#include "ZipLine.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "Texture.h"

// 1. 짚라인 - 버튼이 있는 버전과 버튼 없이 짚라인만 있는 버전
// 2. 짚라인 버튼 - Player와 충돌 처리되면 상호작용 입력을 받아 짚라인 활성화
// 3. 짚라인 전광판 - 버튼 활성화되면 On

ZipLine::ZipLine()
{
	// Flipbook
	_flipbookZipLineOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLine");
	_flipbookZipLineOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLine");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_STRUCTURE_DETECT);

		collider->AddCollisionFlagLayer(CLT_PLAYER);
		
		collider->SetSize({ 200, 200 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);

		_playerDetectCollider = collider;
	}

	SetState(OFF);
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

void ZipLine::UpdateAnimation()
{
	switch (_state)
	{
	case ON:
		SetFlipbook(_flipbookZipLineOn);
		break;
	case OFF:
		SetFlipbook(_flipbookZipLineOff);
		break;
	}
}

void ZipLine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		if (_zipLineType == ZipLineType::ZipLine)
		{
			_state = ON;
		}
		else if (_zipLineType == ZipLineType::ZipLineWithButton)
		{
			if (_zipLineButtonAndDisplay->GetState() == ON)
			{
				_state = ON;
			}
		}
	}
}

void ZipLine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		if (_zipLineType == ZipLineType::ZipLine)
		{
			_state = OFF;
		}
		else if (_zipLineType == ZipLineType::ZipLineWithButton)
		{
			if (_zipLineButtonAndDisplay->GetState() == ON)
			{
				_state = OFF;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////

ZipLineButtonAndDisplay::ZipLineButtonAndDisplay()
{
	_flipbookButtonOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineButtonOff");
	_flipbookButtonOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineButtonOn");
	_flipbookDisplayOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineDisplayOff");
	_flipbookDisplayOn = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLineDisplayOn");

	// ButtonCollider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_STRUCTURE);

		collider->AddCollisionFlagLayer(CLT_PLAYER);

		collider->SetSize({ 120, 150 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(OFF);
}

ZipLineButtonAndDisplay::~ZipLineButtonAndDisplay()
{
}

void ZipLineButtonAndDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void ZipLineButtonAndDisplay::Tick()
{
	Super::Tick();
}

void ZipLineButtonAndDisplay::Render(HDC hdc)
{
	// ZipLine Button
	Super::Render(hdc);

	// ZipLine Display
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineDisplay");

	if (_state == ON)
	{
		::TransparentBlt(hdc,
			((int32)_displayPos.x - texture->GetSize().x / 2) * winSizeAdjustmemt.x - cameraPosAdjustmemt.x,
			((int32)_displayPos.y - texture->GetSize().y / 2) * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
			texture->GetSize().x * winSizeAdjustmemt.x,
			(texture->GetSize().y / 2) * winSizeAdjustmemt.y,
			texture->GetDC(),
			0,
			texture->GetSize().y / 2,
			texture->GetSize().x,
			texture->GetSize().y / 2,
			texture->GetTransparent());
	}
	else
	{
		::TransparentBlt(hdc,
			((int32)_displayPos.x - texture->GetSize().x / 2) * winSizeAdjustmemt.x - cameraPosAdjustmemt.x,
			((int32)_displayPos.y - texture->GetSize().y / 2) * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
			texture->GetSize().x * winSizeAdjustmemt.x,
			(texture->GetSize().y / 2) * winSizeAdjustmemt.y,
			texture->GetDC(),
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y / 2,
			texture->GetTransparent());
	}
}

void ZipLineButtonAndDisplay::UpdateAnimation()
{
	switch (_state)
	{
	case ON:
		SetFlipbook(_flipbookButtonOn);
		break;
	case OFF:
		SetFlipbook(_flipbookButtonOff);
		break;
	}
}

void ZipLineButtonAndDisplay::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b1->GetCollisionLayer() == CLT_STRUCTURE)
	{
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			SetState(ON);
		}
	}
}

void ZipLineButtonAndDisplay::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
