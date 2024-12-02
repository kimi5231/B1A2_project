#pragma once
#include "FlipbookActor.h"

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
	int32 playerID = 0;
	int32 healthPoint = 0;
	int32 runSpeed = 0;
	int32 crouchSpeed = 0;
	int32 jumpHeight = 0;
	int32 attRange = 0;
	bool enemyExistInAttRange = false;
	int32 attID = 0;
	int32 attDamage = 0;
	int32 attStepDistance = 0;
	int32 skillPoint = 0;
	int32 skillDamage = 0;
	int32 skillRange = 0;
	int32 skillDuration = 0;
	int32 skillStepDistance;
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

	PlayerStat* GetPlayerStat() { return _playerStat; }
	void SetPlayerStat(PlayerStat* playerStat) { _playerStat = playerStat; }

private:
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
	Vec2Int _cellPos = {};
	Dir _dir = DIR_RIGHT;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
	PlayerStat* _playerStat = {};

private:
	int32 _geravity = 1000;
};

