#pragma once
#include "Scene.h"	// ��� ������ ���� ���� �ǹ� �����Ƿ�, ������ include�� ��� ��ü �޾ƾ� ��.

class Actor;

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
	void LoadTilemap();
	void LoadPlayer();
	void LoadDialogue();
	void LoadItem();
	void LoadInventory();
	void LoadMenu();
	void LoadSound();

	// Save
	void SaveCurData();
public:
	void SetSceneState();	// ESC �Է����� Menu

public:
	// Menu
	void OnClickGoTitleButton();
	void OnClickMenuButton();
	void OnClickSettingButton();

public:
	// template func
	template<typename T>
	T* SpawnObject(Vec2 pos, LAYER_TYPE layer)
	{
		// Actor�� �´��� Ȯ��
		auto isActor = std::is_convertible_v<T*, Actor*>;
		assert(isActor);

		// Object ����
		T* object = new T();
		object->SetPos(pos);
		object->SetLayer(layer);
		AddActor(object);

		return object;
	}

private:
	Panel* _menuPanel = nullptr;	// Menu ���¿����� ������ �ؼ� _panel�� ������ ���� ����
	
	int32 _monsterCnt = 0;
	std::unordered_map<int32, int32> _monsterHp;	// [ID, hp], ���� ������ �Ҹ��ڿ��� ���� ���� �����ϱ�
	int32 _skillPoint = 0;
	Player* _player = nullptr;	// ü��, ȹ�� ������ �� �˱� ���� �ʿ�
};
