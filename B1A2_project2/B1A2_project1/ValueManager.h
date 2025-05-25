#pragma once

// 전역 변수 용도로 쓸 변수들을 관리하는 매니저
class ValueManager
{
	DECLARE_SINGLE(ValueManager);

public:
	void Init(HWND hwnd);

public:
	void SetHwnd(HWND hwnd) { _hwnd = hwnd; }
	HWND GetHwnd() { return _hwnd; }

	void SetWinSize(Vec2Int size) { _winSize = size; }
	Vec2Int GetWinSize() { return _winSize; }

	void SetMapSize(Vec2Int size) { _mapSize = size; }
	Vec2Int GetMapSize() { return _mapSize; }

	// 윈도우 창 크기에 따른 보정값
	Vec2 GetWinSizeAdjustment();
	// 카메라 위치에 따른 보정값
	Vec2 GetCameraPosAdjustment();

	// 월드 좌표계에서의 마우스 좌표
	Vec2 GetMousePosInWorld();

private:
	// 윈도우 핸들
	HWND _hwnd{};

	// 윈도우 창 사이즈
	Vec2Int _winSize{ DefaultWinSizeX, DefaultWinSizeY };

	// 맵 사이즈
	Vec2Int _mapSize{ 6200, 1440 };
};

