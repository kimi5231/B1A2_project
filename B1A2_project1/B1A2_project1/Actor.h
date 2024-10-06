#pragma once

// Compnent & Collider�� ���߿� �߰��ϱ�

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void BeginPlay();	// Init
	virtual void Tick();	// Update
	virtual void Render(HDC hdc);

	// Vector ����� �ּ� Ǯ��
	//void SetPos(Vec2 pos) { _pos = pos; }
	//Vec2 GetPos() { return _pos; }

	void SetLayer(LAYER_TYPE layer) {}

protected:
	//Vec2 _pos = { 0, 0 };
	//Vec2 _destPos = { 0, 0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
};

