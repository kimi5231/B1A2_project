#pragma once
#include "Scene.h"

class Button;

class SettingScene : public Scene
{
	using Super = Scene;
public:
	SettingScene();
	virtual ~SettingScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};