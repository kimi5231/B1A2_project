#pragma once
#include "Projectile.h"

class Paper : public Projectile
{
	using Super = Projectile;
public:
	Paper();
	virtual ~Paper() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove();
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	// Flipbook
	Flipbook* _flipbookMove[2];
};