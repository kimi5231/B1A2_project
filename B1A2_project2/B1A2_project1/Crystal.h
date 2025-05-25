#pragma once
#include "Structure.h"

class Player;
class FinalBoss;

class Crystal : public Structure
{
	using Super = Structure;
public:
	Crystal();
	virtual ~Crystal() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickIdle() {};
	virtual void TickMove() {};
	virtual void TickDuckDown() {};
	virtual void TickDuckDownMove() {};
	virtual void TickJump() {};
	virtual void TickCloseAttack() {};
	virtual void TickLongAttack() {};
	virtual void TickThrust() {};
	virtual void TickBackStep() {};
	virtual void TickSlashWave() {};
	virtual void TickSkill() {};
	virtual void TickHang() {};
	virtual void TickRelease() {};
	virtual void TickHit() {};
	virtual void TickChase() {};
	virtual void TickRoaming() {};
	virtual void TickDash() {};
	virtual void TickReturn() {};
	virtual void TickReturnIdle() {};
	virtual void TickOff() {};
	virtual void TickOn() {};
	virtual void TickDead();
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetPlayer(Player* player) { _player = player; }
	void SetFinalBoss(FinalBoss* finalBoss) { _finalBoss = finalBoss; }
private:
	Flipbook* _flipbookCrystal = nullptr;

	int32 _hp = 200;

	float _creationTime = 0.f;

	Player* _player = nullptr;
	FinalBoss* _finalBoss = nullptr;

};

