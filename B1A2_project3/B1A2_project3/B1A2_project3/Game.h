#pragma once

class Game
{
public:
	void Init(const WindowInfo& info);
	void Update();

private:
	HWND _hwnd = {};	// 윈도우 핸들 번호
	HDC _hdc = {};	// 도화지 번호
};

