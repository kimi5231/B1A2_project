#include "pch.h"
#include "TiredOfficeWorker.h"
#include "BoxCollider.h"
#include "Player.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

TiredOfficeWorker::TiredOfficeWorker()
{
	TiredOfficeWorkerStat* tiredOfficeWorkerStat = new TiredOfficeWorkerStat();
	tiredOfficeWorkerStat = GET_SINGLE(ResourceManager)->LoadTiredOfficeWorkerStat(L"DataBase\\tiredOfficeWorkerStat.csv");
	_stat = tiredOfficeWorkerStat;

	CalPixelPerSecond();

	// SetFlipbook
	{
		_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookCloseAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookCloseAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookRoaming[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
		_flipbookRoaming[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_TiredOfficeWorker");
	}

	// Collider Component
	{
		// Monster Collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->SetSize({ 31, 77 });

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

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}
}

TiredOfficeWorker::~TiredOfficeWorker()
{
}

void TiredOfficeWorker::BeginPlay()
{
	Super::BeginPlay();
}

void TiredOfficeWorker::Tick()
{
	Super::Tick();
}

void TiredOfficeWorker::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TiredOfficeWorker::TickIdle()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= _stat->idleTime)
	{
		_sumTime = 0.f;
		SetState(ObjectState::Roaming);
	}
}

void TiredOfficeWorker::TickCloseAttack()
{
	int32 idx = GetIdx();

	// ������ ���� ����� ��
	if (idx == 0)
	{
		// ���� ���� üũ
		if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange)
			SetState(ObjectState::CloseAttack);
		else
		{
			// collider ����
			GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
			RemoveComponent(_attackCollider);

			SetState(ObjectState::Chase);
		}
	}
}

void TiredOfficeWorker::TickHit()
{
	// knockback
	if (_dir == DIR_RIGHT)
		_pos.x -= _stat->knockBackDistance;
	else
		_pos.x += _stat->knockBackDistance;

	// ü���� �� ��� ���
	if (_stat->hp == 0)
		SetState(ObjectState::Dead);

	// Idle, Chase, Attack
	SetState(ObjectState::Idle);
}

void TiredOfficeWorker::TickDead()
{
	// ������ ���
}

void TiredOfficeWorker::TickChase()
{
	// ���� üũ
	if (_pos.x > _movementLimit.y || _pos.x < _movementLimit.x)
	{
		_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);
		_sumTime = 0.f;
		SetState(ObjectState::Return);
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
		{
			_sumTime = 0.f;
			SetState(ObjectState::Return);
		}
	}

	// ���� ���� üũ
	if (std::abs(_target->GetPos().x - _pos.x) <= _stat->attackRange)
	{
		// Monster Attack Collider
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

		SetState(ObjectState::CloseAttack);
	}
}

void TiredOfficeWorker::TickRoaming()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if(_dir == DIR_RIGHT)
		_pos.x += _stat->speed * deltaTime;
	else
		_pos.x -= _stat->speed * deltaTime;

	_currentMoveDistance -= _stat->speed * deltaTime;

	if (_currentMoveDistance <= 0.f)
	{
		_currentMoveDistance = _moveDistance;
		SetState(ObjectState::Idle);

		if (_dir == DIR_RIGHT)
			SetDir(DIR_LEFT);
		else
			SetDir(DIR_RIGHT);
	}
}

void TiredOfficeWorker::TickReturn()
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
		SetState(ObjectState::Idle);
		SetPos(_spawnPos);
		SetDir(_spawnDir);
	}
}

void TiredOfficeWorker::UpdateAnimation()
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
	}
}

void TiredOfficeWorker::OnComponentBeginOverlap(Collider* collider, Collider* other)
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
		// ���� CLT_PLAYER_ATTACK�� ������ ����
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
			OnDamaged(otherOwner);
			// Idle, Chase ���¿��� �ʱ�ȭ���� ���� ��� ���
			_sumTime = 0.f;

			SetState(ObjectState::Hit);
		}

		return;
	}

	// �ε��� �ڽ��� collider�� CLT_DETECT�� ��
	if (b1->GetCollisionLayer() == CLT_DETECT)
	{
		// Player�� �浹
		if (b2->GetCollisionLayer() == CLT_PLAYER)
		{
			// Idle ���¿��� �ʱ�ȭ���� ���� ��� ���
			_sumTime = 0.f;

			SetState(ObjectState::Chase);
			SetTarget(dynamic_cast<Player*>(b2->GetOwner()));
		}
	}
}

void TiredOfficeWorker::OnComponentEndOverlap(Collider* collider, Collider* other)
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
 			float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
			_sumTime += deltaTime;
		}
	}
}

void TiredOfficeWorker::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void TiredOfficeWorker::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void TiredOfficeWorker::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

int32 TiredOfficeWorker::GetAttack()
{
	return int32();
}

void TiredOfficeWorker::CalPixelPerSecond()
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