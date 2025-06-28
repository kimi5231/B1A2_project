#include "pch.h"
#include "Paper.h"
#include "GameScene.h"
#include "Creature.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

Paper::Paper()
{
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Paper");
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Paper");

	// Collider Component
	{
		// Projectile Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_PROJECTILE);

			collider->SetSize({ 10, 5 });

			collider->SetCollisionFlag(CLT_PLAYER);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	SetState(MOVE);
}

Paper::~Paper()
{

}

void Paper::BeginPlay()
{
	Super::BeginPlay();
}

void Paper::Tick()
{
	Super::Tick();
}

void Paper::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Paper::TickMove()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_info.dir() == DIR_RIGHT)
		_pos.x += _speed * deltaTime;
	else
		_pos.x -= _speed * deltaTime;

	if (abs(_owner->GetPos().x - _pos.x) >= _range)
	{
		// 추후 GameScene으로 변경
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		// 투사체 삭제
		scene->RemoveActor(this);
	}
}

void Paper::UpdateAnimation()
{
	switch (_info.state())
	{
	case MOVE:
		SetFlipbook(_flipbookMove[_info.dir()]);
		break;
	}
}

float Paper::GetSpeed()
{
	// 추후 수정 예정
	return 0.0f;
}

void Paper::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// Player와 충돌
	if (b2->GetCollisionLayer() == CLT_PLAYER)
	{
		// 추후 GameScene으로 변경
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		// 투사체 삭제
		scene->RemoveActor(this);
	}
}

void Paper::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}