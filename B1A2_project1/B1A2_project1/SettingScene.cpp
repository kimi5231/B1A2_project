#include "pch.h"
#include "SettingScene.h"
#include "InputManager.h"
#include "Panel.h"
#include "Button.h"
#include "ValueManager.h"
#include <iostream>

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
		button = ui;
		//_panel->AddChild(ui);
	}

	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();
	
	button->Tick();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		Vec2 pos = button->GetPos();
		pos.x += 10;
		pos.y += 10;
		button->SetPos(pos);
	}

}

void SettingScene::Render(HDC hdc)
{
	{

		//HDC hdc = GetDC(hwnd);
		//HDC hdc2 = CreateCompatibleDC(hdc);
		
		//SetViewportOrgEx(hdc, 0, 0, NULL);
		//SetWindowOrgEx(hdc, 0, 0, NULL);
		Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetViewportExtEx(hdc, size.x, size.y, NULL);
		SetWindowExtEx(hdc, size.x, size.y, NULL);

	//	//DeleteDC(hdc2);
	//	//ReleaseDC(hwnd, hdc);
	}

	button->Render(hdc);

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
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);

	{
		/*HDC hdc = GetDC(hwnd);

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetViewportExtEx(hdc, 1280, 720, NULL);
		SetWindowExtEx(hdc, size.x, size.y, NULL);
		SetViewportOrgEx(hdc, 100, 100, NULL);
		SetWindowOrgEx(hdc, 0, 0, NULL);
		
		ReleaseDC(hwnd, hdc);*/
	}
}