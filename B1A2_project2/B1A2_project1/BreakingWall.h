#pragma once
#include "Structure.h"

class Player;

class BreakingWall : public Structure
{
	using Super = Structure;
public:
	BreakingWall();
	virtual ~BreakingWall() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetWallType(BreakingWallType type);

protected:
	// On 가만히 있음, Breaking 부서지는 중, Dead 부서져서 사라짐
	virtual void TickOn() override;
	virtual void TickDead() override;
	virtual void UpdateAnimation() override;

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetPlayer(Player* player) { _player = player; }

private:
	Flipbook* _flipbookWall = nullptr;
	Flipbook* _flipbookBreakingWall = nullptr;

	int32 _hp = 120;

	Player* _player = nullptr;
};

