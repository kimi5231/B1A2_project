#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType sceneType);	// 원하는 Scene으로 바꿈
	Scene* GetCurrentScene() { return _scene; }

private:
	Scene* _scene;	// 현재 실행하고 있는 Scene
	SceneType _sceneType = SceneType::None;
	SceneType _prevSceneType = SceneType::None;

public:
	SceneType GetPrevSceneType() { return _prevSceneType; }
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }

private:
	Vec2  _cameraPos{};
};

