#include "pch.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "Flipbook.h"
#include "Sprite.h"
#include "SpriteActor.h"
#include "Actor.h"
#include "Player.h"
#include "SoundManager.h"
#include "Sound.h"
#include "Tilemap.h"
#include "TilemapActor.h"
#include "ValueManager.h"
#include "Scene.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "DialogueManager.h"
#include "SceneManager.h"
#include "ItemActor.h"
#include "Item.h"
#include "Inventory.h"
#include "Button.h"
#include "Panel.h"
#include "FlipbookUI.h"
#include "TitleScene.h"
#include "InGamePanel.h"
#include "BossStagePanel.h"
#include "TiredOfficeWorker.h"
#include "BrokenCopyMachine.h"
#include "AmateurFencer.h"
#include "DialogueComponent.h"
#include "ZipLine.h"
#include "TimeManager.h"
#include "Stage.h"
#include "ItemStage.h"
#include "StructureStage.h"
#include "LockedDoorAndKey.h"
#include "BreakingWall.h"
#include "Window.h"
#include "FootHold.h"
#include "Blanket.h"
#include "LongAtkMonster.h"
#include "FinalBoss.h"
#include "DestructibleObject.h"
#include "MyPlayer.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	// Resource Load
	LoadStage();
	LoadPlayer();
	LoadMonster();
	LoadProjectile();
	LoadStructure();
	LoadDialogue();
	LoadItem();
	LoadInventory();
	LoadUI();
	//LoadSound();

	GET_SINGLE(ResourceManager)->LoadStat();

	// 스테이지 설정
	if (GET_SINGLE(SceneManager)->GetIsContinue())
	{
		LoadGameData();
		SetStage(_curStageNum);
	}
	else
	{
		_curStageNum = 1;
		SetStage(_curStageNum);
	}

	// Inventory
	//{
	//	Inventory* inventory = new Inventory();
	//	_player->AddComponent(inventory);

	//	inventory->SetOwner(_player);

	//	// Update에서 inventory의 멤버 변수에 접근하기 위해
	//	_inventory = inventory;
	//}

	// InGame UI
	InGamePanel* panel = new InGamePanel();
	//panel->SetPlayer(_player);
	AddPanel(panel);

	// player의 체력 변경 시 UI 업데이트 등록
	//_player->SetHealthObserver([panel](int health) {  if (panel) panel->UpdateHealthPoint(health); });
	//_player->SetSkillPointObserver([panel](int skillPoint) {  if (panel) panel->UpdateSkillPoint(skillPoint); });

	// 현재 Scene 정보 넣기 (세이브 포인트 정보 저장 위해)
	//_player->SetCurrentScene(this);

	// Announcemet
	//{
	//	// Layer 추후 수정 예정
	//	Actor* actor = SpawnObject<Actor>({ 500, 500 }, LAYER_PLAYER);

	//	DialogueComponent* dialogueComponent = new DialogueComponent();
	//	actor->AddComponent(dialogueComponent);
	//	actor->SetID(21);
	//}

	// Start Dialogue
	/*{
		std::vector<Actor*> actors;
		actors.push_back(GetActor(1));
		actors.push_back(GetActor(21));
		GET_SINGLE(DialogueManager)->StartDialogue(L"prologue1", actors);
	}*/

	Super::Init();
}

void GameScene::Update()
{
	if (_hasPendingStage)
	{
		SetStage(_pendingStage);
		_hasPendingStage = false;
		_pendingStage = -1;

		return;
	}

	SetSceneState();	// (Game -> Menu) or (Menu -> Game) or (Menu -> Inventory)

	if (_sceneState == SceneState::Play)
	{
		Super::Update();
	}
	else if (_sceneState == SceneState::Menu)
	{
		if (_menuPanel)
			_menuPanel->Tick();
	}
	else if (_sceneState == SceneState::ItemAcquire)
	{
		static float sumTime = 0.f;
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

		sumTime += deltaTime;

		if (sumTime >= 0.5f)
		{
			_sceneState = SceneState::Play;

			sumTime = 0.f;
		}
	}
	else if (_sceneState == SceneState::Inventory)
	{
		if (_inventory->GetInventoryState() == InventoryState::Show)
			_inventory->TickComponent();
	}
}

void GameScene::Render(HDC hdc)
{
	if (_sceneState == SceneState::Play)
	{
		Super::Render(hdc);
	}
	else if (_sceneState == SceneState::Menu)
	{
		Super::Render(hdc);

		// Background
		BackGroundRender(hdc);

		// Menu Panel
		if (_menuPanel)
			_menuPanel->Render(hdc);
	}
	else if (_sceneState == SceneState::ItemAcquire)
	{
		Super::Render(hdc);

		// Background
		BackGroundRender(hdc);

		// Item 
		if (_acquireItem)
		{
			int32 id = _acquireItem->GetItemInfo()->ID;
			std::wstring name = _acquireItem->GetItemInfo()->name;
			std::wstring explain = _acquireItem->GetItemInfo()->explain;

			// 사진
			ItemPictureRender(hdc, id);
			// 이름
			ItemNameRender(hdc, name);
			// 설명
			ItemExplainRender(hdc, explain);
		}

	}
	else if (_sceneState == SceneState::Inventory)
	{
		if (_inventory->GetInventoryState() == InventoryState::Show)
			_inventory->Render(hdc);
	}
}

void GameScene::LoadStage()
{
	// Stage
	{
		// csv 추가되면 변경 예정
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage1_FieldMonster", L"DataBase\\Stage1_FieldMonster.csv");
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage2_FieldMonster", L"DataBase\\Stage2_FieldMonster.csv");
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage3_FieldMonster", L"DataBase\\Stage3_FieldMonster.csv");
	}

	// Item
	{
		GET_SINGLE(ResourceManager)->LoadItemStage(L"Stage1_Item", L"DataBase\\itemList_Field_Stage1.csv");
		GET_SINGLE(ResourceManager)->LoadItemStage(L"Stage2_Item", L"DataBase\\itemList_Field_Stage2.csv");
		GET_SINGLE(ResourceManager)->LoadItemStage(L"Stage3_Item", L"DataBase\\itemList_Field_Stage3.csv");
	}

	// Structure
	{
		GET_SINGLE(ResourceManager)->LoadStructureStage(L"Stage1_Structure", L"DataBase\\Stage1StructurePosList.csv");
		GET_SINGLE(ResourceManager)->LoadStructureStage(L"Stage2_Structure", L"DataBase\\Stage2StructurePosList.csv");
		GET_SINGLE(ResourceManager)->LoadStructureStage(L"Stage3_Structure", L"DataBase\\Stage3StructurePosList.csv");
	}

	// Map
	{
		// Texture
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage1", L"Sprite\\Map\\Stage1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage2", L"Sprite\\Map\\Stage2.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage3", L"Sprite\\Map\\Stage3.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossStage", L"Sprite\\Map\\FinalBossStage.bmp");

		// Sprite
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stage1");
			GET_SINGLE(ResourceManager)->CreateSprite(L"Stage1", texture, 0, 0, 6200, 1440);
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stage2");
			GET_SINGLE(ResourceManager)->CreateSprite(L"Stage2", texture, 0, 0, 8880, 1720);
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stage3");
			GET_SINGLE(ResourceManager)->CreateSprite(L"Stage3", texture, 0, 0, 3080, 1960);
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossStage");
			GET_SINGLE(ResourceManager)->CreateSprite(L"FinalBossStage", texture, 0, 0, 1280, 720);
		}
	}

	// Tilemap
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage1", L"Tilemap\\Stage1.txt");
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage2", L"Tilemap\\Stage2.txt");
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage3", L"Tilemap\\Stage3.txt");
		GET_SINGLE(ResourceManager)->LoadTilemap(L"FinalBossStage", L"Tilemap\\FinalBossStage.txt");
	}
}

