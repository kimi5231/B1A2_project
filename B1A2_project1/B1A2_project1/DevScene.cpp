#include "pch.h"
#include "DevScene.h"
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
#include "TiredOfficeWorker.h"
#include "BrokenCopyMachine.h"
#include "AmateurFencer.h"
#include "DialogueComponent.h"
#include "ZipLine.h"
#include "TimeManager.h"
#include "Stage.h"

DevScene::DevScene()
{
}

DevScene::~DevScene()
{
}

void DevScene::Init()
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
	LoadMenu();
	// LoadSound();

	// �������� ����
	SetStage(1);

	// Inventory
	{
		Inventory* inventory = new Inventory();
		_player->AddComponent(inventory);

		inventory->SetOwner(_player);

		// Update���� inventory�� ��� ������ �����ϱ� ����
		_inventory = inventory;
	}

	// InGame UI
	InGamePanel* panel = new InGamePanel();
	panel->SetPlayer(_player);
	AddPanel(panel);

	// player�� ü�� ���� �� UI ������Ʈ ���
	_player->SetHealthObserver([panel](int health) {  if (panel) panel->UpdateHealthPoint(health); });

	// ���� Scene ���� �ֱ� (���̺� ����Ʈ ���� ���� ����)
	_player->SetCurrentScene(this);

	// Announcemet
	{
		// Layer ���� ���� ����
		Actor* actor = SpawnObject<Actor>({ 500, 500 }, LAYER_PLAYER);

		DialogueComponent* dialogueComponent = new DialogueComponent();
		actor->AddComponent(dialogueComponent);
		actor->SetID(21);
	}

	// Item
	{
		Item* itemData = GET_SINGLE(ResourceManager)->GetItem(L"Item");
		// ����
		{
			ItemActor* item = new ItemActor(310100, itemData->GetItems());
			item->SetPos({ 500, 290 });		// ������ y ��ǥ : 370, 200
			item->SetLayer(LAYER_ITEM);

			AddActor(item);
		}
		// ����
		{
			ItemActor* item = new ItemActor(300100, itemData->GetItems());
			item->SetPos({ 400, 290 });
			item->SetLayer(LAYER_ITEM);
			
			// ���� ���� ����
			item->SetFKeyState(FKeyState::Hidden);

			AddActor(item);
		}
		
	}

	// Monster
	{
			//	// �߰� ������ ������, hp�� �߰��� ������Ʈ �ʿ�
			//	// ID�� Hp ��ü���� �������� �ɷ� ���� �ʿ�, ����� �����Ⱚ�� (CommonStat.id, hp ��)
			//	_monsterHpData[20101] = 100;
			//}
	
			//	_monsterHpData[20201] = 100;

		// AF
		{
			AmateurFencer* AF = SpawnObject<AmateurFencer>({ 1200, 300 }, LAYER_MONSTER);
			AF->SetSpawnDir(DIR_RIGHT);
			AF->SetSpawnPos({ 1200, 300 });
			//AF->SetMoveDistance();
			AF->SetMovementLimit({ 960, 2000 });

			// Player ����
			AF->_player = _player;

			_monsterHpData[20301] = 100;
		}
	}

	// ZipLine
	{
		ZipLine* zipLine = SpawnObject<ZipLine>({ 900, 200 }, LAYER_STRUCTURE);
		zipLine->SetZipLineType(ZipLineType::ZipLineWithButton);
		zipLine->SetBeginPos({800, 250});
		zipLine->SetEndPos({950, 170});

		// Button�� �ʿ� ���� ¤������ �Ʒ� �ڵ� �ۼ�X
		ZipLineButtonAndDisplay* zipLineButtonAndDisplay = SpawnObject<ZipLineButtonAndDisplay>({ 200, 300 }, LAYER_STRUCTURE);
		zipLineButtonAndDisplay->SetOwner(zipLine);
		zipLineButtonAndDisplay->SetDisplayPos({ 500, 200 });

		zipLine->SetZipLineButtonAndDisplay(zipLineButtonAndDisplay);
	}

	// Start Dialogue
	/*{
		std::vector<Actor*> actors;
		actors.push_back(GetActor(1));
		actors.push_back(GetActor(21));
		GET_SINGLE(DialogueManager)->StartDialogue(L"prologue1", actors);
	}*/

	Super::Init();
}

