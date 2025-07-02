#pragma once
#include "UI.h"

class Flipbook;

class FlipbookUI : public UI
{
	using Super = UI;
public:
	FlipbookUI();
	virtual ~FlipbookUI() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetFilpbook(Flipbook* flipbook);
	void Reset();

protected:
	Flipbook* _flipbook = nullptr;
	float _sumTime = 0.f;
	int32 _idx = 0;
};