void GameScene::LoadPlayer()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerIdle", L"Sprite\\Player\\PlayerIdle.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerMove", L"Sprite\\Player\\PlayerMove.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerJump", L"Sprite\\Player\\PlayerJump.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDuckDown", L"Sprite\\Player\\PlayerDuckDown.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDuckDownMove", L"Sprite\\Player\\PlayerDuckDownMove.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHang", L"Sprite\\Player\\PlayerHang.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRelease", L"Sprite\\Player\\PlayerRelease.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerSlash", L"Sprite\\Player\\PlayerSlash.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerThrust", L"Sprite\\Player\\PlayerThrust.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHit", L"Sprite\\Player\\PlayerHit.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerSkillReady", L"Sprite\\Player\\PlayerSkillReady.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerSkillWaiting", L"Sprite\\Player\\PlayerSkillWaiting.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerSkillEnd", L"Sprite\\Player\\PlayerSkillEnd.bmp", RGB(55, 255, 0));

	// Idle
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerIdle");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerIdleRight");
		fb1->SetInfo({ texture, L"FB_PlayerIdleRight", {23, 85}, 0, 4, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerIdleLeft");
		fb2->SetInfo({ texture, L"FB_PlayerIdleLeft", {23, 85}, 0, 4, 1, 0.7f });
	}

	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerMove");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerMoveRight");
		fb1->SetInfo({ texture, L"FB_PlayerMoveRight", {67, 70}, 0, 9, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerMoveLeft");
		fb2->SetInfo({ texture, L"FB_PlayerMoveLeft", {67, 70}, 0, 9, 1, 0.7f });
	}

	// Jump
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerJump");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerJumpRight");
		fb1->SetInfo({ texture, L"FB_PlayerJumpRight", {34, 55}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerJumpLeft");
		fb2->SetInfo({ texture, L"FB_PlayerJumpLeft", {34, 55}, 0, 0, 1, 0.7f });
	}

	// DuckDown
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDuckDown");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerDuckDownRight");
		fb1->SetInfo({ texture, L"FB_PlayerDuckDownRight", {35, 45}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerDuckDownLeft");
		fb2->SetInfo({ texture, L"FB_PlayerDuckDownLeft", {35, 45}, 0, 0, 1, 0.7f });
	}

	// DuckDownMove
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDuckDownMove");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerDuckDownMoveRight");
		fb1->SetInfo({ texture, L"FB_PlayerDuckDownMoveRight", {35, 50}, 0, 9, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerDuckDownMoveLeft");
		fb2->SetInfo({ texture, L"FB_PlayerDuckDownMoveLeft", {35, 50}, 0, 9, 1, 0.7f });
	}

	// Hang
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHang");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHangRight");
		fb1->SetInfo({ texture, L"FB_PlayerHangRight", {30, 92}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHangLeft");
		fb2->SetInfo({ texture, L"FB_PlayerHangLeft", {30, 92}, 0, 0, 1, 0.7f });
	}

	// Release
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRelease");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerReleaseRight");
		fb1->SetInfo({ texture, L"FB_PlayerReleaseRight", {34, 88}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerReleaseLeft");
		fb2->SetInfo({ texture, L"FB_PlayerReleaseLeft", {34, 88}, 0, 0, 1, 0.7f });
	}

	// Slash - CloseAtk
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerSlash");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSlashRight");
		fb1->SetInfo({ texture, L"FB_PlayerSlashRight", {75, 90}, 0, 6, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSlashLeft");
		fb2->SetInfo({ texture, L"FB_PlayerSlashLeft", {75, 90}, 0, 6, 1, 0.7f });
	}

	// Thrust - LongAtk
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerThrust");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerThrustRight");
		fb1->SetInfo({ texture, L"FB_PlayerThrustRight", {125, 85}, 0, 14, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerThrustLeft");
		fb2->SetInfo({ texture, L"FB_PlayerThrustLeft", {125, 85}, 0, 14, 1, 0.7f });
	}

	// Hit
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHit");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHitRight");
		fb1->SetInfo({ texture, L"FB_PlayerHitRight", {41, 80}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHitLeft");
		fb2->SetInfo({ texture, L"FB_PlayerHitLeft", {41, 80}, 0, 0, 1, 0.7f });
	}

	// Skill
	{
		// Skill Ready
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerSkillReady");

			// Right
			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillReadyRight");
			fb1->SetInfo({ texture, L"FB_PlayerSkillReadyRight", {140, 85}, 0, 2, 0, 0.7f });

			// Left
			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillReadyLeft");
			fb2->SetInfo({ texture, L"FB_PlayerSkillReadyLeft", {140, 85}, 0, 2, 1, 0.7f });
		}

		// Skill Waiting
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerSkillWaiting");

			// Right
			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillWaitingRight");
			fb1->SetInfo({ texture, L"FB_PlayerSkillWaitingRight", {140, 85}, 0, 0, 0, 0.7f });

			// Left
			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillWaitingLeft");
			fb2->SetInfo({ texture, L"FB_PlayerSkillWaitingLeft", {140, 85}, 0, 0, 1, 0.7f });
		}

		// Skill End
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerSkillEnd");

			// Right
			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillEndRight");
			fb1->SetInfo({ texture, L"FB_PlayerSkillEndRight", {140, 85}, 0, 8, 0, 0.7f });

			// Left
			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSkillEndLeft");
			fb2->SetInfo({ texture, L"FB_PlayerSkillEndLeft", {140, 85}, 0, 8, 1, 0.7f });
		}
	}

}

