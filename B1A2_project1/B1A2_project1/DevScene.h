#pragma once
#include "Scene.h"	// ��� ������ ���� ���� �ǹ� �����Ƿ�, ������ include�� ��� ��ü �޾ƾ� ��.

class GameObject;

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
	// Resource Load
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

public:
	// template func
	template<typename T>
	T* SpawnObject(Vec2 pos)
	{
		// GameObject�� �´��� Ȯ��
		auto isGameObject = std::is_convertible_v<T*, GameObject*>;
		assert(isGameObject);

		// Object ����
		T* object = new T();
		object->SetPos(pos);
		AddActor(object);

		return object;
	}

private:
	Panel* _menuPanel = nullptr;	// Menu ���¿����� ������ �ؼ� _panel�� ������ ���� ����
};