void DevScene::Update()
{
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
		static float sumTime = 0.0f;
		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

		sumTime += deltaTime;

		if (sumTime >= 2.5f)
		{
			_sceneState = SceneState::Play;
		}

	}
	else if (_sceneState == SceneState::Inventory)
	{
		if (_inventory->GetInventoryState() == InventoryState::Show)
			_inventory->TickComponent();
	}
}

void DevScene::Render(HDC hdc)
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
	
			// ����
			ItemPictureRender(hdc, id);
			// �̸�
			ItemNameRender(hdc, name);
			// ����
			ItemExplainRender(hdc, explain);
		}

	}
	else if (_sceneState == SceneState::Inventory)
	{
		if (_inventory->GetInventoryState() == InventoryState::Show)
			_inventory->Render(hdc);
	}
}

void DevScene::LoadStage()
{
	// Stage
	{
		// csv �߰��Ǹ� ���� ����
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage1_FieldMonster", L"DataBase\\Stage1_FieldMonster.csv");
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage2_FieldMonster", L"DataBase\\Stage2_FieldMonster.csv");
		GET_SINGLE(ResourceManager)->LoadStage(L"Stage3_FieldMonster", L"DataBase\\Stage3_FieldMonster.csv");
	}

	// Map
	{
		// Texture
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage1", L"Sprite\\Map\\Stage1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage2", L"Sprite\\Map\\Stage2.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage3", L"Sprite\\Map\\Stage3.bmp");

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
	}

	// Tilemap
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage1", L"Tilemap\\Stage1.txt");
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage2", L"Tilemap\\Stage2.txt");
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Stage3", L"Tilemap\\Stage3.txt");
	}
}

void DevScene::LoadPlayer()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerIdle", L"Sprite\\Player\\PlayerIdle.bmp", RGB(55, 255, 0));	
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerMove", L"Sprite\\Player\\PlayerMove.bmp", RGB(55, 255, 0));	
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerJump", L"Sprite\\Player\\PlayerJump.bmp", RGB(55, 255, 0));	
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDuckDown", L"Sprite\\Player\\PlayerDuckDown.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDuckDownMove", L"Sprite\\Player\\PlayerDuckDownMove.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHang", L"Sprite\\Player\\PlayerHang.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRelease", L"Sprite\\Player\\PlayerRelease.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerSlash", L"Sprite\\Player\\PlayerSlash.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHit", L"Sprite\\Player\\PlayerHit.bmp", RGB(55, 255, 0));

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
		fb1->SetInfo({ texture, L"FB_PlayerHangRight", {30, 85}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHangLeft");
		fb2->SetInfo({ texture, L"FB_PlayerHangLeft", {30, 85}, 0, 0, 1, 0.7f });
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
		fb1->SetInfo({ texture, L"FB_PlayerSlashRight", {75, 90}, 0, 6, 0, 1.0f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerSlashLeft");
		fb2->SetInfo({ texture, L"FB_PlayerSlashLeft", {75, 90}, 0, 6, 1, 1.0f });
	}

	// Hit
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHit");

		// Right
		Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHitRight");
		fb1->SetInfo({ texture, L"FB_PlayerHitRight", {41, 80}, 0, 0, 0, 0.7f });

		// Left
		Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_PlayerHithLeft");
		fb2->SetInfo({ texture, L"FB_PlayerHitLeft", {41, 80}, 0, 0, 1, 0.7f });
	}
}

void DevScene::LoadMonster()
{
	// TOW
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"TiredOfficeWorker", L"Sprite\\Monster\\TiredOfficeWorker.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TiredOfficeWorker");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_TiredOfficeWorker");
		fb->SetInfo({ texture, L"FB_TiredOfficeWorker", {31, 77}, 0, 0, 0, 0.7f });
	}

	// BCM
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"BrokenCopyMachine", L"Sprite\\Monster\\BrokenCopyMachine.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"BrokenCopyMachine");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BrokenCopyMachine");
		fb->SetInfo({ texture, L"FB_BrokenCopyMachine", {55, 55}, 0, 0, 0, 0.7f });
	}

	// AF
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"AmateurFencer", L"Sprite\\Monster\\AmateurFencer.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"AmateurFencer");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AmateurFencer");
		fb->SetInfo({ texture, L"FB_AmateurFencer", {31, 77}, 0, 0, 0, 0.7f });
	}
}