void GameScene::LoadMonster()
{
	// TOW
	{
		// Idle
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerIdle", L"Sprite\\Monster\\TiredOfficeWorkerIdle.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerIdle");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerIdleRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerIdleRight", {34, 80}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerIdleLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerIdleLeft", {34, 80}, 0, 4, 1, 0.7f });
			}
		}

		// Roaming
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerRoaming", L"Sprite\\Monster\\TiredOfficeWorkerRoaming.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerRoaming");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerRoamingRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerRoamingRight", {50, 81}, 0, 3, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerRoamingLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerRoamingLeft", {50, 81}, 0, 3, 1, 0.7f });
			}
		}

		// Chase
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerChase", L"Sprite\\Monster\\TiredOfficeWorkerChase.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerChase");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerChaseRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerChaseRight", {97, 77}, 0, 5, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerChaseLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerChaseLeft", {97, 77}, 0, 5, 1, 0.7f });
			}
		}

		// CloseAttack
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerCloseAttack", L"Sprite\\Monster\\TiredOfficeWorkerCloseAttack.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerCloseAttack");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerCloseAttackRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerCloseAttackRight", {95, 105}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerCloseAttackLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerCloseAttackLeft", {95, 105}, 0, 4, 1, 0.7f });
			}
		}

		// Hit
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerHit", L"Sprite\\Monster\\TiredOfficeWorkerHit.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerHit");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerHitRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerHitRight", {50, 70}, 0, 0, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerHitLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerHitLeft", {50, 70}, 0, 0, 1, 0.7f });
			}
		}

		// Dead
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorkerDead", L"Sprite\\Monster\\TiredOfficeWorkerDead.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorkerDead");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerDeadRight");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerDeadRight", {60, 78}, 0, 1, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorkerDeadLeft");
				fb->SetInfo({ texture, L"FB_TiredOfficeWorkerDeadLeft", {60, 78}, 0, 1, 1, 0.7f });
			}
		}
	}

	// BCM
	{
		// Idle
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"BrokenCopyMachineIdle", L"Sprite\\Monster\\BrokenCopyMachineIdle.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BrokenCopyMachineIdle");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineIdleRight");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineIdleRight", {40, 55}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineIdleLeft");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineIdleLeft", {40, 55}, 0, 4, 1, 0.7f });
			}
		}

		// LongAttack
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"BrokenCopyMachineLongAttack", L"Sprite\\Monster\\BrokenCopyMachineLongAttack.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BrokenCopyMachineLongAttack");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineLongAttackRight");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineLongAttackRight", {44, 61}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineLongAttackLeft");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineLongAttackLeft", {44, 61}, 0, 4, 1, 0.7f });
			}
		}

		// Hit
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"BrokenCopyMachineHit", L"Sprite\\Monster\\BrokenCopyMachineHit.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BrokenCopyMachineHit");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineHitRight");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineHitRight", {43, 59}, 0, 0, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineHitLeft");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineHitLeft", {43, 59}, 0, 0, 1, 0.7f });
			}
		}

		// Dead
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"BrokenCopyMachineDead", L"Sprite\\Monster\\BrokenCopyMachineDead.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BrokenCopyMachineDead");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineDeadRight");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineDeadRight", {45, 75}, 0, 3, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachineDeadLeft");
				fb->SetInfo({ texture, L"FB_BrokenCopyMachineDeadLeft", {45, 75}, 0, 3, 1, 0.7f });
			}
		}
	}

	// AF
	{
		// Idle
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerIdle", L"Sprite\\Monster\\AmateurFencerIdle.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerIdle");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerIdleRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerIdleRight", {31, 88}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerIdleLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerIdleLeft", {31, 88}, 0, 4, 1, 0.7f });
			}
		}

		// Hit
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerHit", L"Sprite\\Monster\\AmateurFencerHit.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerHit");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerHitRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerHitRight", {75, 65}, 0, 0, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerHitLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerHitLeft", {75, 65}, 0, 0, 1, 0.7f });
			}
		}

		// Chase
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerChase", L"Sprite\\Monster\\AmateurFencerChase.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerChase");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerChaseRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerChaseRight", {90, 100}, 0, 7, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerChaseLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerChaseLeft", {90, 100}, 0, 7, 1, 0.7f });
			}
		}

		// CloseAttack
		{
			// Thrust
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerThrust", L"Sprite\\Monster\\AmateurFencerThrust.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerThrust");

				{
					Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerThrustRight");
					fb->SetInfo({ texture, L"FB_AmateurFencerThrustRight", {145, 88}, 0, 10, 0, 0.7f });
				}
				{
					Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerThrustLeft");
					fb->SetInfo({ texture, L"FB_AmateurFencerThrustLeft", {145, 88}, 0, 10, 1, 0.7f });
				}
			}

			// BackStep
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerBackStep", L"Sprite\\Monster\\AmateurFencerBackStep.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerBackStep");

				{
					Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerBackStepRight");
					fb->SetInfo({ texture, L"FB_AmateurFencerBackStepRight", {145, 88}, 0, 6, 0, 0.7f });
				}
				{
					Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerBackStepLeft");
					fb->SetInfo({ texture, L"FB_AmateurFencerBackStepLeft", {145, 88}, 0, 6, 1, 0.7f });
				}
			}
		}

		// SlashWave - LongAttack
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerLongAttack", L"Sprite\\Monster\\AmateurFencerLongAttack.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerLongAttack");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerSlashWaveRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerSlashWaveRight", {85, 88}, 0, 9, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerSlashWaveLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerSlashWaveLeft", {85, 88}, 0, 9, 1, 0.7f });
			}
		}

		// Dash
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerDash", L"Sprite\\Monster\\AmateurFencerDash.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerDash");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerDashRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerDashRight", {90, 88}, 0, 2, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerDashLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerDashLeft", {90, 88}, 0, 2, 1, 0.7f });
			}
		}

		// Dead
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencerDead", L"Sprite\\Monster\\AmateurFencerDead.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencerDead");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerDeadRight");
				fb->SetInfo({ texture, L"FB_AmateurFencerDeadRight", {75, 60}, 0, 1, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencerDeadLeft");
				fb->SetInfo({ texture, L"FB_AmateurFencerDeadLeft", {75, 60}, 0, 1, 1, 0.7f });
			}
		}
	}

	// FinalBoss
	{
		// Idle
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossIdle", L"Sprite\\Monster\\FinalBossIdle.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossIdle");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossIdleRight");
				fb->SetInfo({ texture, L"FB_FinalBossIdleRight", {35, 90}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossIdleLeft");
				fb->SetInfo({ texture, L"FB_FinalBossIdleLeft", {35, 90}, 0, 4, 1, 0.7f });
			}
		}

		// Chase
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossChase", L"Sprite\\Monster\\FinalBossChase.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossChase");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossChaseRight");
				fb->SetInfo({ texture, L"FB_FinalBossChaseRight", {60, 90}, 0, 4, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossChaseLeft");
				fb->SetInfo({ texture, L"FB_FinalBossChaseLeft", {60, 90}, 0, 7, 1, 0.7f });
			}
		}

		// Hit
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossHit", L"Sprite\\Monster\\FinalBossHit.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossHit");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossHitRight");
				fb->SetInfo({ texture, L"FB_FinalBossHitRight", {60, 86}, 0, 0, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossHitLeft");
				fb->SetInfo({ texture, L"FB_FinalBossHitLeft", {60, 86}, 0, 0, 1, 0.7f });
			}
		}

		// Dead
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossDead", L"Sprite\\Monster\\FinalBossDead.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossDead");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossDeadRight");
				fb->SetInfo({ texture, L"FB_FinalBossDeadRight", {60, 60}, 0, 0, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossDeadLeft");
				fb->SetInfo({ texture, L"FB_FinalBossDeadLeft", {60, 60}, 0, 0, 1, 0.7f });
			}
		}

		// Thrust
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossThrust", L"Sprite\\Monster\\FinalBossThrust.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossThrust");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossThrustRight");
				fb->SetInfo({ texture, L"FB_FinalBossThrustRight", {145, 97}, 0, 5, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossThrustLeft");
				fb->SetInfo({ texture, L"FB_FinalBossThrustLeft", {145, 97}, 0, 5, 1, 0.7f });
			}
		}

		// BackStep
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossBackStep", L"Sprite\\Monster\\FinalBossBackStep.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossBackStep");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossBackStepRight");
				fb->SetInfo({ texture, L"FB_FinalBossBackStepRight", {145, 97}, 0, 5, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossBackStepLeft");
				fb->SetInfo({ texture, L"FB_FinalBossBackStepLeft", {145, 97}, 0, 5, 1, 0.7f });
			}
		}

		// LongAttackLength
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossLongAttackLength", L"Sprite\\Monster\\FinalBossLongAttackLength.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossLongAttackLength");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossLongAttackLengthRight");
				fb->SetInfo({ texture, L"FB_FinalBossLongAttackLengthRight", {94, 105}, 0, 7, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossLongAttackLengthLeft");
				fb->SetInfo({ texture, L"FB_FinalBossLongAttackLengthLeft", {94, 105}, 0, 7, 1, 0.7f });
			}
		}

		// LongAttackWidth
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossLongAttackWidth", L"Sprite\\Monster\\FinalBossLongAttackWidth.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossLongAttackWidth");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossLongAttackWidthRight");
				fb->SetInfo({ texture, L"FB_FinalBossLongAttackWidthRight", {65, 97}, 0, 6, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossLongAttackWidthLeft");
				fb->SetInfo({ texture, L"FB_FinalBossLongAttackWidthLeft", {65, 97}, 0, 6, 1, 0.7f });
			}
		}

		// Dash
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossDash", L"Sprite\\Monster\\FinalBossDash.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossDash");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossDashRight");
				fb->SetInfo({ texture, L"FB_FinalBossDashRight", {66, 97}, 0, 2, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossDashLeft");
				fb->SetInfo({ texture, L"FB_FinalBossDashLeft", {66, 97}, 0, 2, 1, 0.7f });
			}
		}

		// CutServerely
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBossSlash", L"Sprite\\Monster\\FinalBossSlash.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBossSlash");

			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossSlashRight");
				fb->SetInfo({ texture, L"FB_FinalBossSlashRight", {110, 65}, 0, 8, 0, 0.7f });
			}
			{
				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FinalBossSlashLeft");
				fb->SetInfo({ texture, L"FB_FinalBossSlashLeft", {110, 65}, 0, 8, 1, 0.7f });
			}
		}
	}
}

void GameScene::LoadProjectile()
{
	// Paper
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Paper", L"Sprite\\Projectile\\Paper.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Paper");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Paper");
		fb->SetInfo({ texture, L"FB_Paper", {10, 5}, 0, 0, 0, 0.7f });
	}

	// SlashWave - Width
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"SlashWaveW", L"Sprite\\Projectile\\WidthSwordWave.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SlashWaveW");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SlashWaveWRight");
			fb->SetInfo({ texture, L"FB_SlashWaveWRight", {90, 24}, 0, 0, 0, 0.7f });
		}
		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SlashWaveWLeft");
			fb->SetInfo({ texture, L"FB_SlashWaveWLeft", {90, 24}, 0, 0, 1, 0.7f });
		}
	}

	// SlashWave - Length
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"SlashWaveL", L"Sprite\\Projectile\\LengthSwordWave.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SlashWaveL");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SlashWaveLRight");
			fb->SetInfo({ texture, L"FB_SlashWaveLRight", {36, 82}, 0, 0, 0, 0.7f });
		}
		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SlashWaveLLeft");
			fb->SetInfo({ texture, L"FB_SlashWaveLLeft", {36, 82}, 0, 0, 1, 0.7f });
		}
	}

	// Blanket
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Blanket", L"Sprite\\Projectile\\Blanket.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Blanket");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Blanket");
		fb->SetInfo({ texture, L"FB_Blanket", {200, 45}, 0, 2, 0, 0.7f });
	}

	// Falling Projectile
	{
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FallingProjectile1", L"Sprite\\Projectile\\FallingProjectile1.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FallingProjectile1");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FallingProjectile1");
			fb->SetInfo({ texture, L"FB_FallingProjectile1", {54, 142}, 0, 0, 0, 0.7f });
		}
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FallingProjectile2", L"Sprite\\Projectile\\FallingProjectile2.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FallingProjectile2");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FallingProjectile2");
			fb->SetInfo({ texture, L"FB_FallingProjectile2", {54, 122}, 0, 0, 0, 0.7f });
		}
	}
}

