#pragma once
#include "Scene.h"	// ��� ������ ���� ���� �ǹ� �����Ƿ�, ������ include�� ��� ��ü �޾ƾ� ��.

class DevScene : public Scene
{
	using Super = Scene;

public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	void SetSceneState();	// ESC �Է����� Menu
	
	void OnClickGoTitleButton();
	void OnClickMenuButton();
	void OnClickSettingButton();

private:
	Panel* _menuPanel;	// Menu ���¿����� ������ �ؼ� _panel�� ������ ���� ����
};
