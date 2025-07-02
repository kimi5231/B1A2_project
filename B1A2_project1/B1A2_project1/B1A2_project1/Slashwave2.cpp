#include "pch.h"
#include "Slashwave2.h"
#include "GameScene.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "FinalBoss.h"

SlashwaveW::SlashwaveW()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveWRight");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveWLeft");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PROJECTILE);

		collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

		collider->SetSize({ 50, 30 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Move);
}

SlashwaveW::~SlashwaveW()
{
}

void SlashwaveW::BeginPlay()
{
	Super::BeginPlay();
}

void SlashwaveW::Tick()
{
	Super::Tick();
}

void SlashwaveW::Render(HDC hdc)
{
	Super::Render(hdc);
}

float SlashwaveW::GetSpeed()
{
	return 0.0f;
}

void SlashwaveW::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveW::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}
}

void SlashwaveW::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveW::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

//////////////////////////////////////////////////////////////////////////

SlashwaveL::SlashwaveL()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveLRight");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_SlashWaveLLeft");

	// Collider
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_PROJECTILE);

		collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

		collider->SetSize({ 20, 90 });

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	SetState(ObjectState::Move);
}

SlashwaveL::~SlashwaveL()
{
}

void SlashwaveL::BeginPlay()
{
	Super::BeginPlay();
}

void SlashwaveL::Tick()
{
	Super::Tick();
}

void SlashwaveL::Render(HDC hdc)
{
	Super::Render(hdc);
}

void SlashwaveL::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveL::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Move:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}
}

float SlashwaveL::GetSpeed()
{
	return 0.0f;
}

void SlashwaveL::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}
}

void SlashwaveL::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