void DevScene::LoadProjectile()
{
	// Paper
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Paper", L"Sprite\\Projectile\\Paper.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Paper");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Paper");
		fb->SetInfo({ texture, L"FB_Paper", {10, 5}, 0, 0, 0, 0.7f });
	}
	
	// SlashWave
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"SlashWave", L"Sprite\\Projectile\\SlashWave.bmp", RGB(55, 255, 0));
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SlashWave");

		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_SlashWave");
		fb->SetInfo({ texture, L"FB_SlashWave", {20, 88}, 0, 0, 0, 0.7f });
	}
}

void DevScene::LoadStructure()
{
	// ZipLine
	{
		// ZipLine
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLine", L"Sprite\\Structure\\ZipLine.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLine");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLine");
			fb->SetInfo({ texture, L"FB_ZipLine", {4, 400}, 0, 0, 0, 0.7f });
		}
		
		// Grip
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineGrip", L"Sprite\\Structure\\ZipLineGrip.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineGrip");

			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineGrip");
			fb->SetInfo({ texture, L"FB_ZipLineGrip", {35, 22}, 0, 0, 0, 0.7f });
		}

		// Display
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineDisplay", L"Sprite\\Structure\\ZipLineDisplay.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineDisplay");

		//	Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineDisplayOff");
		//	fb1->SetInfo({ texture, L"FB_ZipLineDisplayOff", {110, 120}, 0, 0, 0, 0.7f });
		//	
		//	Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineDisplayOn");
		//	fb2->SetInfo({ texture, L"FB_ZipLineDisplayOn", {110, 120}, 0, 0, 1, 0.7f });
		}

		// Button
		{
			GET_SINGLE(ResourceManager)->LoadTexture(L"ZipLineButton", L"Sprite\\Structure\\ZipLineButton.bmp", RGB(55, 255, 0));
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ZipLineButton");

			Flipbook* fb1 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineButtonOff");
			fb1->SetInfo({ texture, L"FB_ZipLineButtonOff", {101, 116}, 0, 0, 0, 0.7f });

			Flipbook* fb2 = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ZipLineButtonOn");
			fb2->SetInfo({ texture, L"FB_ZipLineButtonOn", {101, 116}, 0, 0, 1, 0.7f });
		}
	}
}

void DevScene::LoadDialogue()
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

void DevScene::LoadItem()
{
	// Item info
	GET_SINGLE(ResourceManager)->LoadItem(L"Item", L"DataBase\\itemList.csv");

	// Texture
	// in Map
	GET_SINGLE(ResourceManager)->LoadTexture(L"F_key", L"Sprite\\Item\\F_key.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"1001_keyInMap", L"Sprite\\Item\\1001_keyInMap.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"1002_pencilInMap", L"Sprite\\Item\\1002_pencilInMap.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"1003_matchInMap", L"Sprite\\Item\\1003_matchInMap.bmp", RGB(55, 255, 0));
	// in Inventory
	GET_SINGLE(ResourceManager)->LoadTexture(L"1001_keyInInventory", L"Sprite\\Item\\1001_keyInInventory.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"1002_pencilInInventory", L"Sprite\\Item\\1002_pencilInInventory.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"1003_matchInInventory", L"Sprite\\Item\\1003_matchInInventory.bmp", RGB(55, 255, 0));

	// F button
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"F_key");
		GET_SINGLE(ResourceManager)->CreateSprite(L"F_key", texture, 0, 0, 30, 30);
	}
	// 1001_Key
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1001_keyInMap");

		// in Map
		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_keyInMap");
			fb->SetInfo({ texture, L"FB_keyInMap", {30, 30}, 0, 2, 0, 0.7f, true });
		}
	}
	// 1002_pencil
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInMap");

		// in Map
		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_pencilInMap");
			fb->SetInfo({ texture, L"FB_pencilInMap", {30, 30}, 0, 2, 0, 0.7f, true });
		}
	}
	// 1003_match
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"1003_matchInMap");

		// in Map
		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_matchInMap");
			fb->SetInfo({ texture, L"FB_matchInMap", {30, 30}, 0, 2, 0, 0.7f, true });
		}
	}
}

void DevScene::LoadInventory()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Inventory", L"Sprite\\Inventory\\Inventory.bmp");

	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Inventory");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Inventory", texture, 0, 0, 1280, 720);
}

void DevScene::LoadMenu()
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
		button->AddOnClickDelegate(this, &DevScene::OnClickGoTitleButton);
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

		button->AddOnClickDelegate(this, &DevScene::OnClickMenuButton);
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

		button->AddOnClickDelegate(this, &DevScene::OnClickSettingButton);
		_menuPanel->AddChild(button);
	}

	// Menu Background
	GET_SINGLE(ResourceManager)->LoadTexture(L"MenuBackground", L"Sprite\\UI\\MenuBackground.bmp", RGB(0, 0, 0));
}

