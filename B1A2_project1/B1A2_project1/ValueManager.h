#pragma once

// ���� ���� �뵵�� �� �������� �����ϴ� �Ŵ���
class ValueManager
{
	DECLARE_SINGLE(ValueManager);

public:
	void Init(HWND hwnd);
	void Update();

public:
	void SetHinstance(HINSTANCE hInstance) { _hInstance = hInstance; }
	HINSTANCE GetHinstance() { return _hInstance; }

	void SetHwnd(HWND hwnd) { _hwnd = hwnd; }
	HWND GetHwnd() { return _hwnd; }

	void SetWinSize(Vec2Int size) { _winSize = size; }
	Vec2Int GetWinSize() { return _winSize; }

	void SetMapSize(Vec2Int size) { _mapSize = size; }
	Vec2Int GetMapSize() { return _mapSize; }

private:
	// ������ �ڵ�
	HWND _hwnd{};

	// �ν��Ͻ� �ڵ�
	HINSTANCE _hInstance{};

	// ������ â ������
	Vec2Int _winSize{ DefaultWinSizeX, DefaultWinSizeY };

	// �� ������
	Vec2Int _mapSize{6400, 1440};
};

