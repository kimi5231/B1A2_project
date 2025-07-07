#pragma once
#include "Actor.h"

class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor;

public:
	SpriteActor();
	virtual ~SpriteActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	// Sprite로 설정하려면
	void SetSprite(Sprite* sprite) { _sprite = sprite; }
	Sprite* GetSprite() { return _sprite; }

protected:
	Sprite* _sprite = nullptr;
};

