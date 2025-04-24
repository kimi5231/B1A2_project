#pragma once
#include "Scene.h"	// ��� ������ ���� ���� �ǹ� �����Ƿ�, ������ include�� ��� ��ü �޾ƾ� ��.

class Actor;
class ItemActor;

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
	void LoadStage();
	void LoadPlayer();
	void LoadMonster();
	void LoadProjectile();
	void LoadStructure();
	void LoadDialogue();
	void LoadItem();
	void LoadInventory();
	void LoadMenu();
	void LoadSound();

private:
	// Set Stage
	void SetStage(int32 stage);
	void SetStage1();
	void SetStage2();
	void SetStage3();

public:
	// Save
	void SaveCurData();
	void LoadGameData();

public:
	void SetSceneState();	// ESC �Է����� Menu
	void SetItemAcquireState(ItemActor* item) { _sceneState = SceneState::ItemAcquire; _acquireItem = item; };

	void BackGroundRender(HDC hdc);	// ��ο� ���� ��� - �޴�, ������ ȹ�� � ���

	// ������ ȹ�� ȿ��
	void ItemPictureRender(HDC hdc, int32 id);
	void ItemNameRender(HDC hdc, std::wstring name);
	void ItemExplainRender(HDC hdc, std::wstring explain);
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

	template<typename T, typename... Args>
	T* SpawnObject(Vec2 pos, LAYER_TYPE layer, Args&&... args)
	{
		auto isActor = std::is_convertible_v<T*, Actor*>;
		assert(isActor);

		T* object = new T(std::forward<Args>(args)...);
		object->SetPos(pos);
		object->SetLayer(layer);
		AddActor(object);

		return object;
	}

private:
	Panel* _menuPanel = nullptr;	// Menu ���¿����� ������ �ؼ� _panel�� ������ ���� ����
	Inventory* _inventory = nullptr;

	int32 _curStageNum;	// ���� ��������
	
	// ���� ��: stage1 - BCM 2, TOW 4, stage2 - BCM 3, TOW 6, AF 3, stage3 - BCM 2, TOW 6, AF 4
	std::unordered_map<int32, int32> _monsterHpData;	// [���� ID, ���� hp]
	
	Player* _player = nullptr;	// ü��, ȹ�� ������ �� �˱� ���� �ʿ�

	ItemActor* _acquireItem = nullptr;	// ������ ȹ�� ȿ���� �ʿ�
};
