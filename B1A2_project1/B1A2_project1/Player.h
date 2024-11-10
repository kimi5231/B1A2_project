#pragma once
#include "FlipbookActor.h"

class Flipbook;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;

public:
	Player();
	virtual ~Player() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:
	// ���� ���ҽ�
	Flipbook* _flipbookPlayerRunRight = nullptr;
	Flipbook* _flipbookPlayerRunLeft = nullptr;
};

