#pragma once
#include "Monster.h"
#include "Player.h"

enum class BehaviorState;
class Node;
class BoxCollider;

struct FinalBossStat
{
	int32 id;
	int32 hp;
	float healItemDropRate;
	float speed;
	Vec2Int playerDetection;	
	int32 knockBackDistance;
	int32 backStepDistance;
	float dashSpeed;
	int32 dashDistance;
	int32 closeAtkRange;
	int32 closeAtkDamage;
	int32 longAtkRange;
	int32 longAtkProjectileDamage;
	float longAtkProjectileSpeed;
	int32 longAtkProjectileCount;
	int32 slashAtkDamage;
	float atkCooldown;
	int32 blanketDamage;
	float blanketSpawnInterval;
	float blanketDuration;

	float landedFallingProjectileDuration;
	float playerHitFallingProjectileDuration;
	int32 fallingProjectile1Count;
	int32 fallingProjectile2Count;

	float fallingProjectile1Speed1st;
	int32 fallingProjectile1Damage1st;
	float fallingProjectile1Speed2nd;
	int32 fallingProjectile1Damage2nd;
	float fallingProjectile1Speed3rd;
	int32 fallingProjectile1Damage3rd;
	float fallingProjectile1Speed4th;
	int32 fallingProjectile1Damage4th;

	float fallingProjectile2Speed1st;
	int32 fallingProjectile2Damage1st;
	float fallingProjectile2Speed2nd;
	int32 fallingProjectile2Damage2nd;
	float fallingProjectile2Speed3rd;
	int32 fallingProjectile2Damage3rd;
	float fallingProjectile2Speed4th;
	int32 fallingProjectile2Damage4th;
	float monsterSpawnInterval;
	float monsterDuration;
	float crystalDuration;
	int32 skillPointOnCrystalDestroy;
	int32 firstCrustalHealPerSec;
	int32 secondCrystalHealPerSec;
	int32 thridCrystalHealPerSec;


	void LoadFile(const std::wstring& path)
	{
		std::ifstream ifs;
		ifs.open(path);

		std::string line;

		if (std::getline(ifs, line))
		{
			std::istringstream lineStream(line);
			std::string cell;
			int column = 0;

			while (std::getline(lineStream, cell, ','))
			{
				switch (column)
				{
				case 0: id = std::stoi(cell); break;
				case 1: hp = std::stoi(cell); break;
				case 2: healItemDropRate = std::stof(cell); break;
				case 3: speed = std::stof(cell); break;
				case 4: playerDetection.x = std::stoi(cell); break;
				case 5: playerDetection.y = std::stoi(cell); break;
				case 6: knockBackDistance = std::stoi(cell); break;
				case 7: backStepDistance = std::stoi(cell); break;
				case 8: dashSpeed = std::stof(cell); break;
				case 9: dashDistance = std::stoi(cell); break;
				case 10: closeAtkRange = std::stoi(cell); break;
				case 11: closeAtkDamage = std::stoi(cell); break;
				case 12: longAtkRange = std::stoi(cell); break;
				case 13: longAtkProjectileDamage = std::stoi(cell); break;
				case 14: longAtkProjectileSpeed = std::stof(cell); break;
				case 15: longAtkProjectileCount = std::stoi(cell); break;
				case 16: slashAtkDamage = std::stoi(cell); break;
				case 17: atkCooldown = std::stof(cell); break;
				case 18: blanketDamage = std::stoi(cell); break;
				case 19: blanketSpawnInterval = std::stof(cell); break;
				case 20: blanketDuration = std::stof(cell); break;
				case 21: landedFallingProjectileDuration = std::stof(cell); break;
				case 22: playerHitFallingProjectileDuration = std::stof(cell); break;
				case 23: fallingProjectile1Count = std::stoi(cell); break;
				case 24: fallingProjectile2Count = std::stoi(cell); break;
				case 25: fallingProjectile1Speed1st = std::stof(cell); break;
				case 26: fallingProjectile1Damage1st = std::stoi(cell); break;
				case 27: fallingProjectile1Speed2nd = std::stof(cell); break;
				case 28: fallingProjectile1Damage2nd = std::stoi(cell); break;
				case 29: fallingProjectile1Speed3rd = std::stof(cell); break;
				case 30: fallingProjectile1Damage3rd = std::stoi(cell); break;
				case 31: fallingProjectile1Speed4th = std::stof(cell); break;
				case 32: fallingProjectile1Damage4th = std::stoi(cell); break;
				case 33: fallingProjectile2Speed1st = std::stof(cell); break;
				case 34: fallingProjectile2Damage1st = std::stoi(cell); break;
				case 35: fallingProjectile2Speed2nd = std::stof(cell); break;
				case 36: fallingProjectile2Damage2nd = std::stoi(cell); break;
				case 37: fallingProjectile2Speed3rd = std::stof(cell); break;
				case 38: fallingProjectile2Damage3rd = std::stoi(cell); break;
				case 39: fallingProjectile2Speed4th = std::stof(cell); break;
				case 40: fallingProjectile2Damage4th = std::stoi(cell); break;
				case 41: monsterSpawnInterval = std::stof(cell); break;
				case 42: monsterDuration = std::stof(cell); break;
				case 43: crystalDuration = std::stof(cell); break;
				case 44: skillPointOnCrystalDestroy = std::stoi(cell); break;
				case 45: firstCrustalHealPerSec = std::stoi(cell); break;
				case 46: secondCrystalHealPerSec = std::stoi(cell); break;
				case 47: thridCrystalHealPerSec = std::stoi(cell); break;
				default: break;
				}
				++column;
			}
		}
		ifs.close();
	}
};

