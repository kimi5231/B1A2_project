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
	void HpRender(HDC hdc);
	void SkillPointRender(HDC hdc);

public:
	void SetPlayer(Player* player) { _player = player; }
	
	void SetHealthPoint(int32 hp) { _hp = hp; }
	void SetSkillPoint(int32 sp) { _skillPoint = sp; }

	void UpdateHealthPoint(int32 health);
	void UpdateSkillPoint(int32 sp);

private:
	Player* _player = nullptr;
	int32 _hp = 100;
	int32 _skillPoint = 0;
};

