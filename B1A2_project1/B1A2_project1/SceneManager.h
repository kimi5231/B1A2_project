#pragma once

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

public:
	void ChangeScene(SceneType sceneType);	// ���ϴ� Scene���� �ٲ�

private:
	class Scene* _scene;	// ���� �����ϰ� �ִ� Scene
	SceneType _sceneType = SceneType::None;
};

