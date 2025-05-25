#include "pch.h"
#include "FootHold.h"
#include "ResourceManager.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "ZipLine.h"
#include "DevScene.h"
#include "SceneManager.h"

FootHoldAndZipLineButton::FootHoldAndZipLineButton()
{
	// Flipbook
	_flipbookFootHoldAndZipLineButtonOff = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FootHoldAndZipLineButtonOff");
	_flipbookFootHoldAndZipLineButtonOn1 = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FootHoldAndZipLineButtonOn1");
	_flipbookFootHoldAndZipLineButtonOn2 = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FootHoldAndZipLineButtonOn2");

	// Collider 
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_STRUCTURE);

		collider->AddCollisionFlagLayer(CLT_PLAYER);

		collider->SetSize({ 150, 105 }); 

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Off);
}

FootHoldAndZipLineButton::~FootHoldAndZipLineButton()
{
}

void FootHoldAndZipLineButton::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Off);
}

void FootHoldAndZipLineButton::Tick()
{
	Super::Tick();
}

void FootHoldAndZipLineButton::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FootHoldAndZipLineButton::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Off:
		SetFlipbook(_flipbookFootHoldAndZipLineButtonOff);
		break;
	case ObjectState::On:
		SetFlipbook(_flipbookFootHoldAndZipLineButtonOn1);
		break;
	case ObjectState::On2:
		SetFlipbook(_flipbookFootHoldAndZipLineButtonOn2);
		break;
	}
}

void FootHoldAndZipLineButton::TickOn2()
{
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	ZipLine* zipLine = scene->SpawnObject<ZipLine>({ _zipLineBegin }, LAYER_STRUCTURE);
	zipLine->SetZipLineType(ZipLineType::ZipLine);
	zipLine->SetBeginPos({_zipLineBegin});
	zipLine->SetEndPos({_zipLineEnd});

	SetState(ObjectState::Idle);	// 계속 생성되지 않도록 상태 바꿈
}

void FootHoldAndZipLineButton::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void FootHoldAndZipLineButton::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

////////////////////////////////////////////////////////////////////////////////////////////

FootHold::FootHold()
{
	_flipbookFootHold = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FootHold");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_GROUND);

		collider->AddCollisionFlagLayer(CLT_PLAYER);

		collider->SetSize({ 320, 120 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Off);
}

FootHold::~FootHold()
{
}

void FootHold::BeginPlay()
{
	Super::BeginPlay();

	SetState(ObjectState::Off);
}

void FootHold::Tick()
{
	Super::Tick();
}

void FootHold::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FootHold::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Off:
		SetFlipbook(_flipbookFootHold);
		break;
	case ObjectState::Ready:
		SetFlipbook(_flipbookFootHold);
		break;
	case ObjectState::On:
		SetFlipbook(_flipbookFootHold);
		break;
	}
}

void FootHold::TickOff()
{
	if (_footHoldAndZipLineButton->GetState() == ObjectState::On && _state == ObjectState::Off)
	{
		SetState(ObjectState::Ready);
	}
}

void FootHold::TickReady()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime;
	sumTime += deltaTime;

	_pos.y -= 80 * deltaTime;

	if (sumTime >= 0.5f)
	{
		SetState(ObjectState::On);
		sumTime = 0.f;
	}
}

void FootHold::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void FootHold::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
