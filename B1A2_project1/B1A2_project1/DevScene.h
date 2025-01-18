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

	void LoadMap();
	void LoadPlayer();
	void LoadDialogue();
	void LoadItem();
	void LoadInventory();
	void LoadMenu();
	void LoadSound();

public:
	void SetSceneState();	// ESC �Է����� Menu
	
	// Menu
	void OnClickGoTitleButton();
	void OnClickMenuButton();
	void OnClickSettingButton();

private:
	Panel* _menuPanel = nullptr;	// Menu ���¿����� ������ �ؼ� _panel�� ������ ���� ����
};
