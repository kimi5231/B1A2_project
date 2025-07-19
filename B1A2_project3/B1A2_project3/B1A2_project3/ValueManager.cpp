#include "pch.h"
#include "ValueManager.h"

void ValueManager::Init(HWND hwnd)
{
	// 윈도우 핸들
	_hwnd = hwnd;

	// 윈도우 창 사이즈
	_winSize.x = DefaultWinSizeX;
	_winSize.y = DefaultWinSizeY;
}