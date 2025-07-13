#pragma once
#include "Scene.h"

class TestScene : public Scene
{
	using Super = Scene;
public:
	TestScene();
	virtual ~TestScene();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Render();

private:
	void LoadTestScene();
};

