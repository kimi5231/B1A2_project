#pragma once
#include "Panel.h"

class TitlePanel : public Panel
{
	using Super = Panel;
public:
	TitlePanel();
	virtual ~TitlePanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void OnClickStartButton();
	void OnClickSettingButton();
	void OnClickEndButton();
};

