#pragma once

class Scene
{
public:
	Scene();
	virtual ~Scene();	// �Ҹ��ڿ� virtual �ʼ�!!!

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
};

