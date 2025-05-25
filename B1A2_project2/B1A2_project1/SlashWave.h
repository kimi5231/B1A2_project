#pragma once
#include "Projectile.h"

class Slashwave : public Projectile
{
	using Super = Projectile;
public:
	Slashwave();
	virtual ~Slashwave() override;

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

public:
	void SetDir(Dir dir) { _dir = dir; }

private:
	Flipbook* _flipbookMove[2];
};

