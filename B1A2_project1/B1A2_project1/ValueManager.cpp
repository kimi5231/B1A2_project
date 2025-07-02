#include "pch.h"
#include "ValueManager.h"
#include "SceneManager.h"
#include "InputManager.h"

void ValueManager::Init(HWND hwnd)
{
	// ������ �ڵ�
	_hwnd = hwnd;

	// ������ â ������
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

	// Screen ��ǥ�迡�� Camera ��ǥ��� �ٲٴ� ���̱� ������
	// World ��ǥ�迡�� Camera ��ǥ��� �ٲٴ� ������ �ݴ��
	Vec2 pos{
		(mousePos.x / winSizeAdjustment.x) + cameraPosAdjustment.x,
		(mousePos.y / winSizeAdjustment.y) + cameraPosAdjustment.y,
	};

	return pos;
}
