#include "pch.h"
#include "Game.h"
#include "InputManager.h"
#include "TimeManager.h"

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

	// ���� ���۸� �ڵ�
	//::GetClientRect(hwnd, &_rect);

	//hdcBack = ::CreateCompatibleDC(_hdc);	// hdc�� ȣȯ�Ǵ� DC ����
	//_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	//HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC�� BMP ����
	//::DeleteObject(prev);

	// �� �Ŵ����� Init
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(TimeManager)->Init();
}

void Game::Update()
{
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(TimeManager)->Update();
}

void Game::Render()
{
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_hdc, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		std::wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(_hdc, 550, 10, str.c_str(), static_cast<int32>(str.size()));
	}
}
