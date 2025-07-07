#include "pch.h"
#include "BrokenCopyMachine.h"
#include "Paper.h"
#include "GameScene.h"
#include "BoxCollider.h"
#include "Item.h"
#include "ItemActor.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

BrokenCopyMachine::BrokenCopyMachine()
{
	// Set Stat
	BrokenCopyMachineStat* brokenCopyMachineStat = new BrokenCopyMachineStat();
	brokenCopyMachineStat = GET_SINGLE(ResourceManager)->LoadBrokenCopyMachineStat(L"DataBase\\brokenCopyMachineStat.csv");
	_stat = brokenCopyMachineStat;

	CalPixelPerSecond();

	// Set Flipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineIdleRight");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineIdleLeft");
		_flipbookLongAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineLongAttackRight");
		_flipbookLongAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineLongAttackLeft");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineHitRight");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineHitLeft");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineDeadRight");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachineDeadLeft");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);
			collider->AddCollisionFlagLayer(CLT_GROUND);

			collider->SetSize({ 40, 55 });

			_collider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

BrokenCopyMachine::~BrokenCopyMachine()
{
	
}

void BrokenCopyMachine::BeginPlay()
{
	Super::BeginPlay();
}

void BrokenCopyMachine::Tick()
{
	Super::Tick();

	TickGravity();
}

void BrokenCopyMachine::Render(HDC hdc)
{
	Super::Render(hdc);
}

void BrokenCopyMachine::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->attackCoolTime)
	{
		_sumTime = 0.f;
		SetState(LONG_ATTACK);
	}
}

void BrokenCopyMachine::TickLongAttack()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 투사체 생성
	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		CreateProjectile();
	}

	if (_currentProjectileCount == _stat->projectileCount)
	{
		_sumTime = 0.f;
		SetState(IDLE);
		_currentProjectileCount = 0;
	}
}

void BrokenCopyMachine::TickHit()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 Idle로 변경
	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(IDLE);
	}
}

void BrokenCopyMachine::TickDead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 객체 제거 후 아이템 드랍
	if (_sumTime >= 0.5f)
	{
		// 난수 생성
		std::random_device rd;
		std::default_random_engine dre{ rd() };
		std::uniform_real_distribution urd{ 0.f, 1.f };

		// 추후 GameScene로 변경할 예정
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		
		// 아이템 드랍
		if (urd(dre) <= _stat->healtemDropRate)
		{
			// 힐템 생성
			Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
			ItemActor* Item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 300100, itemData->GetItems());
		}
		
		scene->InputDeadMonsterIdAndErasePointer(_id);
		scene->RemoveActor(this);
	}
}

void BrokenCopyMachine::UpdateAnimation()
{
	Vec2 colliderSize = _collider->GetSize();

	switch (_info.state())
	{
	case IDLE:
		SetFlipbook(_flipbookIdle[_info.dir()]);
		_collider->SetSize({ 40, 55 });
		break;
	case LONG_ATTACK:
		SetFlipbook(_flipbookLongAttack[_info.dir()]);
		_collider->SetSize({ 44, 61 });
		break;
	case HIT:
		SetFlipbook(_flipbookHit[_info.dir()]);
		_collider->SetSize({ 43, 59 });
		break;
	case DEAD:
		SetFlipbook(_flipbookDead[_info.dir()]);
		_collider->SetSize({ 45, 75 });
		break;
	}

	if (colliderSize.y > _collider->GetSize().y)
	{
		_isGround = false;
		_isAir = true;
	}
}

void BrokenCopyMachine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// Player Attack과 충돌
	if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		_sumTime = 0.f;
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
	}

	if (b2->GetCollisionLayer() == CLT_GROUND)
	{
		_isGround = true;
		_isAir = false;

		AdjustCollisionPosGround(b1, b2);
	}
}

void BrokenCopyMachine::AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();

	Vec2 pos = GetPos();
	Vec2 colliderPos = _collider->GetPos();

	// 충돌 범위
	RECT intersect = {};

	if (::IntersectRect(&intersect, &r1, &r2))
	{
		int32 h = intersect.bottom - intersect.top;

		// 위로 올려 보내기
		pos.y -= h;
		colliderPos.y -= h;
	}

	SetPos(pos);
	_collider->SetPos(colliderPos);
}

float BrokenCopyMachine::GetSpeed()
{
	return 0.0f;
}

int32 BrokenCopyMachine::GetAttack()
{
	switch (_info.state())
	{
	case LONG_ATTACK:
		return _stat->projectileAttack;
		break;
	}
}

void BrokenCopyMachine::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Projectile
	{
		float PROJECTILE_SPEED_KMPH = _stat->projectileSpeed;
		float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
		float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
		float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

		_stat->projectileSpeed = PROJECTILE_SPEED_PPS;
	}
}

void BrokenCopyMachine::CreateProjectile()
{
	// 추후 GameScene으로 변경
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y}, LAYER_PROJECTILE);
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);

	_currentProjectileCount++;
}