void GameScene::LoadStructure()
{
	// LockedDoorAndKey
	{
		// LockedDoor
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"LockedDoor", L"Sprite\\Structure\\LockedDoor.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LockedDoor");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_LockedDoor");
			fb->SetInfo({ texture, L"FB_LockedDoor", {80, 240}, 0, 0, 0, 0.7f });
		}

		// UnlokedDoor
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"UnlockedDoor", L"Sprite\\Structure\\UnlockedDoor.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"UnlockedDoor");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_UnlockedDoor");
			fb->SetInfo({ texture, L"FB_UnlockedDoor", {80, 240}, 0, 0, 0, 0.7f });
		}
	}

	// ZipLine
	{
		// ZipLine
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLine", L"Sprite\\Structure\\ZipLine.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLine");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLine");
			fb->SetInfo({ texture, L"FB_ZipLine", {4, 598}, 0, 0, 0, 0.7f });
		}

		// Grip
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineGrip", L"Sprite\\Structure\\ZipLineGrip.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineGrip");
		}

		// Display
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineDisplay", L"Sprite\\Structure\\ZipLineDisplay.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineDisplay");
		}

		// Button
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineButton", L"Sprite\\Structure\\ZipLineButton.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineButton");

			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineButtonOff");
			fb1->SetInfo({ texture, L"FB_ZipLineButtonOff", {84, 96}, 0, 0, 0, 0.7f });

			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineButtonOn");
			fb2->SetInfo({ texture, L"FB_ZipLineButtonOn", {84, 96}, 0, 0, 1, 0.7f });
		}

		// DestructibleObject
		{
			// DestructibleObject
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"DestructibleObject", L"Sprite\\Structure\\DestructibleObject.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"DestructibleObject");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_DestructibleObject");
				fb->SetInfo({ texture, L"FB_DestructibleObject", {64, 46}, 0, 0, 0, 0.7f });
			}

			// BreakingDestructibleObject
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"BreakingDestructibleObject", L"Sprite\\Structure\\BreakingDestructibleObject.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BreakingDestructibleObject");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BreakingDestructibleObject");
				fb->SetInfo({ texture, L"FB_BreakingDestructibleObject", {64, 46}, 0, 2, 0, 0.7f });
			}
		}
	}

	// BreakingWall
	{
		// Wall
		{
			// Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"Wall", L"Sprite\\Structure\\Wall.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Wall");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Wall");
				fb->SetInfo({ texture, L"FB_Wall", {80, 240}, 0, 0, 0, 0.7f });
			}

			// Breaking Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"BreakingWall", L"Sprite\\Structure\\BreakingWall.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BreakingWall");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BreakingWall");
				fb->SetInfo({ texture, L"FB_BreakingWall", {80, 240}, 0, 2, 0, 0.7f });
			}
		}

		// Short
		{
			// Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"WallShort", L"Sprite\\Structure\\WallShort.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"WallShort");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WallShort");
				fb->SetInfo({ texture, L"FB_WallShort", {80, 160}, 0, 0, 0, 0.7f });
			}

			// Breaking Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"BreakingWallShort", L"Sprite\\Structure\\BreakingWallShort.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BreakingWallShort");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BreakingWallShort");
				fb->SetInfo({ texture, L"FB_BreakingWallShort", {80, 160}, 0, 2, 0, 0.7f });
			}
		}

		// Long
		{
			// Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"WallLong", L"Sprite\\Structure\\WallLong.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"WallLong");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WallLong");
				fb->SetInfo({ texture, L"FB_WallLong", {80, 280}, 0, 0, 0, 0.7f });
			}

			// Breaking Wall
			{
				GET_SINGLE(ResourceManager)->LoadTexture(L"BreakingWallLong", L"Sprite\\Structure\\BreakingWallLong.bmp", RGB(55, 255, 0));
				Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BreakingWallLong");

				Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BreakingWallLong");
				fb->SetInfo({ texture, L"FB_BreakingWallLong", {80, 280}, 0, 2, 0, 0.7f });
			}
		}
	}

	// Window
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Window", L"Sprite\\Structure\\Window.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Window");

		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WindowOff");
		fb1->SetInfo({ texture, L"FB_WindowOff", {280, 120}, 0, 0, 0, 0.7f });

		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_WindowOn");
		fb2->SetInfo({ texture, L"FB_WindowOn", {280, 120}, 0, 0, 1, 0.7f });
	}

	// FootHold
	{
		// FootHoldAndZipLineButton
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FootHoldAndZipLineButton", L"Sprite\\Structure\\FootHoldAndZipLineButton.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FootHoldAndZipLineButton");

			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FootHoldAndZipLineButtonOff");
			fb1->SetInfo({ texture, L"FB_FootHoldAndZipLineButtonOff", { 84, 96 }, 0, 0, 0, 0.7f });

			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FootHoldAndZipLineButtonOn1");
			fb2->SetInfo({ texture, L"FB_FootHoldAndZipLineButtonOn1", { 84, 96 }, 0, 0, 1, 0.7f });

			Flipbook* fb3 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FootHoldAndZipLineButtonOn2");
			fb3->SetInfo({ texture, L"FB_FootHoldAndZipLineButtonOn2", { 84, 96 }, 0, 0, 2, 0.7f });
		}

		// FootHold
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"FootHold", L"Sprite\\Structure\\FootHold.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FootHold");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_FootHold");
			fb->SetInfo({ texture, L"FB_FootHold", {400, 120}, 0, 0, 0, 0.7f });
		}
	}

	// Crystal
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Crystal", L"Sprite\\Structure\\Crystal.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Crystal");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Crystal");
		fb->SetInfo({ texture, L"FB_Crystal", {41, 77}, 0, 0, 0, 0.7f });
	}
}

void GameScene::LoadDialogue()
{
	// Script
	GET_SINGLE(ResourceManager)->LoadDialogue(L"Dialogue", L"Script\\test.csv");
	Dialogue* dialogue = GET_SINGLE(ResourceManager)->GetDialogue(L"Dialogue");
	GET_SINGLE(DialogueManager)->SetDialogue(dialogue);

	// Texture
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueCorner", L"Sprite\\Dialogue\\DialogueCorner.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueTail", L"Sprite\\Dialogue\\DialogueTail.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueWidth", L"Sprite\\Dialogue\\DialogueWidth.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueHeight", L"Sprite\\Dialogue\\DialogueHeight.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueBackground", L"Sprite\\Dialogue\\DialogueBackground.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"DialogueTriangle", L"Sprite\\Dialogue\\DialogueTriangle.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"cutScene1", L"Sprite\\Dialogue\\cutScene1.bmp");

	// Sprite
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueCorner");
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerLeftTop", texture, 0, 0, 7, 6);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerRightTop", texture, 7, 0, 7, 6);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerLeftBottom", texture, 14, 0, 7, 6);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueCornerRightBottom", texture, 21, 0, 7, 6);

	texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueWidth");
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueWidthTop", texture, 0, 0, 1, 6);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueWidthBottom", texture, 1, 0, 1, 6);

	texture = GET_SINGLE(ResourceManager)->GetTexture(L"DialogueHeight");
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueHeightLeft", texture, 0, 0, 7, 1);
	GET_SINGLE(ResourceManager)->CreateSprite(L"DialogueHeightRight", texture, 7, 0, 7, 1);
}

