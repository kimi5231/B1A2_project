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

private:
	// 윈도우 핸들
	HWND _hwnd{};

	// 윈도우 창 사이즈
	Vec2Int _winSize{ DefaultWinSizeX, DefaultWinSizeY };
};

