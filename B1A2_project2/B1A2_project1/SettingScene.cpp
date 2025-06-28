#include "pch.h"
#include "SettingScene.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SettingPanel.h"

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Init()
{
	// 패널
	{
		SettingPanel* ui = new SettingPanel();
		AddPanel(ui);
	}
	
	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		// 추후 GameScene으로 변경
		if(GET_SINGLE(SceneManager)->GetPrevSceneType() == SceneType::GameScene)
			GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
		else
			GET_SINGLE(SceneManager)->ChangeScene(SceneType::TitleScene);
	}
}

void SettingScene::Render(HDC hdc)
{
	Super::Render(hdc);
}