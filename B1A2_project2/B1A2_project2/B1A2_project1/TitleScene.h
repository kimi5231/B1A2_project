#pragma once
#include "Scene.h"


class TitleScene : public Scene
{
	using Super = Scene;
public:
	TitleScene();
	virtual ~TitleScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void BackgroundRender(HDC hdc);

public:
	void LoadSound();
	void LoadUI();

	void OnClickBegin();
	void OnClickContinue();

public:
	void SetSceneState();

private:
	Panel* _beginContinuePanel = nullptr;
};