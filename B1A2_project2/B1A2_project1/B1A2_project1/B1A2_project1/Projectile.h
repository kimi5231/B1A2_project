#pragma once
#include "GameObject.h"

class Creature;

class Projectile : public GameObject
{
	using Super = GameObject;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove() {};
	virtual void UpdateAnimation() {};

public:
	virtual float GetSpeed() = 0;

public:
	void SetSpeed(float speed) { _speed = speed; }
	void SetAttack(int32 attack) { _attack = attack; }
	int32 GetAttack() { return _attack; }
	void SetRange(int32 range) { _range = range; }
	void SetOwner(Creature* owner) { _owner = owner; }

protected:
	float _speed;
	int32 _attack;
	int32 _range;
	Creature* _owner;
};

