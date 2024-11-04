#include "pch.h"
#include "TitleScene.h"
#include "Panel.h"
#include "Button.h"
#include "UI.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Super::Init();

	_panel = new Panel();

	// Title �߰�
	// �ϴ��� ��ġ Ȯ���� ���� Button���� ���� => ���� ���� ����
	{
		Button* title = new Button();
		title->SetPos({ 350, 250 });
		title->SetSize({ 545, 339 });
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
}

void TitleScene::OnClickEndButton()
{
}
