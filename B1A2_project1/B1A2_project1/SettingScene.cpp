#include "pch.h"
#include "SettingScene.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Panel.h"
#include "Button.h"

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
	
	// qHD(960*540) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({100, 100});
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeqHD);
		_panel->AddChild(ui);
	}

	// HD(1280*720) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 200, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeHD);
		_panel->AddChild(ui);
	}

	// FullHD(1920*1080) �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 300, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeFullHD);
		_panel->AddChild(ui);
	}

	// FullScreen �׽�Ʈ�� ��ư
	{
		Button* ui = new Button();
		ui->SetPos({ 400, 100 });
		ui->SetSize({ 50, 50 });
		ui->AddOnClickDelegate(this, &SettingScene::ChangeFullScreen);
		_panel->AddChild(ui);
	}

	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"TestMap", L"Sprite\\Map\\TestMap.bmp");
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TestMap");
		Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
		GET_SINGLE(ResourceManager)->CreateSprite(L"TestMap", texture, 0, 0, mapSize.x, mapSize.y);
	
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"TestMap");
		SpriteActor* map = new SpriteActor();
		const Vec2Int size = sprite->GetSize();
		map->SetPos(Vec2(size.x / 2, size.y / 2));
		map->SetSprite(sprite);
		map->SetLayer(LAYER_BACKGROUND);

		AddActor(map);
	}

	Super::Init();
}

void SettingScene::Update()
{
	Super::Update();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::TitleScene);
	}
}

void SettingScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

// CallBack �Լ�
void SettingScene::ChangeqHD()
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

void SettingScene::ChangeHD()
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

void SettingScene::ChangeFullHD()
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
}