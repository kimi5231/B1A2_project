#include "pch.h"
#include "FinalBoss.h"
#include "ResourceManager.h"
#include "BehaviorTree.h"
#include "Player.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "Flipbook.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SlashWave2.h"
#include "CloseAtkMonster.h"
#include "Blanket.h"
#include "LongAtkMonster.h"
#include "Crystal.h"
#include "FallingProjectile.h"
#include "ItemActor.h"


FinalBoss::FinalBoss()
{
	// Stat
	FinalBossStat* finalBossStat = new FinalBossStat();
	finalBossStat = GET_SINGLE(ResourceManager)->LoadFinalBossStat(L"DataBase\\finalBossStat.csv");
	_stat = finalBossStat;

	CalPixelPerSecond();

	// Flipbook
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossIdleRight");
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossIdleLeft");
	_flipbookChase[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossChaseRight");
	_flipbookChase[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossChaseLeft");
	_flipbookHit[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossHitRight");
	_flipbookHit[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossHitLeft");
	_flipbookDead[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossDeadRight");
	_flipbookDead[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossDeadLeft");
	_flipbookThrust[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossThrustRight");
	_flipbookThrust[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossThrustLeft");
	_flipbookBackStep[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossBackStepRight");
	_flipbookBackStep[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossBackStepLeft");
	_flipbookLongAttackLength[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossLongAttackLengthRight");
	_flipbookLongAttackLength[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossLongAttackLengthLeft");
	_flipbookLongAttackWidth[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossLongAttackWidthRight");
	_flipbookLongAttackWidth[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossLongAttackWidthLeft");
	_flipbookDash[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossDashRight");
	_flipbookDash[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossDashLeft");
	_flipbookCutSeverely[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossSlashRight");
	_flipbookCutSeverely[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_FinalBossSlashLeft");

	// Collider
	{
		// Final Boss
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER);

			collider->AddCollisionFlagLayer(CLT_PLAYER_ATTACK);

			collider->SetSize({ 30, 80 });	// 수정 필요

			_collider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	// Build BT
	{
		// Idle Sequence
		Condition* c1 = new Condition("is cur state Idle?", [&]() {return is_cur_state_idle(); });
		Action* a1 = new Action("Idle", [&]() {return Idle(); });
		Sequence* IdleSequence = new Sequence();
		IdleSequence->addChild(c1);
		IdleSequence->addChild(a1);

		// Chase Sequence
		Condition* c = new Condition("is cur state chase?", [&]() {return is_cur_state_chase(); });
		Action* a = new Action("Chase", [&]() {return Chase(); });
		Sequence* ChaseSequeuce = new Sequence();
		ChaseSequeuce->addChild(c);
		ChaseSequeuce->addChild(a);

		// Hit Sequence
		Condition* c2 = new Condition("is cur state Hit?", [&]() {return is_cur_state_hit(); });
		Action* a2 = new Action("Hit", [&]() {return Hit(); });
		Sequence* HitSequence = new Sequence();
		HitSequence->addChild(c2);
		HitSequence->addChild(a2);

		// Dead Sequence
		Condition* c3 = new Condition("is cur state Dead?", [&]() {return is_cur_state_dead(); });
		Action* a3 = new Action("Dead", [&]() {return Dead(); });
		Sequence* DeadSequence = new Sequence();
		DeadSequence->addChild(c3);
		DeadSequence->addChild(a3);

		// 수정 소환 Sequence
		Condition* c5 = new Condition("is cur state Crystal Creation?", [&]() {return is_cur_state_crystal_creation(); });
		Action* a5 = new Action("CrystalCreation", [&]() {return CrystalCreation(); });
		Sequence* CrystalCreationSequence = new Sequence();
		CrystalCreationSequence->addChild(c5);
		CrystalCreationSequence->addChild(a5);

		// Thrust Sequence
		Condition* c7_1 = new Condition("is cur state Thrust?", [&]() {return is_cur_state_thrust(); });
		Action* a7_1 = new Action("Thrust", [&]() {return Thrust(); });
		Sequence* ThrustSequence = new Sequence();
		ThrustSequence->addChild(c7_1);
		ThrustSequence->addChild(a7_1);

		// BackStep Sequence
		Condition* c7_2 = new Condition("is cur state BackStep?", [&]() {return is_cur_state_backstep(); });
		Action* a7_2 = new Action("BackStep", [&]() {return BackStep(); });
		Sequence* BackStepSequence = new Sequence();
		BackStepSequence->addChild(c7_2);
		BackStepSequence->addChild(a7_2);

		// LongAtk Length Sequence
		Condition* c8_1 = new Condition("is cur state LongAtkLength?", [&]() {return is_cur_state_long_attack_length(); });
		Action* a8_1 = new Action("LongAttackLength", [&]() {return LongAttackLength(); });
		Sequence* LongAtkLengthSequence = new Sequence();
		LongAtkLengthSequence->addChild(c8_1);
		LongAtkLengthSequence->addChild(a8_1);

		// LongAtk Width Sequence
		Condition* c8_2 = new Condition("is cur state LongAtkWidth?", [&]() {return is_cur_state_long_attack_width(); });
		Action* a8_2 = new Action("LongAttackWidth", [&]() {return LongAttackWidth(); });
		Sequence* LongAtkWidthSequence = new Sequence();
		LongAtkWidthSequence->addChild(c8_2);
		LongAtkWidthSequence->addChild(a8_2);

		// Dash Sequence
		Condition* c8_3 = new Condition("is cur State Dash?", [&]() {return is_cur_state_dash(); });
		Action* a8_3 = new Action("Dash", [&]() {return Dash(); });
		Sequence* DashSequence = new Sequence();
		DashSequence->addChild(c8_3);
		DashSequence->addChild(a8_3);

		// Teleport Sequence
		Condition* c9 = new Condition("is cur state teleport?", [&]() {return is_cur_state_teleport(); });
		Action* a9 = new Action("Teleport", [&]() {return Teleport(); });
		Sequence* TeleportSequence = new Sequence();
		TeleportSequence->addChild(c9);
		TeleportSequence->addChild(a9);

		// Cut Severely Sequence
		Condition* c10 = new Condition("is cur state cut severely?", [&]() {return is_cur_state_cut_severely(); });
		Action* a10 = new Action("CutSeverely", [&]() {return CutSeverely(); });
		Sequence* CutSeverelySequence = new Sequence();
		CutSeverelySequence->addChild(c10);
		CutSeverelySequence->addChild(a10);

		// rootNode 설정
		Selector* RootSelector = new Selector();
		RootSelector->addChild(IdleSequence);
		RootSelector->addChild(ChaseSequeuce);
		RootSelector->addChild(HitSequence);
		RootSelector->addChild(DeadSequence);
		RootSelector->addChild(CrystalCreationSequence);
		RootSelector->addChild(ThrustSequence);
		RootSelector->addChild(BackStepSequence);
		RootSelector->addChild(LongAtkLengthSequence);
		RootSelector->addChild(LongAtkWidthSequence);
		RootSelector->addChild(DashSequence);
		RootSelector->addChild(TeleportSequence);
		RootSelector->addChild(CutSeverelySequence);
		_rootNode = RootSelector;

		SetState(IDLE);
	}
}

FinalBoss::~FinalBoss()
{
	GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
}

void FinalBoss::BeginPlay()
{
	Super::BeginPlay();
}

void FinalBoss::Tick()
{
Super::Tick();

	TickGravity();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	
	if (_info.state() != CRYSTAL_CREATION)
	{
		_blancketSumTime += deltaTime;
		_monsterCreationSumTime += deltaTime;
	}

	// Dir
	if (GetFromPlayerXDistance() >= 0)
		SetDir(DIR_LEFT);
	else
		SetDir(DIR_RIGHT);

	// Clamp
	_pos.x = std::clamp(_pos.x, _movementLimit.x, _movementLimit.y);

	// BT
	if (_rootNode)
	{
		_rootNode->run();
	}

	// Blanket
	if (_blancketSumTime >= _stat->blanketSpawnInterval)
	{
		_blancketSumTime = 0.f;

		CreateBlanket();
	}

	// Monster Creation
	if (_monsterCreationSumTime >= _stat->monsterSpawnInterval)
	{
		_monsterCreationSumTime = 0.f;

		CreateMonster();

		_isMonsterCreation = true; //  몬스터 생성했으니 대기 시작
		_monsterIdleSumTime = 0.f;  // 몬스터 생성 Idle 타이머 초기화

		SetState(IDLE);
	}
}

void FinalBoss::Render(HDC hdc)
{
	Super::Render(hdc);
}

void FinalBoss::UpdateAnimation()
{
	switch (_info.state())
	{
	case IDLE:
		_collider->SetSize({ 35, 90 });
		SetFlipbook(_flipbookIdle[_info.dir()]);
		break;
	case CHASE:
		_collider->SetSize({ 60, 90 });
		SetFlipbook(_flipbookChase[_info.dir()]);
		break;
	case HIT:
		_collider->SetSize({ 60, 86 });
		SetFlipbook(_flipbookHit[_info.dir()]);
		break;
	case DEAD:
		_collider->SetSize({ 60, 60 });
		SetFlipbook(_flipbookDead[_info.dir()]);
		break;
	case CRYSTAL_CREATION:
		_collider->SetSize({ 35, 90 });
		SetFlipbook(_flipbookIdle[_info.dir()]);
		break;
	case THRUST:
		_collider->SetSize({ 115, 97 });
		SetFlipbook(_flipbookThrust[_info.dir()]);
		break;
	case BACK_STEP:
		_collider->SetSize({ 115, 97 });
		SetFlipbook(_flipbookBackStep[_info.dir()]);
		break;
	case LONG_ATTACK_LENGTH:
		_collider->SetSize({ 94, 105 });
		SetFlipbook(_flipbookLongAttackLength[_info.dir()]);
		break;
	case LONG_ATTACK_WIDTH:
		_collider->SetSize({ 65, 97 });
		SetFlipbook(_flipbookLongAttackWidth[_info.dir()]);
		break;
	case DASH:
		_collider->SetSize({ 66, 97 });
		SetFlipbook(_flipbookDash[_info.dir()]);
		break;
	case TELEPORT:
		_collider->SetSize({ 35, 90 }); 
		SetFlipbook(_flipbookIdle[_info.dir()]);
		break;
	case CUT_SEVERELY:
		_collider->SetSize({ 110, 65 });
		SetFlipbook(_flipbookCutSeverely[_info.dir()]);
		break;
	}
}

void FinalBoss::OnDamaged(Creature* other)
{
	int32 damage = other->GetAttack();

	if (damage <= 0)
		return;

	// 체력 감소 함수 호출
	SubtractHealthPoint(damage);

	// 체력이 다 닳으면 사망
	if (_stat->hp == 0)
	{
		SetState(DEAD);
		return;
	}

	SetState(HIT);
}

void FinalBoss::SetHealthPoint(int hp)
{
	_stat->hp = hp;

	_healthObserver(_stat->hp);
}

void FinalBoss::AddHealthPoint(int hp)
{
	if (_stat->hp >= 2000)
		return;

	int newHp = _stat->hp + hp; // 증가된 값을 미리 계산

	if (newHp >= 2000)
	{
		_stat->hp = 2000;
	}
	else
	{
		_stat->hp = newHp; // 올바르게 업데이트
	}

	// 관찰자에게 알림
	_healthObserver(_stat->hp);
}

void FinalBoss::SubtractHealthPoint(int hp)
{
	_stat->hp = max(0, _stat->hp - hp);

	// 관찰자에게 알림
	_healthObserver(_stat->hp);
}

int32 FinalBoss::GetAttack()
{
	switch (_info.state())
	{
	case CLOSE_ATTACK:
		return _stat->closeAtkDamage;
		break;
	}
}

void FinalBoss::CalPixelPerSecond()
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

	// Dash
	{
		float DASH_SPEED_KMPH = _stat->dashSpeed;
		float DASH_SPEED_MPM = (DASH_SPEED_KMPH * 1000.0 / 60.0);
		float DASH_SPEED_MPS = (DASH_SPEED_MPM / 60.0);
		float DASH_SPEED_PPS = (DASH_SPEED_MPS * PIXEL_PER_METER);

		_stat->dashSpeed = DASH_SPEED_PPS;
	}

	// LongAtk Projectile 
	{
		float PROJECTILE_SPEED_KMPH = _stat->longAtkProjectileSpeed;
		float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
		float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
		float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

		_stat->longAtkProjectileSpeed = PROJECTILE_SPEED_PPS;
	}

	// Falling Projectile
	{
		// 1
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile1Speed1st;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile1Speed1st = PROJECTILE_SPEED_PPS;
		}
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile1Speed2nd;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile1Speed2nd = PROJECTILE_SPEED_PPS;
		}
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile1Speed3rd;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile1Speed3rd = PROJECTILE_SPEED_PPS;
		}

		// 2
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile2Speed1st;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile2Speed1st = PROJECTILE_SPEED_PPS;
		}
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile2Speed2nd;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile2Speed2nd = PROJECTILE_SPEED_PPS;
		}
		{
			float PROJECTILE_SPEED_KMPH = _stat->fallingProjectile2Speed3rd;
			float PROJECTILE_SPEED_MPM = (PROJECTILE_SPEED_KMPH * 1000.0 / 60.0);
			float PROJECTILE_SPEED_MPS = (PROJECTILE_SPEED_MPM / 60.0);
			float PROJECTILE_SPEED_PPS = (PROJECTILE_SPEED_MPS * PIXEL_PER_METER);

			_stat->fallingProjectile2Speed3rd = PROJECTILE_SPEED_PPS;
		}

	}

}

BehaviorState FinalBoss::is_cur_state_idle()
{
	if (_info.state() == IDLE)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Idle()
{
	UpdatePlayerFloor();
	UpdateBossFloor();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_IdlesumTime += deltaTime;

	if (_isMonsterCreation)
	{
		_monsterIdleSumTime += deltaTime;

		SetPos({ 640, 125 });

		if (_monsterIdleSumTime >= 10.f)
		{
			_isMonsterCreation = false;

			_monsterIdleSumTime = 0.f;
			_IdlesumTime = 0.f;

			SetPos({ 640, 515 });
		}

		return BehaviorState::RUNNING;
	}

	if (_IdlesumTime >= 5.f)
	{
		_IdlesumTime = 0.f;

		if (_bossFloor != _playerFloor)
		{
			SetState(TELEPORT);
			return BehaviorState::SUCCESS;
		}
		else
		{
			SetState(CHASE);
			return BehaviorState::SUCCESS;
		}
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_chase()
{
	if (_info.state() == CHASE)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Chase()
{
	UpdatePlayerFloor();
	UpdateBossFloor();
	UpdateMovementLimit();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_dashTeleportSumTime += deltaTime;
	_atkCoolTime += deltaTime;

	float xDistance = GetAbsFromPlayerXDistance();
	float yDistance = GetAbsFromPlayerYDistance();

	// Chase 유지
	if (xDistance >= _stat->playerDetection.x && _playerFloor == _bossFloor)
	{
		if (_info.dir() == DIR_RIGHT)
			_pos.x += _stat->speed * deltaTime;
		else
			_pos.x -= _stat->speed * deltaTime;

		return BehaviorState::RUNNING;
	}

	// 순간이동
	if (_dashTeleportSumTime >= 5.f)
	{
		_dashTeleportSumTime = 0.f;

		if (_bossFloor != _playerFloor)
		{
			SetState(TELEPORT);
			return BehaviorState::SUCCESS;
		}
	}

	// 근거리 or 원거리 공격
	if (_atkCoolTime >= _stat->atkCooldown && _bossFloor == _playerFloor)
	{
		_atkCoolTime = 0.f;

		if (xDistance <= _stat->closeAtkRange)
		{
			SetState(THRUST);
			return BehaviorState::SUCCESS;
		}
		else if (std::abs(xDistance - _stat->closeAtkRange) > std::abs(xDistance - _stat->longAtkRange))
		{
			std::random_device rd;
			std::mt19937 gen(rd()); // 시드 생성기
			std::uniform_int_distribution<> dist(0, 1); // 0 또는 1 반환

			bool isWidth = (dist(gen) == 0);

			if (isWidth)
				SetState(LONG_ATTACK_WIDTH);
			else
				SetState(LONG_ATTACK_LENGTH);

			return BehaviorState::SUCCESS;
		}

	}
}

BehaviorState FinalBoss::is_cur_state_hit()
{
	if (_info.state() == HIT)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Hit()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static bool knockBackApplied = false;

	// 수정 소환
	if (_stat->hp <= 1000 && _stat->hp > 900 && !_isFirstCrystalCreationWork)
	{
		_isFirstCrystalCreationWork = true;
		_currentCrystalCreationNumber = 1;

		SetState(CRYSTAL_CREATION);
		return BehaviorState::SUCCESS;
	}
	else if (_stat->hp <= 600 && _stat->hp > 500 && !_isSecondCrystalCreationWork)
	{
		_isSecondCrystalCreationWork = true;
		_currentCrystalCreationNumber = 2;

		SetState(CRYSTAL_CREATION);
		return BehaviorState::SUCCESS;

	}
	else if (_stat->hp <= 100 && _isThirdCrystalCreationWork)
	{
		_isThirdCrystalCreationWork = true;
		_currentCrystalCreationNumber = 3;

		SetState(CRYSTAL_CREATION);
		return BehaviorState::SUCCESS;
	}

	// knock back
	if (!knockBackApplied)
	{
		if (_info.dir() == DIR_RIGHT)
			_pos.x -= _stat->knockBackDistance;
		else
			_pos.x += _stat->knockBackDistance;

		knockBackApplied = true;
	}

	_sumTime += deltaTime;

	if (_sumTime >= 0.5f)
	{
		// 난수 생성
		std::random_device rd;
		std::default_random_engine dre{ rd() };
		std::uniform_real_distribution urd{ 0.f, 1.f };

		// 힐템 드랍
		if (urd(dre) <= _stat->healItemDropRate)
		{
			GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

			Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
			ItemActor* item = scene->SpawnObject<ItemActor>({ _pos.x, _pos.y }, LAYER_ITEM, 300100, itemData->GetItems());
		}

		knockBackApplied = false;
		_sumTime = 0.f;

		SetState(CHASE);
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_dead()
{
	if (_info.state() == DEAD)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Dead()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	static float sumTime = 0.f;
	sumTime += deltaTime;

	if (sumTime >= 2.f)
	{
		sumTime = 0.f;

		// 객체 제거
		// 추후 GameScene로 변경할 예정
		//GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		//scene->RemoveActor(this);

		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_crystal_creation()
{
	if (_info.state() == CRYSTAL_CREATION)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::CrystalCreation()
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_hpSumTime += deltaTime;
	_projectileSumTime += deltaTime;
	_crystalCreationSumTime += deltaTime;

	SetPos({ 640, 125 });

	// 수정 생성
	if (!_isCrystalSpawned)
	{
		Crystal* crystal1 = scene->SpawnObject<Crystal>({ 25.50, 521.50 }, LAYER_STRUCTURE);
		crystal1->SetFinalBoss(this);
		Crystal* crystal2 = scene->SpawnObject<Crystal>({ 639.50, 521.50 }, LAYER_STRUCTURE);
		crystal2->SetFinalBoss(this);
		Crystal* crystal3 = scene->SpawnObject<Crystal>({ 1254.50, 521.50 }, LAYER_STRUCTURE);
		crystal3->SetFinalBoss(this);

		_currentCryatalNum = 3;
		_isCrystalSpawned = true;
	}

	// 몬스터 hp 올리기
	if (_hpSumTime >= 1.f)
	{
		_hpSumTime = 0.f;

		switch (_currentCrystalCreationNumber)
		{
		case 3:
			AddHealthPoint(6);
			break;
		case 2:
			AddHealthPoint(4);
			break;
		case 1:
			AddHealthPoint(2);
			break;
		}

	}

	// Projectile Fall
	if (_projectileSumTime >= 1.f)
	{
		_projectileSumTime = 0.f;

		if (_currentFallingProjectile1Count < _stat->fallingProjectile1Count)
			CreateProjectileFall1(_currentCrystalCreationNumber);

		if (_currentFallingProjectile2Count < _stat->fallingProjectile2Count)
			CreateProjectileFall2(_currentCrystalCreationNumber);
	}

	// 상태 변경
	if (_crystalCreationSumTime >= 10.f)
	{
		// 변수 정리
		_crystalCreationSumTime = 0.f;
		_hpSumTime += 0.f;
		_projectileSumTime = 0.f;
		_isCrystalSpawned = false;
		_currentCryatalNum = 0;

		SetPos({ 640, 515 });
		SetState(IDLE);
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_thrust()
{
	if (_info.state() == THRUST)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Thrust()
{
	if (!_attackCollider)
	{
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_MONSTER_ATTACK);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 80, 60 });	// 스프라이트에 따라 수정 필요

			_attackCollider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	if (GetIdx() == _flipbookThrust[_info.dir()]->GetFlipbookEndNum())	// _flipbookThrust[_info.dir()}->GetFlipbookEndNum()
	{
		GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
		RemoveComponent(_attackCollider);
		SAFE_DELETE(_attackCollider);

		SetState(BACK_STEP);

		return BehaviorState::SUCCESS;
	}
}

BehaviorState FinalBoss::is_cur_state_backstep()
{
	if (_info.state() == BACK_STEP)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::BackStep()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_info.dir() == DIR_RIGHT)
		_pos.x -= (_stat->backStepDistance * 2) * deltaTime;
	else
		_pos.x += (_stat->backStepDistance * 2) * deltaTime;

	if (_sumTime >= 0.5f)
	{
		_sumTime = 0.f;
		SetState(CHASE);

		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_long_attack_length()
{
	if (_info.state() == LONG_ATTACK_LENGTH)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::LongAttackLength()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		CreateLengthProjectile();

		return BehaviorState::RUNNING;
	}

	if (_currentProjectileCount == _stat->longAtkProjectileCount)
	{
		SetState(DASH);

		_currentProjectileCount = 0;
		_sumTime = 0.f;

		return BehaviorState::SUCCESS;
	}
}

BehaviorState FinalBoss::is_cur_state_long_attack_width()
{
	if (_info.state() == LONG_ATTACK_WIDTH)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::LongAttackWidth()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= 0.3f)
	{
		_sumTime = 0.f;
		CreateWidthProjectile();

		return BehaviorState::RUNNING;
	}

	if (_currentProjectileCount == _stat->longAtkProjectileCount)
	{
		SetState(DASH);

		_currentProjectileCount = 0;
		_sumTime = 0.f;

		return BehaviorState::SUCCESS;
	}
}

BehaviorState FinalBoss::is_cur_state_dash()
{
	if (_info.state() == DASH)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Dash()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_info.dir() == DIR_RIGHT)
		_pos.x += _stat->dashSpeed * deltaTime;
	else
		_pos.x -= _stat->dashSpeed * deltaTime;

	
	if (_sumTime >= 0.48f)
	{
		_sumTime = 0.f;

		SetState(CHASE);
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

BehaviorState FinalBoss::is_cur_state_teleport()
{
	if (_info.state() == TELEPORT)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::Teleport()
{
	// 이동 
	Vec2 playerPos = _player->GetPos();
	float yPos = 0.f;
	int32 targetFloor = 0;

	switch (_playerFloor)
	{
	case 1:
	{
		yPos = _firstFloorYpos;
		targetFloor = 1;
		break;
	}
	case 2:
	{
		if (playerPos.x < 480 || playerPos.x > 800)
		{
			yPos = _secondFloorYPos;
			targetFloor = 2;
		}
		else
		{
			SetState(IDLE);
			return BehaviorState::SUCCESS;
		}

		break;
	}
	case 3:
	{
		yPos = _thirdFloorYPos;
		targetFloor = 3;
		break;
	}
	}

	Vec2 limit = { 0.f, 0.f };
	switch (targetFloor)
	{
	case 1:
		limit = { 50, 1240 };
		break;
	case 2:
		if (playerPos.x < 480)
			limit = { 40, 440 };
		else if (playerPos.x > 800)
			limit = { 840, 1240 };
		break;
	case 3:
		limit = { 440, 840 };
		break;
	}

	float targetX = (playerPos.x <= _pos.x) ? (playerPos.x - 20.f) : (playerPos.x + 20.f);
	targetX = std::clamp(targetX, limit.x, limit.y);

	_pos = { targetX, yPos };

	SetState(CUT_SEVERELY);
	return BehaviorState::SUCCESS;
}

BehaviorState FinalBoss::is_cur_state_cut_severely()
{
	if (_info.state() == CUT_SEVERELY)
		return BehaviorState::SUCCESS;
	else
		return BehaviorState::FAIL;
}

BehaviorState FinalBoss::CutSeverely()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (!_attackCollider)
	{
		{
			BoxCollider* collider = new BoxCollider();
			collider->ResetCollisionFlag();
			collider->SetCollisionLayer(CLT_FINAL_BOSS_SLASH);

			collider->AddCollisionFlagLayer(CLT_PLAYER);

			collider->SetSize({ 110, 65 });	// 스프라이트에 따라 수정 필요

			_attackCollider = collider;

			GET_SINGLE(CollisionManager)->AddCollider(collider);
			AddComponent(collider);
		}
	}

	if (_sumTime >= 2.5f)
	{
		_sumTime = 0.f;

		GET_SINGLE(CollisionManager)->RemoveCollider(_attackCollider);
		RemoveComponent(_attackCollider);
		SAFE_DELETE(_attackCollider);

		SetState(CHASE);
		return BehaviorState::SUCCESS;
	}

	return BehaviorState::RUNNING;
}

float FinalBoss::GetFromPlayerXDistance()
{
	return this->GetPos().x - _player->GetPos().x;
}

float FinalBoss::GetAbsFromPlayerXDistance()
{
	return std::abs(GetFromPlayerXDistance());
}

float FinalBoss::GetFromPlayerYDistance()
{
	return this->GetPos().y - _player->GetPos().y;
}

float FinalBoss::GetAbsFromPlayerYDistance()
{
	return std::abs(GetFromPlayerXDistance());
}

void FinalBoss::SetSpawnPos(Vec2 pos)
{
	_spawnPos = pos;
	SetPos(_spawnPos);
}

void FinalBoss::SetSpawnDir(Dir dir)
{
	_spawnDir = dir;
	SetDir(dir);
}

void FinalBoss::SetMoveDistance(float distance)
{
	_moveDistance = distance;
	_currentMoveDistance = _moveDistance;
}

void FinalBoss::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	BoxCollider* b1 = dynamic_cast<BoxCollider*>(collider);
	BoxCollider* b2 = dynamic_cast<BoxCollider*>(other);

	if (b1 == nullptr || b2 == nullptr)
		return;
	
	if (b2->GetCollisionLayer() == CLT_PLAYER_ATTACK)
	{
		if (_info.state() == CRYSTAL_CREATION)
			return;

		Creature* otherOwner = dynamic_cast<Creature*>(b2->GetOwner());
		OnDamaged(otherOwner);
	}
}

void FinalBoss::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}

void FinalBoss::CreateWidthProjectile()
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	SlashwaveW* slashwaveW = scene->SpawnObject<SlashwaveW>({ _pos.x, _pos.y }, LAYER_PROJECTILE);
	slashwaveW->SetSpeed(_stat->longAtkProjectileSpeed);
	slashwaveW->SetAttack(_stat->longAtkProjectileDamage);
	slashwaveW->SetRange(_stat->longAtkRange);
	slashwaveW->SetOwner(this);
	slashwaveW->SetDir(_info.dir());

	_currentProjectileCount++;
}

void FinalBoss::CreateLengthProjectile()
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	SlashwaveL* slashwaveH = scene->SpawnObject<SlashwaveL>({ _pos.x, _pos.y }, LAYER_PROJECTILE);
	slashwaveH->SetSpeed(_stat->longAtkProjectileSpeed);
	slashwaveH->SetAttack(_stat->longAtkProjectileDamage);
	slashwaveH->SetRange(_stat->longAtkRange);
	slashwaveH->SetOwner(this);
	slashwaveH->SetDir(_info.dir());

	_currentProjectileCount++;
}

void FinalBoss::CreateProjectileFall1(int32 crystalCreationNumber)
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	std::random_device rd;
	std::mt19937 gen(rd()); // 시드 생성기
	std::uniform_int_distribution<> dist(0, 1200);

	float speed = 0.f;
	int32 damage = 0;

	switch (crystalCreationNumber)
	{
	case 1:
		speed = _stat->fallingProjectile1Speed1st;
		damage = _stat->fallingProjectile1Damage1st;
		break;
	case 2:
		speed = _stat->fallingProjectile1Speed2nd;
		damage = _stat->fallingProjectile1Damage2nd;
		break;
	case 3:
		speed = _stat->fallingProjectile1Speed3rd;
		damage = _stat->fallingProjectile1Damage3rd;
		break;
	}

	FallingProjectile1* fp = scene->SpawnObject<FallingProjectile1>({ float(dist(gen)), 0 }, LAYER_PROJECTILE);	// {float(dist(gen))
	fp->SetSpeed(speed);
	fp->SetAttack(damage);
	fp->SetLandedFallingProjectileDuration(_stat->landedFallingProjectileDuration);
	fp->SetPlayerHitFallingProjectileDuration(_stat->playerHitFallingProjectileDuration);
	fp->SetOwner(this);
	_currentFallingProjectile1Count++;
}

void FinalBoss::CreateProjectileFall2(int32 crystalCreationNumber)
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	std::random_device rd;
	std::mt19937 gen(rd()); // 시드 생성기
	std::uniform_int_distribution<> dist(0, 1200);

	float speed = 0.f;
	int32 damage = 0;

	switch (crystalCreationNumber)
	{
	case 1:
		speed = _stat->fallingProjectile2Speed1st;
		damage = _stat->fallingProjectile2Damage1st;
		break;
	case 2:
		speed = _stat->fallingProjectile2Speed2nd;
		damage = _stat->fallingProjectile2Damage2nd;
		break;
	case 3:
		speed = _stat->fallingProjectile2Speed3rd;
		damage = _stat->fallingProjectile2Damage3rd;
		break;
	}

	FallingProjectile2* fp = scene->SpawnObject<FallingProjectile2>({ float(dist(gen)), 0 }, LAYER_PROJECTILE);	// {float(dist(gen))
	fp->SetSpeed(speed);
	fp->SetAttack(damage);
	fp->SetLandedFallingProjectileDuration(_stat->landedFallingProjectileDuration);
	fp->SetPlayerHitFallingProjectileDuration(_stat->playerHitFallingProjectileDuration);
	fp->SetOwner(this);
	_currentFallingProjectile2Count++;
}

void FinalBoss::CreateBlanket()
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	std::random_device rd;
	std::mt19937 gen(rd()); // 시드 생성기
	std::uniform_int_distribution<> dist(0, 20);

	Blanket* blanket = scene->SpawnObject<Blanket>({ float(dist(gen) * 40), float(540) }, LAYER_PROJECTILE);	// 위치 수정 필요
	blanket->SetAttack(_stat->blanketDamage);
	blanket->SetDuartion(_stat->blanketDuration);
}

void FinalBoss::CreateMonster()
{
	GameScene* scene = dynamic_cast<GameScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());

	// CloseAtk Monster
	{
		CloseAtkMonster* cm = scene->SpawnObject<CloseAtkMonster>({ 500.f, _firstFloorYpos }, LAYER_MONSTER);		// 위치 수정 필요
		cm->SetSpawnDir(DIR_RIGHT);
		cm->SetSpawnPos({ 500.f, _firstFloorYpos });
		cm->SetMoveDistance(240.f);
		cm->SetMovementLimit({ 400.f, 640.f });
	}

	// LongAtk Monster
	{
		LongAtkMonster* lam = scene->SpawnObject<LongAtkMonster>({ 800.f, _firstFloorYpos + 10 }, LAYER_MONSTER);
		lam->SetSpawnDir(DIR_RIGHT);
		lam->SetSpawnPos({ 800.f, _firstFloorYpos + 10 });
		lam->SetMoveDistance(240.f);
		lam->SetMovementLimit({ 640, 800 });
	}
}

void FinalBoss::UpdatePlayerFloor()
{
	int32 playerY = _player->GetPos().y;

	if (playerY >= 0 && playerY < 280)
		_playerFloor = 3;
	else if (playerY >= 280 && playerY < 480)
		_playerFloor = 2;
	else if (playerY >= 480 && playerY < 640)
		_playerFloor = 1;
}

void FinalBoss::UpdateBossFloor()
{
	if (_pos.y >= 0 && _pos.y < 280)
		_bossFloor = 3;
	else if (_pos.y >= 280 && _pos.y < 480)
		_bossFloor = 2;
	else if (_pos.y >= 480 && _pos.y < 640)
		_bossFloor = 1;
}

void FinalBoss::UpdateMovementLimit()
{
	switch (_bossFloor)
	{
	case 1:
		SetMovementLimit({ 50, 1240 });
		break;
	case 2:
	{
		float playerXPos = _player->GetPos().x;
		if (playerXPos < 480)
			SetMovementLimit({ 40, 440 });
		else if (playerXPos > 800)
			SetMovementLimit({ 840, 1240 });

		break;
	}
	case 3:
		SetMovementLimit({ 440, 840 });
		break;
	}
}