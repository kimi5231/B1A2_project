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
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc);	// hdc�� ȣȯ�Ǵ� DC ����
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack);	// DC�� BMP ����
	::DeleteObject(prev);

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
}
