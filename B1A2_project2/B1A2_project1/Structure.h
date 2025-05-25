#pragma once
#include "GameObject.h"

class Structure : public GameObject
{
	using Super = GameObject;
public:
	Structure();
	virtual ~Structure() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickMove() {};
	virtual void UpdateAnimation() {};

};