void GameScene::LoadItem()
{
	// Item info
	GET_SINGLE(ResourceManager)->LoadItem(L"Item", L"DataBase\\itemList_Inventory.csv");

	// Texture
	// Map	
	GET_SINGLE(ResourceManager)->LoadTexture(L"F_key", L"Sprite\\Item\\F_key.bmp", RGB(55, 255, 0));

	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Heal", L"Sprite\\Item\\map_Heal.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Key", L"Sprite\\Item\\map_Key.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Multipletap", L"Sprite\\Item\\map_Multipletap.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Gem", L"Sprite\\Item\\map_Gem.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Nametag", L"Sprite\\Item\\map_Nametag.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Sword", L"Sprite\\Item\\map_Sword.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Medal1gold", L"Sprite\\Item\\map_Medal1gold.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Medal2gold", L"Sprite\\Item\\map_Medal2gold.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Photo1", L"Sprite\\Item\\map_Photo1.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Medal3silver", L"Sprite\\Item\\map_Medal3silver.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Photo2", L"Sprite\\Item\\map_Photo2.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Photo3", L"Sprite\\Item\\map_Photo3.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Box", L"Sprite\\Item\\map_Box.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Photo4", L"Sprite\\Item\\map_Photo4.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"map_Poster", L"Sprite\\Item\\map_Poster.bmp", RGB(55, 255, 0));

	// Inventory
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Key", L"Sprite\\Item\\inventory_Key.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Multipletap", L"Sprite\\Item\\inventory_Multipletap.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Gem", L"Sprite\\Item\\inventory_Gem.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Nametag", L"Sprite\\Item\\inventory_Nametag.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Sword", L"Sprite\\Item\\inventory_Sword.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Medal1gold", L"Sprite\\Item\\inventory_Medal1gold.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Medal2gold", L"Sprite\\Item\\inventory_Medal2gold.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Photo1", L"Sprite\\Item\\inventory_Photo1.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Medal3silver", L"Sprite\\Item\\inventory_Medal3silver.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Photo2", L"Sprite\\Item\\inventory_Photo2.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Photo3", L"Sprite\\Item\\inventory_Photo3.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Box", L"Sprite\\Item\\inventory_Box.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Photo4", L"Sprite\\Item\\inventory_Photo4.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"inventory_Poster", L"Sprite\\Item\\inventory_Poster.bmp", RGB(55, 255, 0));

	// Map
	{
		// F button
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"F_key");
			GET_SINGLE(ResourceManager)->CreateSprite(L"F_key", texture, 0, 0, 30, 30);
		}

		// Heal
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Heal");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Heal");
			fb->SetInfo({ texture, L"FB_map_Heal", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// key
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Key");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Key");
			fb->SetInfo({ texture, L"FB_map_Key", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Multipletap
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Multipletap");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Multipletap");
			fb->SetInfo({ texture, L"FB_map_Multipletap", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Gem
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Gem");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Gem");
			fb->SetInfo({ texture, L"FB_map_Gem", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Nametag
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Nametag");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Nametag");
			fb->SetInfo({ texture, L"FB_map_Nametag", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Sword
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Sword");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Sword");
			fb->SetInfo({ texture, L"FB_map_Sword", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Medal1gold
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal1gold");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Medal1gold");
			fb->SetInfo({ texture, L"FB_map_Medal1gold", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Medal2gold
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal2gold");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Medal2gold");
			fb->SetInfo({ texture, L"FB_map_Medal2gold", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Photo1
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo1");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Photo1");
			fb->SetInfo({ texture, L"FB_map_Photo1", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Medal3silver
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal3silver");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Medal3silver");
			fb->SetInfo({ texture, L"FB_map_Medal3silver", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Photo2
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo2");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Photo2");
			fb->SetInfo({ texture, L"FB_map_Photo2", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Photo3
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo3");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Photo3");
			fb->SetInfo({ texture, L"FB_map_Photo3", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Box
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Box");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Box");
			fb->SetInfo({ texture, L"FB_map_Box", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Photo4
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo4");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Photo4");
			fb->SetInfo({ texture, L"FB_map_Photo4", {30, 30}, 0, 2, 0, 0.7f, true });
		}

		// Poster
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Poster");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_map_Poster");
			fb->SetInfo({ texture, L"FB_map_Poster", {30, 30}, 0, 2, 0, 0.7f, true });
		}
	}
}

void GameScene::LoadInventory()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Inventory", L"Sprite\\Inventory\\Inventory.bmp");

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Inventory");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Inventory", texture, 0, 0, 1280, 720);
}

void GameScene::LoadUI()
{
	// Menu
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"GoTitle", L"Sprite\\UI\\GoTitle.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"InventoryButton", L"Sprite\\UI\\Inventory.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"Setting", L"Sprite\\UI\\Setting.bmp", RGB(55, 255, 0));

		_menuPanel = new Panel();
	}

	// Go Title
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GoTitle");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GoTitleDefault");
			fb->SetInfo({ texture, L"FB_GoTitleDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GoTitleHovered");
			fb->SetInfo({ texture, L"FB_GoTitleHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 1100, 400 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &GameScene::OnClickGoTitleButton);
		_menuPanel->AddChild(button);
	}

	// Inventory
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"InventoryButton");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_InventoryDefault");
			fb->SetInfo({ texture, L"FB_InventoryDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_InventoryHover");
			fb->SetInfo({ texture, L"FB_InventoryHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}


		button->SetPos({ 1100, 500 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &GameScene::OnClickMenuButton);
		_menuPanel->AddChild(button);
	}

	// Setting
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Setting");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SettingDefault");
			fb->SetInfo({ texture, L"FB_SettingDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SettingHover");
			fb->SetInfo({ texture, L"FB_SettingHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 1100, 600 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &GameScene::OnClickSettingButton);
		_menuPanel->AddChild(button);
	}

	GET_SINGLE(ResourceManager)->LoadTexture(L"MenuBackground", L"Sprite\\UI\\MenuBackground.bmp", RGB(0, 0, 0));
	// HP
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"HpBar", L"Sprite\\UI\\HpBar.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"HpPoint", L"Sprite\\UI\\HpPoint.bmp", RGB(55, 255, 0));
	}

	// Skill Point
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"SkillPointBar", L"Sprite\\UI\\SkillPointBar.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"SkillPoint", L"Sprite\\UI\\SkillPoint.bmp", RGB(55, 255, 0));
	}

	// Boss HP
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBoss_HpBar", L"Sprite\\UI\\FinalBoss_HpBar.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"FinalBoss_HpPoint", L"Sprite\\UI\\FinalBoss_HpPoint.bmp", RGB(55, 255, 0));
	}
}

void GameScene::LoadSound()
{
	// BGM
	{
		//GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");

		//Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		//sound->Play(true);
	}

	// UI
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"Click", L"Sound\\Click.wav");
	}

	// Player
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"PlayerCloseAtk", L"Sound\\PlayerCloseAtk.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"PlayerLongAtk", L"Sound\\PlayerLongAtk.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"PlayerPickUpItem", L"Sound\\PlayerPickUpItem.wav");
	}

	// TOW
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"TowCloseAtk", L"Sound\\TowCloseAtk.wav");
	}

	// BCM
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"BcmLongAtk", L"Sound\\BcmLongAtk.wav");
	}

	// AF
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"AfCloseAtk", L"Sound\\AfCloseAtk.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"AfLongAtk", L"Sound\\AfLongAtk.wav");
	}

	// FB
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"FbCloseAtk", L"Sound\\FbCloseAtk.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"FbLongAtk", L"Sound\\FbLongAtk.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"FbSlashAtk", L"Sound\\FbSlashAtk.wav");
	}

	// Projectile, Structure
	{
		GET_SINGLE(ResourceManager)->LoadSound(L"FallingProjectile1", L"Sound\\FallingProjectile1.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"FallingProjectile2", L"Sound\\FallingProjectile2.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"BreakCrystal", L"Sound\\BreakCrystal.wav");

		GET_SINGLE(ResourceManager)->LoadSound(L"UnlockedDoorOpen", L"Sound\\UnlockedDoorOpen.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"BreakingWall", L"Sound\\BreakingWall.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"BreakingObject", L"Sound\\BreakingObject.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"ZipLineButtonPress", L"Sound\\ZipLineButtonPress.wav");
		GET_SINGLE(ResourceManager)->LoadSound(L"WindowFlickering", L"Sound\\WindowFlickering.wav");
	}
}

void GameScene::SetStage(int32 stage)
{
	_curStageNum = stage;
	_monsters.clear();

	// 이전 스테이지 내용 삭제
	// 저장된 세이브 파일 삭제
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";
	if (std::filesystem::exists(path))
		std::filesystem::remove(path);

	switch (stage)
	{
	case 1:
		SetStage1();
		break;
	case 2:
		SetStage2();
		break;
	case 3:
		SetStage3();
		break;
	case 4:
		SetFinalBossStage();
		break;
	}
}