void DevScene::LoadSound()
{
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\BGM.wav");
	{
		Sound* sound = GET_SINGLE(ResourceManager)->GetSound(L"BGM");
		sound->Play(true);
	}
}

void DevScene::SetStage(int32 stage)
{
	_curStageNum = stage;

	// ���� �������� ���� ����

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
	}
}

void DevScene::SetStage1()
{
	// ���� �������� ��ü ���� (Player, UI ����)
	{
		for (const std::vector<Actor*>& actors : _actors)
		{
			if (actors == _actors[LAYER_PLAYER])
				break;
			for (Actor* actor : actors)
				SAFE_DELETE(actor);
		}
	}

	// Map
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage1");
		
		const Vec2Int size = sprite->GetSize();
		SpriteActor* map = SpawnObject<SpriteActor>(Vec2(size.x / 2, size.y / 2), LAYER_BACKGROUND);
		map->SetSprite(sprite);

		GET_SINGLE(ValueManager)->SetMapSize(size);
	}

	// Tilemap
	{
		Tilemap* tm = GET_SINGLE(ResourceManager)->GetTilemap(L"Stage1");

		TilemapActor* actor = SpawnObject<TilemapActor>({ 0, 0 }, LAYER_TILEMAP);
		actor->SetShowDebug(false);
		actor->SetTilemap(tm);
	}
	
	// Player
	{
		// Player�� ���ٸ� ����
		if (!_player)
		{
			Player* player = SpawnObject<Player>({ 400, 200 }, LAYER_PLAYER);
			_player = player;
		}
		
		_player->SetPos({ 400, 200 });
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
				TiredOfficeWorker* TOW = SpawnObject<TiredOfficeWorker>(info.spawnPos, LAYER_MONSTER);
				TOW->SetSpawnDir(info.dir);
				TOW->SetSpawnPos(info.spawnPos);
				TOW->SetMoveDistance(info.movingDistance);
				TOW->SetMovementLimit(info.movementLimit);
				continue;
			}
			
			// BCM
			if (info.id > 20200 && info.id <= 20299)
			{
				BrokenCopyMachine* BCM = SpawnObject<BrokenCopyMachine>(info.spawnPos, LAYER_MONSTER);
				BCM->SetDir(info.dir);
				continue;
			}

			// AF
			if (info.id > 20300 && info.id <= 20399)
			{
				continue;
			}
		}
	}

	// Structure

	// Item
}

void DevScene::SaveCurData()
{
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";
	std::ofstream file(path);

	if (!file.is_open())
	{
		std::cerr << "������ �� �� �����ϴ�...";
		return;
	}

	// ���� �������� ��ȣ
	file << _curStageNum << ",";


	// �÷��̾� ü��
	file << _player->GetHp() << ",";

	// ��ų ����Ʈ
	file << _player->GetSkillPoint() << ",";

	// ���� ID�� ü��
	for (const auto& [monsterID, monsterHp] : _monsterHpData )
	{
		file << monsterID << "," << monsterHp << ",";
	}

	// ������ ���� - ������ 0 ����
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

void DevScene::LoadGameData()
{
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1/Resources/Database/SaveData.csv";

	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "������ �� �� �����ϴ�: " << path << std::endl;
		return;
	}

	std::string line;
	if (!std::getline(file, line))
	{
		std::cerr << "������ ��� �ְų� �����͸� ���� �� �����ϴ�." << std::endl;
		return;
	}

	// ',' �������� ������ ����
	std::stringstream ss(line);
	std::vector<std::string> tokens;
	std::string token;

	while (std::getline(ss, token, ','))
	{
		tokens.push_back(token);
	}

	size_t index = 0;

	// ���� �������� ��ȣ
	_curStageNum = std::stoi(tokens[index++]);

	// �÷��̾� ü��
	_player->SetHp(std::stoi(tokens[index++]));

	// ��ų ����Ʈ
	_player->SetSkillPoint(std::stoi(tokens[index++]));

	// ���� ID�� ü�� �б�
	_monsterHpData.clear();
	while (index < tokens.size() - 2) // �ּ��� ��ų����Ʈ�� ������ �� ���� ���ƾ� ��
	{
		int32 monsterID = std::stoi(tokens[index++]);
		int32 monsterHp = std::stoi(tokens[index++]);
		_monsterHpData[monsterID] = monsterHp;
	}

	// ������ ���� �б�
	if (std::stoi(tokens[index++]) == 0)
	{
		_player->ClearAcquireItems();
	}
	else
	{
		std::unordered_map<int32, int32> tempItems;
		while (index < tokens.size())
		{
			int32 itemID = std::stoi(tokens[index++]);
			int32 itemCount = std::stoi(tokens[index++]);
			tempItems[itemID] = itemCount;
		}
		_player->SetAcquireItems(tempItems);
	}

	file.close();

}

