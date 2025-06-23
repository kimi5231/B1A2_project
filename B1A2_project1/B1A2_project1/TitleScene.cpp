#include "pch.h"
#include "TitleScene.h"
#include "TitlePanel.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Button.h"
#include "Flipbook.h"
#include "InputManager.h"
#include "ValueManager.h"
#include "Texture.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	LoadSound();
	LoadUI();

	TitlePanel* panel = new TitlePanel();
	panel->SetOwner(this);
	AddPanel(panel);

	
	_sceneState = SceneState::Title;

	Super::Init();
}

void TitleScene::Update()
{
	SetSceneState();

	if (_sceneState == SceneState::Title)
	{
		Super::Update();
	}
	else if (_sceneState == SceneState::SelectStart)
	{
		if (_beginContinuePanel)
			_beginContinuePanel->Tick();
	}
}

void TitleScene::Render(HDC hdc)
{
	if (_sceneState == SceneState::Title)
	{
		Super::Render(hdc);
	}
	else if (_sceneState == SceneState::SelectStart)
	{
		Super::Render(hdc);

		// Background
		BackgroundRender(hdc);

		// Panel
		if (_beginContinuePanel)
			_beginContinuePanel->Render(hdc);
	}
}

void TitleScene::BackgroundRender(HDC hdc)
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

void TitleScene::LoadSound()
{
	// ����
	GET_SINGLE(ResourceManager)->LoadSound(L"Click", L"Sound\\Click.wav");
}

void TitleScene::LoadUI()
{
	// Menu
	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Begin", L"Sprite\\UI\\Begin.bmp", RGB(55, 255, 0));
		GET_SINGLE(ResourceManager)->LoadTexture(L"Continue", L"Sprite\\UI\\Continue.bmp", RGB(55, 255, 0));

		_beginContinuePanel = new Panel();
	}

	// Begin
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Begin");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BeginDefault");
			fb->SetInfo({ texture, L"FB_BeginDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_BeginHovered");
			fb->SetInfo({ texture, L"FB_BeginHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 540, 360 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitleScene::OnClickBegin);
		_beginContinuePanel->AddChild(button);
	}

	// Continue
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Continue");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ContinueDefault");
			fb->SetInfo({ texture, L"FB_ContinueDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ContinueHover");
			fb->SetInfo({ texture, L"FB_ContinueHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}


		button->SetPos({ 740, 360 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &TitleScene::OnClickContinue);
		_beginContinuePanel->AddChild(button);
	}

	// Menu Background
	GET_SINGLE(ResourceManager)->LoadTexture(L"MenuBackground", L"Sprite\\UI\\MenuBackground.bmp", RGB(0, 0, 0));
}

void TitleScene::OnClickBegin()
{
	// ����� ���̺� ���� ����
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";
	if (std::filesystem::exists(path))
		std::filesystem::remove(path);

	GET_SINGLE(SceneManager)->SetIsContinue(false);
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void TitleScene::OnClickContinue()
{
	std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path() / "B1A2_project1\\Resources\\Database\\SaveData.csv";
	if (!std::filesystem::exists(path))
		return;

	GET_SINGLE(SceneManager)->SetIsContinue(true);
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::GameScene);
}

void TitleScene::SetSceneState()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Esc))
	{
		if (_sceneState == SceneState::Title)
			return;
		
		if (_sceneState == SceneState::SelectStart)
		{
			_sceneState = SceneState::Title;
		}
	}
}