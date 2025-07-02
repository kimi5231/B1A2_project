#include "pch.h"
#include "ValueManager.h"
#include "SceneManager.h"
#include "InputManager.h"

void ValueManager::Init(HWND hwnd)
{
	// 윈도우 핸들
	_hwnd = hwnd;

	// 윈도우 창 사이즈
	_winSize.x = DefaultWinSizeX;
	_winSize.y = DefaultWinSizeY;
}

Vec2 ValueManager::GetWinSizeAdjustment()
{
	Vec2 adjustment{
		(float)_winSize.x / (float)DefaultWinSizeX,
		(float)_winSize.y / (float)DefaultWinSizeY
	};
	
	return adjustment;
}

Vec2 ValueManager::GetCameraPosAdjustment()
{
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	Vec2 adjustment{
		cameraPos.x - ((float)_winSize.x / 2),
		cameraPos.y - ((float)_winSize.y / 2)
	};

	return adjustment;
}

Vec2 ValueManager::GetMousePosInWorld()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 cameraPosAdjustment = GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GetWinSizeAdjustment();

	// Screen 좌표계에서 Camera 좌표계로 바꾸는 것이기 때문에
	// World 좌표계에서 Camera 좌표계로 바꾸는 연산을 반대로
	Vec2 pos{
		(mousePos.x / winSizeAdjustment.x) + cameraPosAdjustment.x,
		(mousePos.y / winSizeAdjustment.y) + cameraPosAdjustment.y,
	};

	return pos;
}