void DevScene::SetStage2()
{

}

void DevScene::SetStage3()
{

}

void DevScene::SetSceneState()
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

	// Player �̵� ġƮ
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

void DevScene::BackGroundRender(HDC hdc)
{
	BLENDFUNCTION bf;
	bf.AlphaFormat = 0; // ��Ʈ�� ������ �Ϲ� ��Ʈ���� ��� 0, 32��Ʈ ��Ʈ���� ��� AC_SRC_ALPHA
	bf.BlendFlags = 0; // ������ 0�̾�� �Ѵ�
	bf.BlendOp = AC_SRC_OVER; // ������ AC_SRC_OVER�̾�� �ϰ� ������ ��� �̹����� ��ģ�ٴ� �ǹ�
	bf.SourceConstantAlpha = 170; // ����(���� 0 - ������ 255)

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

void DevScene::ItemPictureRender(HDC hdc, int32 id)
{
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	static Texture* texture = nullptr;

	switch (id)
	{
	case 310100:
		texture = GET_SINGLE(ResourceManager)->GetTexture(L"1002_pencilInMap");
		break;
	}

	::TransparentBlt(hdc,
		(DefaultWinSizeX / 2 - 50) * winSizeAdjustment.x,
		(DefaultWinSizeY / 2 - 80) * winSizeAdjustment.y,
		100 * winSizeAdjustment.x,
		100 * winSizeAdjustment.y,
		texture->GetDC(),
		0,
		0,
		30,	// Sprite ����� ���� �ʿ�
		texture->GetSize().y,
		texture->GetTransparent());
}

void DevScene::ItemNameRender(HDC hdc, std::wstring name)
{
	// ���� ���� ��������
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// ����� ��ġ
	RECT rect = { (DefaultWinSizeX / 2 - 30) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 120) * winSizeAdjustmemt.y, (DefaultWinSizeX / 2 + 30) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 140) * winSizeAdjustmemt.y };

	// ��Ʈ ����
	HFONT hfont = Utils::MakeFont(20.f * winSizeAdjustmemt.y, L"DungGeunMo");

	// ��Ʈ ����
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// �ؽ�Ʈ ���� ����
	::SetTextColor(hdc, RGB(0, 0, 0));

	// �ؽ�Ʈ ��� ����ȭ
	::SetBkMode(hdc, TRANSPARENT);

	Utils::DrawString(hdc, name, rect);

	::SetTextColor(hdc, RGB(0, 0, 0));
	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void DevScene::ItemExplainRender(HDC hdc, std::wstring explain)
{
	// ���� ���� ��������
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// ����� ��ġ
	RECT rect = { (DefaultWinSizeX / 2 - 50) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 150) * winSizeAdjustmemt.y, (DefaultWinSizeX / 2 + 50) * winSizeAdjustmemt.x, (DefaultWinSizeY / 2 + 200) * winSizeAdjustmemt.y };

	// ��Ʈ ����
	HFONT hfont = Utils::MakeFont(20.f * winSizeAdjustmemt.y, L"DungGeunMo");

	// ��Ʈ ����
	HFONT oldFont = (HFONT)::SelectObject(hdc, hfont);

	// �ؽ�Ʈ ���� ����
	::SetTextColor(hdc, RGB(0, 0, 0));

	// �ؽ�Ʈ ��� ����ȭ
	::SetBkMode(hdc, TRANSPARENT);

	Utils::DrawString(hdc, explain, rect);

	::SetTextColor(hdc, RGB(0, 0, 0));
	::SelectObject(hdc, oldFont);
	::DeleteObject(hfont);
}

void DevScene::OnClickGoTitleButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::TitleScene);
}

void DevScene::OnClickMenuButton()
{
	// ������ ���� �ֱ�
	_inventory->SaveAcquireItems();

	// �κ��丮 ����
	_sceneState = SceneState::Inventory;
	_inventory->SetInventoryState(InventoryState::Show);
}

void DevScene::OnClickSettingButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::SettingScene);
}