void GameScene::SetStage1()
{
	// 이전 스테이지 객체 삭제 (Player, UI 제외)
	{
		for (const std::vector<Actor*>& actors : _actors)
		{
			if (actors == _actors[LAYER_PLAYER])
				break;

			for (Actor* actor : actors)
			{
				toRemove.push_back(actor);
			}
		}
	}

	for (Actor* actor : toRemove)
		RemoveActor(actor);


	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage1");

		const Vec2Int size = sprite->GetSize();
		SpriteActor* map = SpawnObject<SpriteActor>(-1, Vec2(size.x / 2, size.y / 2), LAYER_BACKGROUND);
		map->SetSprite(sprite);

		GET_SINGLE(ValueManager)->SetMapSize(size);
	}

	// Tilemap
	{
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Stage1");

		TilemapActor* actor = SpawnObject<TilemapActor>(-2, { 0, 0 }, LAYER_TILEMAP);
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
	}

	// Player
	{
		// Player가 없다면 생성
		/*if (!_player)
		{
			MyPlayer* player = SpawnObject<MyPlayer>(1, { 200, 400 }, LAYER_PLAYER);
			_player = player;
		}

		_player->SetCurStageNum(_curStageNum);*/
	}

	// Monster
	{
		Stage* stage = GET_SINGLE(ResourceManager)->GetStage(L"Stage1_FieldMonster");
		const std::vector<StageInfo>& infos = stage->GetInfos();

		for (const StageInfo& info : infos)
		{
			// TOW
			if (info.id > 20100 && info.id <= 20199)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				TiredOfficeWorker* TOW = SpawnObject<TiredOfficeWorker>(info.id, info.spawnPos, LAYER_MONSTER);
				TOW->SetMonsterId(info.id);
				TOW->SetSpawnDir(info.dir);
				TOW->SetSpawnPos(info.spawnPos);
				TOW->SetMoveDistance(info.movingDistance);
				TOW->SetMovementLimit(info.movementLimit);
				_monsters[info.id] = TOW;
				continue;
			}

			// BCM
			if (info.id > 20200 && info.id <= 20299)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				BrokenCopyMachine* BCM = SpawnObject<BrokenCopyMachine>(info.id, info.spawnPos, LAYER_MONSTER);
				BCM->SetMonsterId(info.id);
				BCM->SetDir(info.dir);
				_monsters[info.id] = BCM;
				continue;
			}
		}
	}

	// Item
	{
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		ItemStage* itemStage = GET_SINGLE(ResourceManager)->GetItemStage(L"Stage1_Item");
		const std::vector<ItemStageInfo>& infos = itemStage->GetItemStageInfos();

		for (const ItemStageInfo& info : infos)
		{
			ItemActor* item = SpawnObject<ItemActor>({ info.spawnPos }, LAYER_ITEM, info.id, itemData->GetItems());
		}
	}

	// Structure
	//SetStructureStageN(1);

	// LoadData 적용
	if (GET_SINGLE(SceneManager)->GetIsContinue())
	{
		_player->SetPos(_loadData.playerPos);
		_player->SetHp(_loadData.playerHp);
		_player->SetSkillPoint(_loadData.skillPoint);
		_player->SetAcquireItems(_loadData.playerItems);
	}

	Super::Init();
}

void GameScene::SetStage2()
{
	// 이전 스테이지 객체 삭제 (Player, UI 제외)
	{
		for (const std::vector<Actor*>& actors : _actors)
		{
			if (actors == _actors[LAYER_PLAYER])
				break;

			for (Actor* actor : actors)
			{
				toRemove.push_back(actor);
			}
		}
	}

	for (Actor* actor : toRemove)
		RemoveActor(actor);

	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage2");

		const Vec2Int size = sprite->GetSize();
		SpriteActor* map = SpawnObject<SpriteActor>(Vec2(size.x / 2, size.y / 2), LAYER_BACKGROUND);
		map->SetSprite(sprite);

		GET_SINGLE(ValueManager)->SetMapSize(size);
	}

	// Tilemap
	{
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Stage2");

		TilemapActor* actor = SpawnObject<TilemapActor>(-2, { 0, 0 }, LAYER_TILEMAP);
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
	}

	// Player
	{
		// Player가 없다면 생성
		if (!_player)
		{
			MyPlayer* player = SpawnObject<MyPlayer>({ 370, 200 }, LAYER_PLAYER);
			_player = player;
		}

		_player->SetPos({ 370, 200 });
		_player->SetCurStageNum(_curStageNum);
	}

	// Monster
	{
		Stage* stage = GET_SINGLE(ResourceManager)->GetStage(L"Stage2_FieldMonster");
		const std::vector<StageInfo>& infos = stage->GetInfos();

		for (const StageInfo& info : infos)
		{
			// TOW
			if (info.id > 20100 && info.id <= 20199)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue; // 죽은 몬스터는 생성하지 않음

				TiredOfficeWorker* TOW = SpawnObject<TiredOfficeWorker>(info.spawnPos, LAYER_MONSTER);
				TOW->SetMonsterId(info.id);
				TOW->SetSpawnDir(info.dir);
				TOW->SetSpawnPos(info.spawnPos);
				TOW->SetMoveDistance(info.movingDistance);
				TOW->SetMovementLimit(info.movementLimit);
				_monsters[info.id] = TOW;
				continue;
			}

			// BCM
			if (info.id > 20200 && info.id <= 20299)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				BrokenCopyMachine* BCM = SpawnObject<BrokenCopyMachine>(info.spawnPos, LAYER_MONSTER);
				BCM->SetMonsterId(info.id);
				BCM->SetDir(info.dir);
				_monsters[info.id] = BCM;
				continue;
			}

			// AF
			if (info.id > 20300 && info.id <= 20399)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				AmateurFencer* AF = SpawnObject<AmateurFencer>(info.spawnPos, LAYER_MONSTER);
				AF->SetMonsterId(info.id);
				AF->SetSpawnDir(info.dir);
				AF->SetSpawnPos(info.spawnPos);
				AF->SetMoveDistance(info.movingDistance);
				AF->SetMovementLimit(info.movementLimit);
				AF->SetPlayer(_player);
				_monsters[info.id] = AF;
				continue;
			}
		}
	}

	// Item
	{
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		ItemStage* itemStage = GET_SINGLE(ResourceManager)->GetItemStage(L"Stage2_Item");
		const std::vector<ItemStageInfo>& infos = itemStage->GetItemStageInfos();

		for (const ItemStageInfo& info : infos)
		{
			ItemActor* item = SpawnObject<ItemActor>({ info.spawnPos }, LAYER_ITEM, info.id, itemData->GetItems());
		}
	}

	// Structure
	SetStructureStageN(2);

	// LoadData 적용
	if (GET_SINGLE(SceneManager)->GetIsContinue())
	{
		_player->SetPos(_loadData.playerPos);
		_player->SetHp(_loadData.playerHp);
		_player->SetSkillPoint(_loadData.skillPoint);
		_player->SetAcquireItems(_loadData.playerItems);
	}

	Super::Init();
}

