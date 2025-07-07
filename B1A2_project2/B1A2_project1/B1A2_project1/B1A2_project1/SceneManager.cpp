#include "pch.h"
#include "SceneManager.h"
#include "ValueManager.h"
#include "TitleScene.h"
#include "SettingScene.h"
#include "GameScene.h"
#include "TilemapScene.h"

void SceneManager::Init()
{
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	_cameraPos.x = winSize.x / 2;
	_cameraPos.y = winSize.y / 2;
};


void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	// ���ο� Scene ����
	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::TitleScene:
		newScene = new TitleScene();
		break;
	case SceneType::SettingScene:
		newScene = new SettingScene();
		break;
	case SceneType::GameScene:
		newScene = new GameScene();
		break;
	case SceneType::TilemapScene:
		newScene = new TilemapScene();
		break;
	}

	SAFE_DELETE(_scene);

	// ���� Scene�� �����̾����� ����
	_prevSceneType = _sceneType;

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
