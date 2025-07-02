#pragma once

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {};	// 윈도우 핸들 번호
	HDC _hdc = {};		// 도화지 번호

private:
	// 더블 버퍼링
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};

	// 상대 경로를 위해 Game에 path 넣음(절대 경로로 했을 땐 ResourceManager에서 관리했음)
	std::filesystem::path _resourcePath;
};

