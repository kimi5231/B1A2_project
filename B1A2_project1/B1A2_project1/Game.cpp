#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "ValueManager.h"
#include "CollisionManager.h"
#include "DialogueManager.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);	// hwnd�� hdc �� �� �ִ� �Լ�

	// ��� ��� path �˾Ƴ��� �ڵ�
	_resourcePath = std::filesystem::current_path().relative_path();
	std::filesystem::path _resourcePath = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources";

	// ��Ʈ ���
	std::filesystem::path fullPath = _resourcePath / L"Font\\DungGeunMo.ttf";
	// ��Ʈ �߰�
	::AddFontResourceEx(fullPath.c_str(), FR_PRIVATE, NULL);

	// ���� ���۸� �ڵ�
	::GetClientRect(hwnd, &_rect);

	_hdcBack = ::CreateCompatibleDC(_hdc);	// hdc�� ȣȯ�Ǵ� DC ����
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);	// DC�� BMP ����
	::DeleteObject(prev);

	// �� �Ŵ����� Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd, _resourcePath);
	GET_SINGLE(SoundManager)->Init(hwnd);
	GET_SINGLE(ValueManager)->Init(hwnd);
	GET_SINGLE(CollisionManager)->Init();
	GET_SINGLE(DialogueManager)->Init();

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::TilemapScene);
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(DialogueManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// ������ â ������ ������
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	// â ����� ����ƴ��� Ȯ��
	if ((_rect.right != winSize.x) || (_rect.bottom != winSize.y))
	{
		// ����� ������ ����
		_rect.right = winSize.x;
		_rect.bottom = winSize.y;
		// ���� ��Ʈ�� ����
		HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, NULL);
		::DeleteObject(prev);
		// ����� ����� ���� ��Ʈ�� �����
		_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
		// DC�� ��Ʈ�� ����
		(HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	}

	GET_SINGLE(SceneManager)->Render(_hdcBack);

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		Utils::DrawString(_hdcBack, str, Vec2Int{ 20, 10 });
	}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		Utils::DrawString(_hdcBack, str, Vec2Int{ 550, 10 });
	}

	// Double Buffering
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // ��Ʈ �� : ��� ����
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}