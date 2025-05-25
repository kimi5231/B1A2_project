#pragma once
#include "Projectile.h"

class SlashwaveW : public Projectile
{
	using Super = Projectile;
public:
	SlashwaveW();
	virtual ~SlashwaveW() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	virtual float GetSpeed() override;

protected:
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookMove[2];
};

////////////////////////////////////////////////////////////

class SlashwaveL : public Projectile
{
	using Super = Projectile;
public:
	SlashwaveL();
	virtual ~SlashwaveL() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;

public:
	virtual float GetSpeed() override;

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookMove[2];
};

