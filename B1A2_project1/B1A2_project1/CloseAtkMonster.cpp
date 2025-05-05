#include "pch.h"
#include "CloseAtkMonster.h"
#include "BoxCollider.h"
#include "Player.h"
#include "DevScene.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "ItemActor.h"

CloseAtkMonster::CloseAtkMonster()
{
	CloseAtkMonsterStat* closeAtkMonsterStat = new CloseAtkMonsterStat();
	_stat = closeAtkMonsterStat;

	CalPixelPerSecond();

	// SetFlipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleRight");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleLeft");
		_flipbookCloseAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerCloseAttackRight");
		_flipbookCloseAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerCloseAttackLeft");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerHitRight");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerHitLeft");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerDeadRight");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerDeadLeft");
		_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerChaseRight");
		_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerChaseLeft");
		_flipbookRoaming[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingRight");
		_flipbookRoaming[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingLeft");
		_flipbookReturn[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingRight");
		_flipbookReturn[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerRoamingLeft");
		_flipbookReturnIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleRight");
		_flipbookReturnIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorkerIdleLeft");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 31, 77 });

			_collider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}

		// Monster Detection Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_DETECT);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ float(_stat->playerDetection.x), float(_stat->playerDetection.y) });

			_detectCollider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

CloseAtkMonster::~CloseAtkMonster()
{
	GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
	GET_SINGLE(CollisionManager)->RemoveCollider(_detectCollider);
}

void CloseAtkMonster::BeginPlay()
{
	Super::BeginPlay();
}

void CloseAtkMonster::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_creationTime += deltaTime;

	if (_creationTime > 10.f)
	{
		// ���� GameScene���� ����
		DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		scene->RemoveActor(this);
	}

	if (_state != ObjectState::CloseAttack)
	{
		if (_attackCollider)
		{
			GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
			RemoveComponent(_attackCollider);
			_attackCollider = nullptr;
		}
	}
}

void CloseAtkMonster::Render(HDC hdc)
{
	Super::Render(hdc);
}

void CloseAtkMonster::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->idleTime)
	{
		_currentMoveDistance = _moveDistance;
		SetState(ObjectState::Roaming);
	}
}

void CloseAtkMonster::TickCloseAttack()
{
	// Monster Attack Collider ����
	if (!_attackCollider)
	{
		BoxCollider* collider = new BoxCollider();
		collider->ResetCollisionFlag();
		collider->SetCollisionLayer(CLT_MONSTER_ATTACK);

		collider->AddCollisionFlagLayer(CLT_PLAYER);

		collider->SetSize({ 50, 50 });

		_attackCollider = collider;

		GET_SINGLE(CollisionManager)->AddCollider(collider);
		AddComponent(collider);
	}

	// ������ ���� ����� ��
	if (GetIdx() == 0)
	{
		// ���� ���� üũ (���� y�� �����Ͽ� ���� ����)
		if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange)
			SetState(ObjectState::CloseAttack);
		else
		{
			_sumTime = 0.f;
			SetState(ObjectState::Chase);
		}
	}
}

void CloseAtkMonster::TickHit()
{
	// knockback
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->knockBackDistance;
	else
		_pos.x += _stat->knockBackDistance;

	_sumTime = 0.f;
	SetState(ObjectState::Chase);
}

void CloseAtkMonster::TickDead()
{
	// ���� ���
	DevScene* scene = dynamic_cast<DevScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
	ItemActor* item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 300100, itemData->GetItems());

	// ��ü ����
	// ���� GameScene�� ������ ����
	scene->RemoveActor(this);
}

void CloseAtkMonster::TickChase()
{
	// ���� üũ
	if (_pos.x > _movementLimit.y || _pos.x < _movementLimit.x)
	{
		_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);
		_sumTime = 0.f;
		SetState(ObjectState::ReturnIdle);
	}

	// ����
	if (_target->GetPos().x - _pos.x < 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->chaseSpeed * deltaTime;
	else
		_pos.x -= _stat->chaseSpeed * deltaTime;

	// ���� �� ������ ��
	if (_sumTime != 0.f)
	{
		_sumTime += deltaTime;

		// 3�ʰ� ���ϸ� ����
		if (_sumTime >= 3.0f)
			SetState(ObjectState::Return);
	}

	// ���� ���� üũ (���� y�� �����Ͽ� ���� ����)
	if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange)
		SetState(ObjectState::CloseAttack);
}

