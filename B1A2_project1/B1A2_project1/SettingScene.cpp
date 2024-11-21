#include "pch.h"
#include "SettingScene.h"
#include "Panel.h"
#include "Button.h"
#include "ValueManager.h"

SettingScene::SettingScene()
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Init()
{
	// �г�
	{
		Panel* ui = new Panel();
		_panel = ui;
	}
	
	// FullScreen �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({500, 500});
		ui->SetSize({ 100, 100 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeFullScreen);
		_panel->AddChild(ui);
	}

	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();
}

void SettingScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

// callback �Լ�
void SettingScene::ChangeFullScreen()
{
	// ȭ�� ũ��� �����ϱ�
	GET_SINGLE(ValueManager)->SetWinSize({ ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN) });
	Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();
	HWND hwnd = GET_SINGLE(ValueManager)->GetHwnd();

	// ���� â ��Ÿ�� ��������
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// ��üȭ�� ��Ÿ�Ϸ� ��ȯ
	::SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
	// â ũ�� �缳��
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW);
}