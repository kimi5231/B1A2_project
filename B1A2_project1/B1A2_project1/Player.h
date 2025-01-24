#pragma once
#include "Creature.h"
#include "FlipbookActor.h"
#include <fstream>
#include <iostream>
#include <string>

class Flipbook;
class BoxCollider;
class ItemActor;

struct PlayerStat
{
	int32 PlayerID = 0;	// A
	int32 healthPoint = 0;	// B
	float runSpeed = 0;	// C
	float crouchSpeed = 0;	// D
	float jumpSpeed = 0;	// E
	int32 skillPoint = 0;	// F
	int32 nAtkRange = 0;	// G
	int32 nLongAtkDistance = 0;	// H
	int32 knockBackDistance = 0;	// I
	float strongAtkMultiplier = 0.f;	// J	
	int32 nAtkDamage = 0;	// K
	int32 skillDamage = 0;	// L
	int32 skillRange = 0;	// M
	float skillDuration = 0;	// N
	int32 skillStepDistance = 0;	// O

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
				case 0:this->PlayerID = std::stoi(cell); break;	// A
				case 1: this->healthPoint = std::stoi(cell); break;	// B
				case 2: this->runSpeed = std::stof(cell); break;	// C
				case 3: this->crouchSpeed = std::stof(cell); break;	// D
				case 4: this->jumpSpeed = std::stof(cell); break;	// E
				case 5: this->skillPoint = std::stoi(cell); break;	// F
				case 6: this->nAtkRange = std::stoi(cell); break;	// G
				case 7: this->nLongAtkDistance = std::stoi(cell); break;	// H
				case 8: this->knockBackDistance = std::stoi(cell); break;	// I
				case 9: this->strongAtkMultiplier = std::stof(cell); break;	// J
				case 10: this->nAtkDamage = std::stoi(cell); break;	// K
				case 11: this->skillDamage = std::stoi(cell); break;	// L
				case 12: this->skillRange = std::stoi(cell); break;	// M
				case 13: this->skillDamage = std::stof(cell); break;	// N
				case 14: this->skillStepDistance = std::stoi(cell); break;	// O
				}
				++column;
			}
		}
		ifs.close();
	}
};

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	// Player State
	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickDuckDown() override;
	virtual void TickDuckDownMove() override;
	virtual void TickJump() override;
	virtual void TickNormalAttack() override;
	virtual void TickSkill() override;
	virtual void TickHang() override;
	virtual void TickRelease() override;
	virtual void TickHit() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

public:
	// Hp �ٲ� ��
	using HealthObserver = void(*)(int);	// hp ��ȭ�� ȣ��� �ݹ� �Լ� Ÿ��
	void SetHealthObserver(std::function<void(int)> observer) { _healthObserver = observer; }
	
	void AddHealthPoint(int hp);
	void SubtractHealthPoint(int hp);

public: 
	// ���ǿ����� ������ �ȼ� ������ �ٲ�
	void CalPixelPerSecond();

	// Collider
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// ƨ���
	void TickGravity();

public:
	// Item
	void RemoveItem(int32 id, int32 count);
	std::unordered_map<int32, int32>& GetAquireItems() { return _acquiredItems; }

private:
	// Flipbook
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerSkill[2] = {};
	Flipbook* _flipbookPlayerNormalAttack[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

private:
	bool _keyPressed = false;

	PlayerStat* _playerStat = {};
	std::function<void(int)> _healthObserver;	// ü�� ��ȭ �˸� ���� �Լ� ������

	// Jump
	int32 _groundCollisionCount = 0;	// �浹���� Ÿ�ϸ� ���� (0���� �� _Ground = true)
	int32 _gravity = 1000;
	float _ySpeed = {};

	bool _isGround = false;
	bool _isAir = false;

	// ȹ���� ������
	ItemActor* _collideItem = {};	// unordered map�� �����ϱ� ����, �浹�� �������� ���� ����
	std::unordered_map<int32, int32> _acquiredItems;		// [������ ID, ����]
};

