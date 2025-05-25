#include "pch.h"
#include "TitleScene.h"
#include "TitlePanel.h"
#include "SceneManager.h"
#include "ResourceManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	TitlePanel* panel = new TitlePanel();
	AddPanel(panel);

	Super::Init();
}

void TitleScene::Update()
{
	Super::Update();
}

void TitleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}