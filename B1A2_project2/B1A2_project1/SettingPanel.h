#pragma once
#include "Panel.h"

class SettingPanel : public Panel
{
	using Super = Panel;
public:
	SettingPanel();
	virtual ~SettingPanel() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	void OnClickChangeqHD();
	void OnClickChangeHD();
	void OnClickChangeFullHD();
	void OnClickChangeFullScreen();
};