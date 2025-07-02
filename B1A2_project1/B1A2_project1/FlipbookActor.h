#pragma once
#include "Actor.h"

class Flipbook;

class FlipbookActor : public Actor
{
	using Super = Actor;

public:
	FlipbookActor();
	virtual ~FlipbookActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetFlipbook(Flipbook* flipbook);
	Flipbook* GetFlipbook() { return _flipbook; }
	void Reset();

	int32 GetIdx() { return _idx; }

private:
	Flipbook* _flipbook = nullptr;
	float _sumTime = 0.f;
	int32 _idx = 0;		// 어디까지 틀었는지 확인
};

