#pragma once
#include "Projectile.h"

class FallingProjectile1 : public Projectile
{
	using Super = Projectile;
public:
	FallingProjectile1();
	virtual ~FallingProjectile1() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove();
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() override;

	void SetLandedFallingProjectileDuration(float duration) { _landedFallingProjectileDuration = duration; }
	void SetPlayerHitFallingProjectileDuration(float duration) { _playerHitFallingProjectileDuration = duration; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	// Flipbook
	Flipbook* _flipbookMove;

	float _landedFallingProjectileDuration = 0.f;
	float _playerHitFallingProjectileDuration = 0.f;
	float _sumTime = 0.f;
	bool _isArriveGround = false;
	bool _isHitPlayer = false;
};

////////////////////////////////////////////////////////////////////////////////////////////////

class FallingProjectile2 : public Projectile
{
	using Super = Projectile;
public:
	FallingProjectile2();
	virtual ~FallingProjectile2() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove();
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() override;

	void SetLandedFallingProjectileDuration(float duration) { _landedFallingProjectileDuration = duration; }
	void SetPlayerHitFallingProjectileDuration(float duration) { _playerHitFallingProjectileDuration = duration; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	// Flipbook
	Flipbook* _flipbookMove;

	float _landedFallingProjectileDuration = 0.f;
	float _playerHitFallingProjectileDuration = 0.f;
	float _sumTime = 0.f;
	bool _isArriveGround = false;
	bool _isHitPlayer = false;
};

