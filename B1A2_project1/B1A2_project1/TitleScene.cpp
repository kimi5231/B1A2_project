#include "pch.h"
#include "TitleScene.h"
#include "Panel.h"
#include "Button.h"
#include "UI.h"

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
		title->SetPos({ 200, 100 });
		title->SetSize({ 300, 100 });
		_panel->AddChild(title);
	}
	
	// ���� ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 600, 300 });
		button->SetSize({ 100, 50 });
		_panel->AddChild(button);
	}

	// ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 600, 400 });
		button->SetSize({ 100, 50 });
		_panel->AddChild(button);
	}

	// ���� ���� Button �߰�
	{
		Button* button = new Button();
		button->SetPos({ 600, 500 });
		button->SetSize({ 100, 50 });
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