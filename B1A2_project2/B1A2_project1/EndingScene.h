#pragma once
#include "Scene.h"

class EndingScene : public Scene
{
	using Super = Scene;
public:
	EndingScene();
	virtual ~EndingScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