void GameScene::SetStage3()
{
	// 이전 스테이지 객체 삭제 (Player, UI 제외)
	{
		for (const std::vector<Actor*>& actors : _actors)
		{
			if (actors == _actors[LAYER_PLAYER])
				break;

			for (Actor* actor : actors)
			{
				toRemove.push_back(actor);
			}
		}
	}

	for (Actor* actor : toRemove)
		RemoveActor(actor);


	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage3");

		const Vec2Int size = sprite->GetSize();
		SpriteActor* map = SpawnObject<SpriteActor>(Vec2(size.x / 2, size.y / 2), LAYER_BACKGROUND);
		map->SetSprite(sprite);

		GET_SINGLE(ValueManager)->SetMapSize(size);
	}

	// Tilemap
	{
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Stage3");

		TilemapActor* actor = SpawnObject<TilemapActor>(-2, { 0, 0 }, LAYER_TILEMAP);
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
	}

	// Player
	{
		// Player가 없다면 생성
		if (!_player)
		{
			MyPlayer* player = SpawnObject<MyPlayer>({ 400, 200 }, LAYER_PLAYER);
			_player = player;
		}

		_player->SetPos({ 400, 200 });
		_player->SetCurStageNum(_curStageNum);
	}

	// Monster
	{
		Stage* stage = GET_SINGLE(ResourceManager)->GetStage(L"Stage3_FieldMonster");
		const std::vector<StageInfo>& infos = stage->GetInfos();

		for (const StageInfo& info : infos)
		{
			// TOW
			if (info.id > 20100 && info.id <= 20199)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				TiredOfficeWorker* TOW = SpawnObject<TiredOfficeWorker>(info.spawnPos, LAYER_MONSTER);
				TOW->SetMonsterId(info.id);
				TOW->SetSpawnDir(info.dir);
				TOW->SetSpawnPos(info.spawnPos);
				TOW->SetMoveDistance(info.movingDistance);
				TOW->SetMovementLimit(info.movementLimit);
				_monsters[info.id] = TOW;
				continue;
			}

			// BCM
			if (info.id > 20200 && info.id <= 20299)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				BrokenCopyMachine* BCM = SpawnObject<BrokenCopyMachine>(info.spawnPos, LAYER_MONSTER);
				BCM->SetMonsterId(info.id);
				BCM->SetDir(info.dir);
				_monsters[info.id] = BCM;
				continue;
			}

			// AF
			if (info.id > 20300 && info.id <= 20399)
			{
				if (std::find(_deadMonsterIds.begin(), _deadMonsterIds.end(), info.id) != _deadMonsterIds.end())
					continue;

				AmateurFencer* AF = SpawnObject<AmateurFencer>(info.spawnPos, LAYER_MONSTER);
				AF->SetMonsterId(info.id);
				AF->SetSpawnDir(info.dir);
				AF->SetSpawnPos(info.spawnPos);
				AF->SetMoveDistance(info.movingDistance);
				AF->SetMovementLimit(info.movementLimit);
				AF->SetPlayer(_player);
				_monsters[info.id] = AF;
				continue;
			}
		}
	}

	// Item
	{
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		ItemStage* itemStage = GET_SINGLE(ResourceManager)->GetItemStage(L"Stage3_Item");
		const std::vector<ItemStageInfo>& infos = itemStage->GetItemStageInfos();

		for (const ItemStageInfo& info : infos)
		{
			ItemActor* item = SpawnObject<ItemActor>({ info.spawnPos }, LAYER_ITEM, info.id, itemData->GetItems());
		}
	}

	// Structure
	SetStructureStageN(3);

	// LoadData 적용
	if (GET_SINGLE(SceneManager)->GetIsContinue())
	{
		_player->SetPos(_loadData.playerPos);
		_player->SetHp(_loadData.playerHp);
		_player->SetSkillPoint(_loadData.skillPoint);
		_player->SetAcquireItems(_loadData.playerItems);
	}

	Super::Init();
}

void GameScene::SetFinalBossStage()
{
	// 이전 스테이지 객체 삭제 (Player, UI 제외)
	{
		for (const std::vector<Actor*>& actors : _actors)
		{
			if (actors == _actors[LAYER_PLAYER])
				break;

			for (Actor* actor : actors)
			{
				toRemove.push_back(actor);
			}
		}
	}

	for (Actor* actor : toRemove)
		RemoveActor(actor);

	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"FinalBossStage");

		const Vec2Int size = sprite->GetSize();
		SpriteActor* map = SpawnObject<SpriteActor>(Vec2(size.x / 2, size.y / 2), LAYER_BACKGROUND);
		map->SetSprite(sprite);

		GET_SINGLE(ValueManager)->SetMapSize(size);
	}

	// Tilemap
	{
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"FinalBossStage");

		TilemapActor* actor = SpawnObject<TilemapActor>(-2, { 0, 0 }, LAYER_TILEMAP);
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
	}

	// Player
	{
		// Player가 없다면 생성
		/*if (!_player)
		{
			MyPlayer* player = SpawnObject<MyPlayer>({ 200, 520 }, LAYER_PLAYER);
			_player = player;
		}

		_player->SetPos({ 200, 520 });
		_player->SetCurStageNum(_curStageNum);*/
	}

	// FinalBoss
	{
		FinalBoss* finalBoss = SpawnObject<FinalBoss>({ 1000, 520 }, LAYER_MONSTER);
		_finalBoss = finalBoss;
		_finalBoss->SetPlayer(_player);
		_finalBoss->SetSpawnDir(DIR_RIGHT);
		_finalBoss->SetMovementLimit({ 50, 1200 });	// 수정 필요

		BossStagePanel* panel = new BossStagePanel();
		panel->SetFinalBoss(_finalBoss);
		AddPanel(panel);

		_finalBoss->SetHealthObserver([panel](int health) {  if (panel) panel->UpdateHealthPoint(health); });
	}

	Super::Init();
}

void GameScene::SetStructureStageN(int32 stageNum)
{
	StructureStage* structureStage = nullptr;

	switch (stageNum)
	{
	case 1:	structureStage = GET_SINGLE(ResourceManager)->GetStructureStage(L"Stage1_Structure"); break;
	case 2: structureStage = GET_SINGLE(ResourceManager)->GetStructureStage(L"Stage2_Structure"); break;
	case 3: structureStage = GET_SINGLE(ResourceManager)->GetStructureStage(L"Stage3_Structure"); break;
	}

	const std::vector<StructureStageInfo>& infos = structureStage->GetStructureStageInfos();

	for (const StructureStageInfo& info : infos)
	{
		if (info.name == L"LockedDoor")
		{
			LockedDoorAndKey* lockedDoorAndKey = SpawnObject<LockedDoorAndKey>({ info.spawnPos }, LAYER_STRUCTURE);
			lockedDoorAndKey->SetItemPos({ info.keyPos });
		}
		else if (info.name == L"BreakingWall")
		{
			BreakingWall* breakingWall = SpawnObject<BreakingWall>({ info.spawnPos }, LAYER_STRUCTURE);

			// 타입 0(Normal), 1(Short), 2(Long)
			BreakingWallType type;
			switch (info.wallType)
			{
			case 0: type = BreakingWallType::Normal; break;
			case 1: type = BreakingWallType::Short; break;
			case 2: type = BreakingWallType::Long; break;
			}
			breakingWall->SetWallType(type);
			breakingWall->SetPlayer(_player);
		}
		else if (info.name == L"ZipLine")
		{
			ZipLine* zipLine = SpawnObject<ZipLine>({ info.spawnPos }, LAYER_STRUCTURE);

			// 시작 - 끝 위치
			zipLine->SetBeginPos({ info.zipLineStartPos });
			zipLine->SetEndPos({ info.zipLineEndPos });

			// 짚라인 타입
			if (info.zipLineType == 0)
				zipLine->SetZipLineType(ZipLineType::ZipLine);
			else
			{
				zipLine->SetZipLineType(ZipLineType::ZipLineWithButton);

				ZipLineButtonAndDisplay* zipLineButtonAndDisplay = SpawnObject<ZipLineButtonAndDisplay>({ info.zipLineButtonPos }, LAYER_STRUCTURE);
				zipLineButtonAndDisplay->SetOwner(zipLine);
				zipLineButtonAndDisplay->SetDisplayPos({ info.zipLineDisplayPos });

				zipLine->SetZipLineButtonAndDisplay(zipLineButtonAndDisplay);
			}

			// 짚라인 렌더 타입
			if (info.zipLineRenderType == 0)
				zipLine->SetZipLineRenderType(ZipLineRenderType::None);
			else
				zipLine->SetZipLineRenderType(ZipLineRenderType::Line);

			zipLine->SetPlayer(_player);
		}
		else if (info.name == L"DestructibleObject")
		{
			DestructibleObject* destructibleObject = SpawnObject<DestructibleObject>({ info.spawnPos }, LAYER_STRUCTURE);
			destructibleObject->SetPlayer(_player);
		}
		else if (info.name == L"Window")
		{
			Window* window = SpawnObject<Window>({ info.spawnPos }, LAYER_STRUCTURE);
			window->SetFlickeringCycle(info.windowFlickeringCycle);
			window->SetFlickeringDuration(info.windowFlickeringDuration);
		}
		else if (info.name == L"FootHoldAndZipLineButton")
		{
			float zipLineXPos = (info.zipLineStartPos.x + info.zipLineEndPos.x) / 2;
			float zipLineYPos = (info.zipLineStartPos.y + info.zipLineEndPos.y) / 2;

			FootHoldAndZipLineButton* button = SpawnObject<FootHoldAndZipLineButton>({ info.zipLineButtonPos }, LAYER_STRUCTURE);
			button->SetZipLinePos({ zipLineXPos, zipLineYPos });
			button->SetZipLineBegin({ info.zipLineStartPos });
			button->SetZipLineEnd({ info.zipLineEndPos });

			FootHold* footHold = SpawnObject<FootHold>({ info.spawnPos }, LAYER_STRUCTURE);
			footHold->SetFootHoldAndZipLineButton(button);
		}
	}
}

