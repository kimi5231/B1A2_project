#pragma once
#include "Scene.h"	// 상속 받으면 전방 선언 의미 없으므로, 무조건 include로 상속 객체 받아야 함.

class Actor;
class ItemActor;
class MyPlayer;

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
	void SetFinalBossStage();

public:
	// Load&&Save
	void SaveCurData();
	void LoadGameData();

public:
	void SetSceneState();	// ESC 입력으로 Menu
	void SetItemAcquireState(ItemActor* item) { _sceneState = SceneState::ItemAcquire; _acquireItem = item; };

	void SetPlayer(MyPlayer* player) { _player = player; }
	MyPlayer* GetMyPlayer() { return _player; }

	void BackGroundRender(HDC hdc);	// 어두운 투명 배경 - 메뉴, 아이템 획득 등에 사용

	// 아이템 획득 효과
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
		// Actor가 맞는지 확인
		auto isActor = std::is_convertible_v<T*, Actor*>;
		assert(isActor);

		// Object 생성
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
	Panel* _menuPanel = nullptr;	// Menu 상태에서만 보여야 해서 _panel과 별개로 변수 생성
	Inventory* _inventory = nullptr;

	int32 _curStageNum;	// 현재 스테이지
	
	// 몬스터 수: stage1 - BCM 2, TOW 4, stage2 - BCM 3, TOW 6, AF 3, stage3 - BCM 2, TOW 6, AF 4
	std::unordered_map<int32, int32> _monsterHpData;	// [몬스터 ID, 몬스터 hp]

	MyPlayer* _player = nullptr;	// 체력, 획득 아이템 등 알기 위해 필요

	ItemActor* _acquireItem = nullptr;	// 아이템 획득 효과에 필요
};
