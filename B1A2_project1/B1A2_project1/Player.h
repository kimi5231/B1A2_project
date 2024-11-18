#pragma once
#include "FlipbookActor.h"

class Flipbook;

enum class PlayerState
{
	Idle,
	Move,
	Skill
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

private:
	// Player State
	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickSkill();

	void SetState(PlayerState);
	//void SetDir(Dir dir);

	void UpdateAnimation();

	// * ������ ���� �ڵ� �߰� �ʿ�

private:
	// ���� ���ҽ�
	Flipbook* _flipbookPlayerRunRight = nullptr;
	Flipbook* _flipbookPlayerRunLeft = nullptr;

	Vec2Int _cellPos = {};
	Vec2 _speed = {};
	//Dir _dir = DIR_DOWN;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
};