void GameScene::SaveCurData()
{
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";
	std::ofstream file(path);

	if (!file.is_open())
	{
		std::cerr << "파일을 열 수 없습니다...";
		return;
	}

	// 현재 스테이지 번호
	file << _curStageNum << ",";

	// 플레이어 위치
	file << _player->GetPos().x << "," << _player->GetPos().y << ",";

	// 플레이어 체력
	file << _player->GetHp() << ",";

	// 스킬 포인트
	file << _player->GetSkillPoint() << ",";

	// 몬스터 ID와 체력
	for (const auto& [id, monster] : _monsters)
	{
		if (monster)
		{
			file << id << "," << monster->GetHp() << ",";
		}
	}
	for (int32 deadId : _deadMonsterIds)	// 죽은 몬스터 기록
	{
		file << deadId << ",0,";
	}

	// 아이템 정보 - 없으면 0 저장
	if (_player->GetAquireItems().empty())
	{
		file << 0 << ",";
	}
	else
	{
		for (const auto& [itemID, itemCount] : _player->GetAquireItems())
		{
			file << itemID << "," << itemCount << ",";
		}
	}

	file << "\n";
	file.close();
}

void GameScene::LoadGameData()
{
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";

	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "파일을 열 수 없습니다: " << path << std::endl;
		return;
	}

	std::string line;
	if (!std::getline(file, line))
	{
		std::cerr << "파일이 비어 있거나 데이터를 읽을 수 없습니다." << std::endl;
		return;
	}

	std::stringstream ss(line);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(ss, token, ','))
		tokens.push_back(token);

	size_t index = 0;

	// 1. 현재 스테이지 번호
	_curStageNum = std::stoi(tokens[index++]);

	// 2. 플레이어 위치
	float x = std::stof(tokens[index++]);
	float y = std::stof(tokens[index++]);
	_loadData.playerPos = { x, y };

	// 3. 플레이어 체력
	_loadData.playerHp = std::stoi(tokens[index++]);

	// 4. 스킬 포인트
	_loadData.skillPoint = std::stoi(tokens[index++]);

	// 5. 몬스터 정보 복원
	_deadMonsterIds.clear();
	_monsters.clear();  // 기존 몬스터 클리어 (혹시 모를 중복 방지)

	while (index + 1 < tokens.size())
	{
		int32 id = std::stoi(tokens[index]);

		// 아이템 ID 범위면 루프 종료
		if (id >= 300000)
			break;

		index++;
		int32 hp = std::stoi(tokens[index++]);

		if (hp <= 0)
		{
			_deadMonsterIds.push_back(id);
		}
		else
		{
			// 살아 있는 몬스터는 아직 Spawn되지 않았기 때문에
			// 일단 nullptr로 등록하고 이후 Stage 로딩 시 hp를 찾아 세팅
			_monsters[id] = nullptr;
		}
	}

	// 6. 아이템 정보
	_loadData.playerItems.clear();

	if (index < tokens.size() && std::stoi(tokens[index]) == 0)
	{
		index++; // 0 스킵
	}
	else
	{
		while (index + 1 < tokens.size())
		{
			int32 itemID = std::stoi(tokens[index++]);
			int32 itemCount = std::stoi(tokens[index++]);
			_loadData.playerItems[itemID] = itemCount;
		}
	}

	file.close();
}

void GameScene::SetSceneState()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		if (_sceneState == SceneState::Play)
		{
			_sceneState = SceneState::Menu;
		}
		else if (_sceneState == SceneState::Menu)
		{
			_sceneState = SceneState::Play;
		}
		else if (_sceneState == SceneState::Inventory)
		{
			_inventory->SetInventoryState(InventoryState::Hidden);
			_sceneState = SceneState::Play;
		}
	}
	
	if (_sceneState != SceneState::Play)
		return;

	// Player 이동 치트
	if (GET_SINGLE(InputManager)->GetButton(KeyType::LeftAlt))
	{
		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
		{
			Vec2 mousePosInWorld = GET_SINGLE(ValueManager)->GetMousePosInWorld();

			Vec2 pos = mousePosInWorld;
	
			_actors[LAYER_PLAYER][0]->SetPos(pos);
		}
	}
}

void GameScene::BackGroundRender(HDC hdc)
{
	BLENDFUNCTION bf;
	bf.AlphaFormat = 0; // 비트맵 종류로 일반 비트맵의 경우 0, 32비트 비트맵의 경우 AC_SRC_ALPHA
	bf.BlendFlags = 0; // 무조건 0이어야 한다
	bf.BlendOp = AC_SRC_OVER; // 무조건 AC_SRC_OVER이어야 하고 원본과 대상 이미지를 합친다는 의미
	bf.SourceConstantAlpha = 170; // 투명도(투명 0 - 불투명 255)

	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"MenuBackground");
		::AlphaBlend(hdc,
			0,
			0,
			(texture->GetSize().x) * winSizeAdjustmemt.x,
			(texture->GetSize().y) * winSizeAdjustmemt.y,
			texture->GetDC(),
			0,
			0,
			texture->GetSize().x,
			texture->GetSize().y,
			bf);
	}
}

void GameScene::ItemPictureRender(HDC hdc, int32 id)
{
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	static Texture* texture = nullptr;

	switch (id)
	{
	case 310100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Key");
		break;
	case 310200:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Multipletap");
		break;
	case 320100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Gem");
		break;
	case 320001:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Nametag");
		break;
	case 320002:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Sword");
		break;
	case 320003:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal1gold");
		break;
	case 320004:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal2gold");
		break;
	case 320005:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo1");
		break;
	case 320006:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Medal3silver");
		break;
	case 320007:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo2");
		break;
	case 320008:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo3");
		break;
	case 320009:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Box");
		break;
	case 320010:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Photo4");
		break;
	case 320011:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"map_Poster");
		break;
	}

	if (!texture)
		return;
	::TransparentBlt(hdc,
		(DefaultWinSizeX / 2 - 50) * winSizeAdjustment.x,
		(DefaultWinSizeY / 2 - 80) * winSizeAdjustment.y,
		100 * winSizeAdjustment.x,
		100 * winSizeAdjustment.y,
		texture->GetDC(),
		0,
		0,
		30,	// Sprite 변경시 수정 필요
		texture->GetSize().y,
		texture->GetTransparent());
}

void GameScene::ItemNameRender(HDC hdc, std::wstring name)
{
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// 출력할 위치
	RECT rect = { (DefaultWinSizeX / 2 - 30) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 120) * winSizeAdjustmemt.y, (DefaultWinSizeX / 2 + 30) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 140) * winSizeAdjustmemt.y };

	// 폰트 생성
	HFONT hfont = Utils::MakeFont(20.f * winSizeAdjustmemt.y, L"DungGeunMo");

	// 폰트 선택
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// 텍스트 색깔 설정
	::SetTextColor(hdc, RGB(0, 0, 0));

	// 텍스트 배경 투명화
	::SetBkMode(hdc, TRANSPARENT);

	Utils::DrawString(hdc, name, rect);

	::SetTextColor(hdc, RGB(0, 0, 0));
	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void GameScene::ItemExplainRender(HDC hdc, std::wstring explain)
{
	// 보정 변수 가져오기
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// 출력할 위치
	RECT rect = { (DefaultWinSizeX / 2 - 170) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 150) * winSizeAdjustmemt.y, (DefaultWinSizeX / 2 + 300) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 200) * winSizeAdjustmemt.y };

	// 폰트 생성
	HFONT hfont = Utils::MakeFont(17.f * winSizeAdjustmemt.y, L"DungGeunMo");

	// 폰트 선택
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// 텍스트 색깔 설정
	::SetTextColor(hdc, RGB(0, 0, 0));

	// 텍스트 배경 투명화
	::SetBkMode(hdc, TRANSPARENT);

	Utils::DrawString(hdc, explain, rect);

	::SetTextColor(hdc, RGB(0, 0, 0));
	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void GameScene::OnClickGoTitleButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::TitleScene);
}

void GameScene::OnClickMenuButton()
{
	// 아이템 정보 넣기
	_inventory->SaveAcquireItems();

	// 인벤토리 들어가기
	_sceneState = SceneState::Inventory;
	_inventory->SetInventoryState(InventoryState::Show);
}

void GameScene::OnClickSettingButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::SettingScene);
}
