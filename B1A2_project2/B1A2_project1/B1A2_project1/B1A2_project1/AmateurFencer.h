#pragma once
#include "Monster.h"
#include "Player.h"

enum class BehaviorState;
class Node;

struct AmateurFencerStat
{
	int32 hp;	// A
	float healItemDropRate;	// B
	float speed;	// C
	Vec2Int playerDetection;	// D, E
	int32 knockBackDistance; // F
	int32 backStepDistance;	// G
	int32 closeAtkRangeX;	// H
	int32 closeAtkRangeY;	// I
	int32 closeAtkDamage;	// J
	float dashSpeed;	// K
	int32 dashDistance;	// L
	int32 longAtkRange;	// M
	float longAtkProjectileSpeed;	// N
	int32 longAtkProjectileDamage;	// O
	int32 longAtkProjectileCount;	// P
	float atkCooldown;	// Q

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
				case 0: this->hp = std::stoi(cell); break;
				case 1: this->healItemDropRate = std::stof(cell); break;	// B
				case 2: this->speed = std::stof(cell); break;	// C
				case 3: this->playerDetection.x = std::stoi(cell); break;	// D
				case 4: this->playerDetection.y = std::stoi(cell); break;	// E
				case 5: this->knockBackDistance = std::stoi(cell); break;	// F
				case 6: this->backStepDistance = std::stoi(cell); break;	// G
				case 7: this->closeAtkRangeX = std::stoi(cell); break;	// H
				case 8: this->closeAtkRangeY = std::stoi(cell); break;	// I
				case 9: this->closeAtkDamage = std::stoi(cell); break;	// J
				case 10: this->dashSpeed = std::stof(cell); break;	// K
				case 11: this->dashDistance = std::stoi(cell); break;	// L
				case 12: this->longAtkRange = std::stoi(cell); break;	// M
				case 13: this->longAtkProjectileSpeed = std::stof(cell); break;	// N
				case 14: this->longAtkProjectileDamage = std::stoi(cell); break;	// O
				case 15: this->longAtkProjectileCount = std::stoi(cell); break;		// P
				case 16: this->atkCooldown = std::stof(cell); break;
				}
				++column;
			}
		}
		ifs.close();
	}
};

class AmateurFencer : public Monster
{
	using Super = Monster;
public:
	AmateurFencer();
	virtual ~AmateurFencer() override;

	virtual void BeginPlay() override;		// Build BT
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void UpdateAnimation() override;

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

public:
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual float GetSpeed() override { return _stat->speed; }

public:
	void CalPixelPerSecond();

	// Idle Sequence
	BehaviorState is_cur_state_idle();
	BehaviorState Idle();

	// Attacked Sequence
	BehaviorState is_cur_state_hit();
	BehaviorState Hit();

	// Chase Sequence
	BehaviorState is_cur_state_chase();
	BehaviorState Chase();

	// Close Attack Sequence
	BehaviorState is_cur_state_thrust();
	BehaviorState Thrust();
	BehaviorState is_cur_state_backstep();
	BehaviorState BackStep();

	// Long Attack Sequence
	BehaviorState is_cur_state_slashwave();
	BehaviorState SlashWave();
	BehaviorState is_cur_state_dash();
	BehaviorState Dash();

	// Dead
	BehaviorState is_cur_state_dead();
	BehaviorState Dead();

public:
	float GetFromPlayerXDistance();
	float GetAbsFromPlayerXDisatance();
	float GetFromPlayerYDistance();
	float GetAbsFromPlayerYDistance();

	void SetSpawnPos(Vec2 pos);
	void SetSpawnDir(Dir dir);
	void SetMoveDistance(float distance);
	void SetMovementLimit(Vec2 limit) { _movementLimit = limit; }

	virtual Vec2Int GetPlayerDetection() override { return _stat->playerDetection; };

public:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void CreateProjectile();

	void SetPlayer(Player* player) { _player = player; }

private:
	// Flipbook
	Flipbook* _flipbookIdle[2] = {};
	Flipbook* _flipbookHit[2] = {};
	Flipbook* _flipbookChase[2] = {};
	Flipbook* _flipbookThrust[2] = {};
	Flipbook* _flipbookBackStep[2] = {};
	Flipbook* _flipbookSlashWave[2] = {};
	Flipbook* _flipbookDash[2] = {};
	Flipbook* _flipbookDead[2] = {};

private:
	AmateurFencerStat* _stat;
	Node* _rootNode;	// BT 최상위 노드

	Vec2 _spawnPos;
	Dir _spawnDir;
	float _moveDistance;
	Vec2 _movementLimit;

	float _currentMoveDistance;
	BoxCollider* _collider = nullptr;
	Collider* _detectCollider = nullptr;
	Collider* _attackCollider = nullptr;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;

	Player* _player;
};

