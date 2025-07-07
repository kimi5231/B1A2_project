#pragma once
#include "Monster.h"

class BoxCollider;

struct BrokenCopyMachineStat
{
	int32 hp;	// A
	float healtemDropRate;	// B
	int32 attackRange;	// C
	float projectileSpeed;	// D
	int32 projectileAttack;	// E
	int32 projectileCount;	// F
	float attackCoolTime;	// G

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
				case 0: this->hp = std::stoi(cell); break;	// A
				case 1: this->healtemDropRate = std::stof(cell); break;	// B
				case 2: this->attackRange = std::stoi(cell); break;	// C
				case 3: this->projectileSpeed = std::stof(cell); break;	// D
				case 4: this->projectileAttack = std::stoi(cell); break;	// E
				case 5: this->projectileCount = std::stoi(cell); break;	// F
				case 6: this->attackCoolTime = std::stof(cell); break;	// G
				}
				++column;
			}
		}
		ifs.close();
	}
};

class BrokenCopyMachine : public Monster
{
	using Super = Monster;
public:
	BrokenCopyMachine();
	virtual ~BrokenCopyMachine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	virtual void TickIdle() override;
	virtual void TickLongAttack() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other) {};

	void AdjustCollisionPosGround(BoxCollider* b1, BoxCollider* b2);

public:
	virtual float GetSpeed() override;
	virtual int32 GetAttack() override;
	virtual int32& GetHp() override { return _stat->hp; }
	virtual Vec2Int GetPlayerDetection() { return {0, 0}; };

private:
	void CalPixelPerSecond();

	void CreateProjectile();

private:
	// Flipbook
	Flipbook* _flipbookIdle[2]{};
	Flipbook* _flipbookLongAttack[2]{};
	Flipbook* _flipbookHit[2]{};
	Flipbook* _flipbookDead[2]{};

private:
	BrokenCopyMachineStat* _stat;

	BoxCollider* _collider;

	int32 _currentProjectileCount = 0;
	float _sumTime = 0.f;
};