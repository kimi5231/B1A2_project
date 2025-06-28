#pragma once
#include "Panel.h"

class FinalBoss;

class BossStagePanel : public Panel
{
	using Super = UI;
public:
	BossStagePanel();
	virtual ~BossStagePanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void SetFinalBoss(FinalBoss* finalBoss) { _finalBoss = finalBoss; }
	void SetHealthPoint(int32 hp) { _hp = hp; }
	void UpdateHealthPoint(int32 health);

private:
	FinalBoss* _finalBoss = nullptr;
	int32 _hp = 2000;
};