void CloseAtkMonster::TickRoaming()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	_currentMoveDistance -= _stat->speed * deltaTime;

	if (_currentMoveDistance <= 0.f)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);

		// ���� ��ȯ
		if (_dir == DIR_RIGHT)
			SetDir(DIR_LEFT);
		else
			SetDir(DIR_RIGHT);
	}
}

void CloseAtkMonster::TickReturn()
{
	if (_pos.x > _spawnPos.x)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_dir == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	// ��ġ Ȯ��
	if (_dir == DIR_LEFT)
		_pos.x = max(_spawnPos.x, _pos.x);
	else
		_pos.x = min(_pos.x, _spawnPos.x);

	if (_pos.x == _spawnPos.x)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Idle);
		SetPos(_spawnPos);
		SetDir(_spawnDir);
	}
}

void CloseAtkMonster::TickReturnIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->idleTime)
		SetState(ObjectState::Return);
}

void CloseAtkMonster::UpdateAnimation()
{
	switch (_state)
	{
	case ObjectState::Idle:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case ObjectState::CloseAttack:
		SetFlipbook(_flipbookCloseAttack[_dir]);
		break;
	case ObjectState::Hit:
		SetFlipbook(_flipbookHit[_dir]);
		break;
	case ObjectState::Dead:
		SetFlipbook(_flipbookDead[_dir]);
		break;
	case ObjectState::Chase:
		SetFlipbook(_flipbookChase[_dir]);
		break;
	case ObjectState::Roaming:
		SetFlipbook(_flipbookRoaming[_dir]);
		break;
	case ObjectState::Return:
		SetFlipbook(_flipbookReturn[_dir]);
		break;
	case ObjectState::ReturnIdle:
		SetFlipbook(_flipbookReturnIdle[_dir]);
		break;
	}
}

void CloseAtkMonster::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// �ǰ� >> ����

	// �ε��� �ڽ��� collider�� CLT_MONSTER�� ��
	if (b1->GetCollisionLayer() == CLT_MONSTER)
	{
		// Player Attack�� �浹
		if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
		{
			Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
			OnDamaged(otherOwner);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}

		return;
	}

	// �ε��� �ڽ��� collider�� CLT_DETECT�� ��
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player�� �浹
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			_sumTime = 0.f;
			SetState(ObjectState::Chase);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
	}
}

void CloseAtkMonster::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;

	// �ε��� �ڽ��� collider�� CLT_DETECT�� ��
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player�� �浹
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			// ��ģ �ð� ���� ����
			float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
			_sumTime += deltaTime;
		}
	}
}

void CloseAtkMonster::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void CloseAtkMonster::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void CloseAtkMonster::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

float CloseAtkMonster::GetSpeed()
{
	switch (_state)
	{
	case ObjectState::Move:
		return _stat->speed;
		break;
	case ObjectState::Chase:
		return _stat->chaseSpeed;
		break;
	}
}

int32 CloseAtkMonster::GetAttack()
{
	switch (_state)
	{
	case ObjectState::CloseAttack:
		return _stat->attack;
		break;
	}
}

void CloseAtkMonster::CalPixelPerSecond()
{
	float PIXEL_PER_METER = (10.0 / 0.2);

	// Move(Roaming)
	{
		float MOVE_SPEED_KMPH = _stat->speed;
		float MOVE_SPEED_MPM = (MOVE_SPEED_KMPH * 1000.0 / 60.0);
		float MOVE_SPEED_MPS = (MOVE_SPEED_MPM / 60.0);
		float MOVE_SPEED_PPS = (MOVE_SPEED_MPS * PIXEL_PER_METER);

		_stat->speed = MOVE_SPEED_PPS;
	}

	// Chase
	{
		float CHASE_SPEED_KMPH = _stat->chaseSpeed;
		float CHASE_SPEED_MPM = (CHASE_SPEED_KMPH * 1000.0 / 60.0);
		float CHASE_SPEED_MPS = (CHASE_SPEED_MPM / 60.0);
		float CHASE_SPEED_PPS = (CHASE_SPEED_MPS * PIXEL_PER_METER);

		_stat->chaseSpeed = CHASE_SPEED_PPS;
	}
}
