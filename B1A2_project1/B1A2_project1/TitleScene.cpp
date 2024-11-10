#include "pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "UI.h"
#include "Panel.h"
#include "FlipbookUI.h"
#include "Button.h"
#include "Texture.h"
#include "Flipbook.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Super::Init();

	// TitleScene Texture Load
	GET_SINGLE(ResourceManager)->LoadTexture(L"Title", L"Sprite\\UI\\Title.bmp", RGB(55, 255, 0));

	_panel = new Panel();

	// Title �߰�
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Title");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Title");
		fb->SetInfo({ texture, L"FB_Title", { 545, 339 }, 0, 3, 0, 0.5f, true });

		FlipbookUI* title = new FlipbookUI();
		title->SetPos({ 350, 250 });
		title->SetSize({ 545, 339 });
		title->SetFilpbook(fb);
		_panel->AddChild(title);
	}
	
	// ���� ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 1100, 400 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickStartButton);
		_panel->AddChild(button);
	}

	// ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 1100, 500 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickSettingButton);
		_panel->AddChild(button);
	}

	// ���� ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 1100, 600 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickEndButton);
		_panel->AddChild(button);
	}
}

void TitleScene::Update()
{
	Super::Update();
}

void TitleScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void TitleScene::OnClickStartButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void TitleScene::OnClickSettingButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::SettingScene);
}

void TitleScene::OnClickEndButton()
{
	// ���� ������ ������ ������ ����� �޼��� â�� �߰��� ����.
	// �ϴ��� �ٷ� ����ǰ� ����.
	::PostQuitMessage(0);
}