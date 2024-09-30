#include "pch.h"
#include "Game.h"

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
}

void Game::Update()
{
}

void Game::Render()
{
}
