#pragma once
#include "SpriteActor.h"

class Player;

class Item : SpriteActor
{
	using Super = SpriteActor;

public:
	Item();
	virtual ~Item() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	// ����
	Player* _owner = nullptr;

	// ������ ���� - �̸�, ����, ����(ResourceManager����)

};

