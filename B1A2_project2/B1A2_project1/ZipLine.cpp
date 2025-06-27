#include "pch.h"
#include "ZipLine.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "Texture.h"
#include "Player.h"
#include "InputManager.h"
#include "Sound.h"

// 1. 짚라인 - 버튼이 있는 버전과 버튼 없이 짚라인만 있는 버전
// 2. 짚라인 버튼 - Player와 충돌 처리되면 상호작용 입력을 받아 짚라인 활성화
// 3. 짚라인 전광판 - 버튼 활성화되면 On

ZipLine::ZipLine()
{
	// Flipbook
	_flipbookZipLine = nullptr;

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
	// Grip 
	GripRender(hdc);

	// 직선 줄 
	if (_renderType == ZipLineRenderType::None)
		return;

	Super::Render(hdc);

	LineRender(hdc);
}

void ZipLine::LineRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	int32 length = _beginPos.y - _endPos.y;

	if (_player->GetState() == HANG)
		length = _player->GetPos().y - _endPos.y;

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLine");

	::TransparentBlt(hdc,
		((int32)_endPos.x - 2) * winSizeAdjustmemt.x - cameraPosAdjustmemt.x, // x 기준 좌우 2픽셀 중심 정렬
		((int32)_endPos.y) * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
		4 * winSizeAdjustmemt.x,                  // 폭은 4 픽셀
		(length - 30) * winSizeAdjustmemt.y,            // 줄의 길이
		texture->GetDC(),
		0,
		0,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetTransparent());
}

void ZipLine::GripRender(HDC hdc)
{
	if (_player->GetState() == HANG)
		return;

	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	Vec2 cameraPosAdjustmemt = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineGrip");

	Vec2 GripPos;
	if (_renderType == ZipLineRenderType::None)
		GripPos = _beginPos;
	else
		GripPos = { _beginPos.x - 9, _beginPos.y - 37 };

	if (_midPos.x != 0 && _midPos.y != 0)	// 중간 하차했을 때 그리기
	{
		GripPos = _midPos;
	}

	::TransparentBlt(hdc,
		((int32)GripPos.x) * winSizeAdjustmemt.x - cameraPosAdjustmemt.x,
		((int32)GripPos.y + 5) * winSizeAdjustmemt.y - cameraPosAdjustmemt.y,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetDC(),
		0,
		0,
		texture->GetSize().x,
		texture->GetSize().y,
		texture->GetTransparent());
}

void ZipLine::UpdateAnimation()
{
	switch (_state)
	{
	case ON:
		SetFlipbook(_flipbookZipLine);
		break;
	case OFF:
		SetFlipbook(_flipbookZipLine);
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

	if (_isCollide)
	{
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::F))
		{
			SetState(ON);
		}
	}
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

	if (_info.state() == ON)
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
	switch (_info.state())
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

	if (b1->GetCollisionLayer() == CLT_STRUCTURE && b2->GetCollisionLayer() == CLT_PLAYER)
	{
		_isCollide = true;
	}
}

void ZipLineButtonAndDisplay::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b1->GetCollisionLayer() == CLT_STRUCTURE && b2->GetCollisionLayer() == CLT_PLAYER)
	{
		_isCollide = false;
	}
}