#pragma once
class UI
{
public:
	UI();
	virtual ~UI();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render(HDC hdc);

public:
	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }
	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

protected:
	Vec2 _pos{};
	Vec2Int _size{};
};