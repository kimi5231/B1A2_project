#include "pch.h"
#include "LongAtkMonster.h"
#include "Paper.h"
#include "GameScene.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "ItemActor.h"

LongAtkMonster::LongAtkMonster()
{
	LongAtkMonsterStat* longAtkMonsterStat = new LongAtkMonsterStat();
	_stat = longAtkMonsterStat;

	CalPixelPerSecond();

	// SetFlipbook
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
			_collider = collider;

			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 55, 55 });

			_collider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

LongAtkMonster::~LongAtkMonster()
{
	GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
}

void LongAtkMonster::BeginPlay()
{
	Super::BeginPlay();
}

void LongAtkMonster::Tick()
{
	Super::Tick();

	TickGravity();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_creationTime += deltaTime;
	_changeDirTime += deltaTime;

	// 일정 시간 지나면 자동으로 삭제 
	if (_creationTime > 10.f)
	{
		_creationTime = 0.f;

		// 추후 GameScene으로 변경
		GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);

		return;
	}
	
	if (_changeDirTime >= 3.f)
	{
		_changeDirTime = 0.f;

		if (_dir == DIR_RIGHT)
			SetDir(DIR_LEFT);
		else
			SetDir(DIR_RIGHT);
	}
}

void LongAtkMonster::Render(HDC hdc)
{
	Super::Render(hdc);
}

void LongAtkMonster::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->attackCoolTime)
	{
		_sumTime = 0.f;
		SetState(ObjectState::LongAttack);
	}
}

void LongAtkMonster::TickMove()
{
}

void LongAtkMonster::TickLongAttack()
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
		SetState(ObjectState::Idle);
		_currentProjectileCount = 0;
	}
}

void LongAtkMonster::TickHit()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 스턴이 끝나면 Idle로 변경
	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);
	}
}

void LongAtkMonster::TickDead()
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

		scene->RemoveActor(this);
	}
}

void LongAtkMonster::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		_collider->SetSize({ 40, 55 });
		break;
	case ObjectState::LongAttack:
		SetFlipbook(_flipbookLongAttack[_dir]);
		_collider->SetSize({ 44, 61 });
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		_collider->SetSize({ 43, 59 });
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		_collider->SetSize({ 45, 75 });
		break;
	}
}

void LongAtkMonster::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
	}
}

void LongAtkMonster::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

void LongAtkMonster::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void LongAtkMonster::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void LongAtkMonster::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

float LongAtkMonster::GetSpeed()
{
	return _stat->speed;
}

int32 LongAtkMonster::GetAttack()
{
	switch (_state)
	{
	case ObjectState::LongAttack:
		return _stat->projectileAttack;
		break;
	}
}

void LongAtkMonster::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Projectile Move
	{
		float PROJECTILE_MOVE_SPEED_KMPH = _stat->projectileSpeed;
		float PROJECTILE_MOVE_SPEED_MPM = (PROJECTILE_MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float PROJECTILE_MOVE_SPEED_MPS = (PROJECTILE_MOVE_SPEED_MPM / 60.0);
		float PROJECTILE_MOVE_SPEED_PPS = (PROJECTILE_MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->projectileSpeed = PROJECTILE_MOVE_SPEED_PPS;
	}
}

void LongAtkMonster::CreateProjectile()
{
	// 추후 GameScene으로 변경
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	// 추후 Layer, Pos 변경 예정
	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y }, LAYER_PLAYER);
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);

	_currentProjectileCount++;
}
