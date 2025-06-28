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
	void ChangeScene(SceneType sceneType);	// ���ϴ� Scene���� �ٲ�
	Scene* GetCurrentScene() { return _scene; }

private:
	Scene* _scene;	// ���� �����ϰ� �ִ� Scene
	SceneType _sceneType = SceneType::None;
	SceneType _prevSceneType = SceneType::None;

public:
	SceneType GetPrevSceneType() { return _prevSceneType; }
	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }

	void SetIsContinue(bool isContinue) { _isContinue = isContinue; }
	bool GetIsContinue() const { return _isContinue; }

private:
	Vec2  _cameraPos{};

	bool _isContinue = false;	// �̾��ϱ�
};

