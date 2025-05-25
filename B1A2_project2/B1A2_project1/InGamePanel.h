#pragma once
#include "Panel.h"

class Player;

class InGamePanel : public Panel
{
	using Super = UI;
public:
	InGamePanel();
	virtual ~InGamePanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetPlayer(Player* player) { _player = player; }
	void UpdateHealthPoint(int32 health);

public:
	Player* _player = nullptr;
	int32 _hp = 100;
};

