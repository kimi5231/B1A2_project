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
};