#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();	// �Ҹ��ڿ� virtual �ʼ�!!!

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
};