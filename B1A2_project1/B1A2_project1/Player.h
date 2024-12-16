#pragma once
#include "FlipbookActor.h"
#include <fstream>
#include <iostream>
#include <string>

class Flipbook;
class BoxCollider;

enum class PlayerState
{
	Idle,	// ���
	Move,	// �޸���
	DuckDown,	// ���̱�
	DuckDownMove,	// ���̸鼭 �޸���
	Jump,	// ����
	Hang,	// �Ŵ޸���
	Release,	// ����
	Skill,	// ��ų
	AttackNormal,	// �⺻ ����
	Hit,	// �ǰ�
	Dead	// ���
};

struct PlayerStat
{
	int32 PlayerID = 0;
	int32 healthPoint = 0;
	int32 runSpeed = 0;
	int32 crouchSpeed = 0;
	int32 jumpHeight = 0;
	int32 skillPoint = 0;
	int32 nAtkRange = 0;
	int32 nLongAtkDistance = 0;
	int32 nAtkDamage = 0;
	int32 skillDamage = 0;
	int32 skillRange = 0;
	int32 skillDuration = 0;
	int32 skillStepDistance = 0;

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
				case 0:this->PlayerID = std::stoi(cell); break;
				case 1: this->healthPoint = std::stoi(cell); break;
				case 2: this->runSpeed = std::stoi(cell); break;
				case 3: this->crouchSpeed = std::stoi(cell); break;
				case 4: this->jumpHeight = std::stoi(cell); break;
				case 5: this->skillPoint = std::stoi(cell); break;
				case 6: this->nAtkRange = std::stoi(cell); break;
				case 7: this->nLongAtkDistance = std::stoi(cell); break;
				case 8: this->nAtkDamage = std::stoi(cell); break;
				case 9: this->skillDamage = std::stoi(cell); break;
				case 10: this->skillRange = std::stoi(cell); break;
				case 11: this->skillDuration = std::stoi(cell); break;
				case 12: this->skillStepDistance = std::stoi(cell); break;
				}
				++column;
			}
		}
		ifs.close();
	}
};

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	// Player Stat
	PlayerStat* GetPlayerStat() { return _playerStat; }
	void SetPlayerStat(PlayerStat* playerStat) { _playerStat = playerStat; }
	void CalPixelPerSecond();	// ���ǿ����� ������ �ȼ� ������ �ٲ�

public:
	// Player State
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickDuckDown();
	virtual void TickDuckDownMove();
	virtual void TickJump();
	virtual void TickHang();
	virtual void TickRelease();
	virtual void TickSkill();
	virtual void TickAttackNormal();
	virtual void TickHit();
	virtual void TickDead();

	void SetState(PlayerState);
	void SetDir(Dir dir);

	void UpdateAnimation();

public: 
	// Collider
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);
	
	void AdjustCollisionPos(BoxCollider* b1, BoxCollider* b2);	// ƨ���
	void TickGravity();

private:
	// ���� ���ҽ�
	Flipbook* _flipbookPlayerIdle[2] = {};
	Flipbook* _flipbookPlayerMove[2] = {};
	Flipbook* _flipbookPlayerDuckDown[2] = {};
	Flipbook* _flipbookPlayerDuckDownMove[2] = {};
	Flipbook* _flipbookPlayerJump[2] = {};
	Flipbook* _flipbookPlayerHang[2] = {};
	Flipbook* _flipbookPlayerRelease[2] = {};
	Flipbook* _flipbookPlayerSkill[2] = {};
	Flipbook* _flipbookPlayerAttackNormal[2] = {};
	Flipbook* _flipbookPlayerHit[2] = {};
	Flipbook* _flipbookPlayerDead[2] = {};

private:
	Dir _dir = DIR_RIGHT;
	PlayerState _state;
	bool _keyPressed = false;
	PlayerStat* _playerStat = {};

	// Jump
	int32 _gravity = 1000;
	float _ySpeed = {};

	bool _Ground = false;
	bool _isInAir = false;

	// ȹ���� �������� ����
	std::vector<std::wstring> _ownItemIDs;
};

