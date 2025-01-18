#include "pch.h"
#include "SettingPanel.h"
#include "Button.h"
#include "ValueManager.h"

SettingPanel::SettingPanel()
{
}

SettingPanel::~SettingPanel()
{
}

void SettingPanel::BeginPlay()
{
	// qHD(960*540) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 100, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingPanel::OnClickChangeqHD);
		AddChild(ui);
	}

	// HD(1280*720) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 200, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingPanel::OnClickChangeHD);
		AddChild(ui);
	}

	// FullHD(1920*1080) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 300, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingPanel::OnClickChangeFullHD);
		AddChild(ui);
	}

	// FullScreen �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 400, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingPanel::OnClickChangeFullScreen);
		AddChild(ui);
	}

	Super::BeginPlay();
}

void SettingPanel::Tick()
{
	Super::Tick();
}

void SettingPanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

// CallBack �Լ�
void SettingPanel::OnClickChangeqHD()
{
	// qHD(960*540) ũ��� �����ϱ�
	GET_SINGLE(ValueManager)->SetWinSize({ 960, 540 });
	Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();

	HWND hwnd = GET_SINGLE(ValueManager)->GetHwnd();

	// ���� â ��Ÿ�� ��������
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// â��� ��Ÿ�Ϸ� ��ȯ
	::SetWindowLong(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
	// â ũ�� �缳��
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
}

void SettingPanel::OnClickChangeHD()
{
	// HD(1280*720) ũ��� �����ϱ�
	GET_SINGLE(ValueManager)->SetWinSize({ 1280, 720 });
	Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();

	HWND hwnd = GET_SINGLE(ValueManager)->GetHwnd();

	// ���� â ��Ÿ�� ��������
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// â��� ��Ÿ�Ϸ� ��ȯ
	::SetWindowLong(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
	// â ũ�� �缳��
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
}

void SettingPanel::OnClickChangeFullHD()
{
	// FullHD(1920*1080) ũ��� �����ϱ�
	GET_SINGLE(ValueManager)->SetWinSize({ 1920, 1080 });
	Vec2Int size = GET_SINGLE(ValueManager)->GetWinSize();

	HWND hwnd = GET_SINGLE(ValueManager)->GetHwnd();

	// ���� â ��Ÿ�� ��������
	DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
	// â��� ��Ÿ�Ϸ� ��ȯ
	::SetWindowLong(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
	// â ũ�� �缳��
	::SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
}

void SettingPanel::OnClickChangeFullScreen()
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
}