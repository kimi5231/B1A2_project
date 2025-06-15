#pragma once
#include "Scene.h"	// ��� ������ ���� ���� �ǹ� �����Ƿ�, ������ include�� ��� ��ü �޾ƾ� ��.

class Actor;
class ItemActor;
class Monster;
class FinalBoss;
class InGamePanel;

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
	void LoadUI();
	void LoadSound();

public:
	// Set Stage
	void SetStage(int32 stage);
private:
	void SetStage1();
	void SetStage2();
	void SetStage3();
	void SetFinalBossStage();

public:
	// Save
	void SaveCurData();
	void LoadGameData();

	void InputDeadMonsterIdAndErasePointer(int32 id) { _deadMonsterIds.push_back(id);  _monsters.erase(id); }

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
	T* SpawnObject(int32 id, Vec2 pos, LAYER_TYPE layer)
	{
		// Actor�� �´��� Ȯ��
		auto isActor = std::is_convertible_v<T*, Actor*>;
		assert(isActor);

		// Object ����
		T* object = new T();
		object->SetID(id);
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
	
	// Stage�� ������ ����
	std::vector<int32> _deadMonsterIds;
	std::unordered_map<int32, Monster*> _monsters;	

	Player* _player = nullptr;	// ü��, ȹ�� ������ �� �˱� ���� �ʿ�

	ItemActor* _acquireItem = nullptr;	// ������ ȹ�� ȿ���� �ʿ�

	FinalBoss* _finalBoss = nullptr;	// ü��
};