class FinalBoss : public Monster
{
	using Super = Monster;
public:
	FinalBoss();
	virtual ~FinalBoss() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() override {};
	virtual void TickMove() override {};
	virtual void TickJump() override {};
	virtual void TickCloseAttack() override {};
	virtual void TickLongAttack() override {};
	virtual void TickHit() override {};
	virtual void TickDead() override {};
	virtual void TickChase() override {};
	virtual void TickRoaming() override {};
	virtual void TickReturn() override {};
	virtual void TickReturnIdle() override {};

	virtual void UpdateAnimation() override;

public:
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual float GetSpeed() override { return _stat->speed; };
	virtual Vec2Int GetPlayerDetection() { return { 0, 0 }; }

	virtual void OnDamaged(Creature* other);
public:
	// Hp 
	using HealthObserver = void(*)(int);	// hp 변화시 호출될 콜백 함수 타입
	void SetHealthObserver(std::function<void(int)> observer) { _healthObserver = observer; }
	
	void SetHealthPoint(int hp);
	void AddHealthPoint(int hp);
	void SubtractHealthPoint(int hp);

public:
	void CalPixelPerSecond();

	// Idle Sequence
	BehaviorState is_cur_state_idle();
	BehaviorState Idle();

	//  Chase Sequeuce
	BehaviorState is_cur_state_chase();
	BehaviorState Chase();

	// Hit Sequeucne
	BehaviorState is_cur_state_hit();
	BehaviorState Hit();

	// Dead Sequence;
	BehaviorState is_cur_state_dead();
	BehaviorState Dead();

	// 수정 소환 Sequence
	BehaviorState is_cur_state_crystal_creation();
	BehaviorState CrystalCreation();

	// CloseAtk Sequence
	BehaviorState is_cur_state_thrust();
	BehaviorState Thrust();
	BehaviorState is_cur_state_backstep();
	BehaviorState BackStep();

	// LongAtk Length Sequence
	BehaviorState is_cur_state_long_attack_length();
	BehaviorState LongAttackLength();
	BehaviorState is_cur_state_dash();
	BehaviorState Dash();

	// LongAtk Width Sequence
	BehaviorState is_cur_state_long_attack_width();
	BehaviorState LongAttackWidth();

	// 순간 이동 Sequence
	BehaviorState is_cur_state_teleport();
	BehaviorState Teleport();

	// 마구 베기 Sequence
	BehaviorState is_cur_state_cut_severely();
	BehaviorState CutSeverely();

public:
	float GetFromPlayerXDistance();
	float GetAbsFromPlayerXDistance();
	float GetFromPlayerYDistance();
	float GetAbsFromPlayerYDistance();

	void SetSpawnPos(Vec2 pos);
	void SetSpawnDir(Dir dir);
	void SetMoveDistance(float distance);
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

	void SetPlayer(Player* player) { _player = player; }

public:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void CreateWidthProjectile();	
	void CreateLengthProjectile();
	void CreateProjectileFall1(int32 crystalCreationNumber);	// Projectile Fall
	void CreateProjectileFall2(int32 crystalCreationNumber);
	void CreateBlanket();
	void CreateMonster();

	void SubtractCurrentCrystalCount(int32) { _currentCryatalNum--; }

	void UpdatePlayerFloor();
	void UpdateBossFloor();

	void UpdateMovementLimit();
private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookChase[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookDead[2] = {};
	// 수정 소환 & 몬스터 소환 Flipbook은 Idle로 임시 설정
	Flipbook* _flipbookThrust[2] = {};
	Flipbook* _flipbookBackStep[2] = {};
	Flipbook* _flipbookLongAttackLength[2] = {};
	Flipbook* _flipbookLongAttackWidth[2] = {};
	Flipbook* _flipbookDash[2] = {};
	Flipbook* _flipbookCutSeverely[2] = {};

private:
	FinalBossStat* _stat;
	Node* _rootNode;	// BT 최상위 노드

	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;

	std::function<void(int)> _healthObserver;	// 체력 변화 알림 받을 함수 포인터

	BoxCollider* _collider = nullptr;
	Collider* _attackCollider = nullptr;

	int32 _currentProjectileCount = 0;
	int32 _currentFallingProjectile1Count = 0;
	int32 _currentFallingProjectile2Count = 0;

	int32 _currentMonsterCreationCount = 0;		// 생성할 때
	int32 _currentMonsterCount = 0;		// 생성 후
	int32 _currentCrystalCreationNumber = 0;

	float _sumTime = 0.f;
	float _atkCoolTime = 0.f;
	float _IdlesumTime = 0.f;
	float _dashTeleportSumTime = 0.f;
	float _crystalCreationSumTime = 0.f;
	float _hpSumTime = 0.f;
	float _projectileSumTime = 0.f;
	float _blancketSumTime = 0.f;
	float _monsterCreationSumTime = 0.f;
	float _monsterIdleSumTime = 0.f;

	int32 _playerFloor = 0;
	int32 _bossFloor = 0;
	float _firstFloorYpos = 520;
	float _secondFloorYPos = 370;
	float _thirdFloorYPos = 250;

	bool _isFirstCrystalCreationWork = false;
	bool _isSecondCrystalCreationWork = false;
	bool _isThirdCrystalCreationWork = false;
	bool _isCrystalSpawned = false;
	int32 _currentCryatalNum = 0;

	bool _isMonsterCreation = false;

public:
	Player* _player;
};

