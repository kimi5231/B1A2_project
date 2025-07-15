#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render();

public:
	void ChangeScene(SceneType sceneType);

	std::shared_ptr<class GameObject> Pick(int32 screenX, int32 screenY);

public:
	std::shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private:
	std::shared_ptr<Scene> _activeScene;
	SceneType _sceneType = SceneType::None;
	SceneType _prevSceneType = SceneType::None;
};