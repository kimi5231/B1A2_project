#pragma once

// ���� ���� �뵵�� �� �������� �����ϴ� �Ŵ���
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

	// ������ â ũ�⿡ ���� ������
	Vec2 GetWinSizeAdjustment();
	// ī�޶� ��ġ�� ���� ������
	Vec2 GetCameraPosAdjustment();

	// ���� ��ǥ�迡���� ���콺 ��ǥ
	Vec2 GetMousePosInWorld();

private:
	// ������ �ڵ�
	HWND _hwnd{};

	// ������ â ������
	Vec2Int _winSize{ DefaultWinSizeX, DefaultWinSizeY };

	// �� ������
	Vec2Int _mapSize{ 3080, 1960 };
};

