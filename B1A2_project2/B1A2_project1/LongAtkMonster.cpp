#include "pch.h"
#include "LongAtkMonster.h"
#include "Paper.h"
#include "DevScene.h"
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
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookLongAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookLongAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_BrokenCopyMachine");
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

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_creationTime += deltaTime;

	// 일정 시간 지나면 자동으로 삭제 
	if (_creationTime > 10.f)
	{
		GET_SINGLE(CollisionManager)->RemoveCollider(_collider);

		// 추후 GameScene으로 변경
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}

	if (_pos.x <= _movementLimit.x)
		SetDir(DIR_RIGHT);
	else if (_pos.x >= _movementLimit.y)
		SetDir(DIR_LEFT);

	if (_info.dir() == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);
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
		SetState(LONG_ATTACK);
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
		SetState(IDLE);
		_currentProjectileCount = 0;
	}
}

void LongAtkMonster::TickHit()
{
	_sumTime = 0.f;
	SetState(IDLE);
}

void LongAtkMonster::TickDead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 0.5f)
	{
		// 힐템 드랍
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		ItemActor* item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 300100, itemData->GetItems());

		// 객체 제거
		// 추후 GameScene로 변경할 예정
		scene->RemoveActor(this);
	}
}

void LongAtkMonster::UpdateAnimation()
{
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
}

void LongAtkMonster::SetSpawnDir(Dir dir)
{
}

void LongAtkMonster::SetMoveDistance(float distance)
{
}

float LongAtkMonster::GetSpeed()
{
	return 0.0f;
}

int32 LongAtkMonster::GetAttack()
{
	switch (_info.state())
	{
	case LONG_ATTACK:
		return _stat->projectileAttack;
		break;
	}
}

void LongAtkMonster::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);


	// Move
	{
		float MOVE_SPEED_KMPH = _stat->speed;
		float MOVE_SPEED_MPM = (MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float MOVE_SPEED_MPS = (MOVE_SPEED_MPM / 60.0);
		float MOVE_SPEED_PPS = (MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->speed = MOVE_SPEED_PPS;
	}

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
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	// 추후 Layer, Pos 변경 예정
	Paper* paper = scene->SpawnObject<Paper>({ _pos.x, _pos.y }, LAYER_PLAYER);
	paper->SetSpeed(_stat->projectileSpeed);
	paper->SetAttack(_stat->projectileAttack);
	paper->SetRange(_stat->attackRange);
	paper->SetOwner(this);

	_currentProjectileCount++;
}
