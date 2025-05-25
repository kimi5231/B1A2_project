#include "pch.h"
#include "TitlePanel.h"
#include "FlipbookUI.h"
#include "Button.h"
#include "Texture.h"
#include "Flipbook.h"
#include "SceneManager.h"
#include "ResourceManager.h"

TitlePanel::TitlePanel()
{
}

TitlePanel::~TitlePanel()
{
}

void TitlePanel::BeginPlay()
{
	// TitleScene Texture Load
	GET_SINGLE(ResourceManager)->LoadTexture(L"Title", L"Sprite\\UI\\Title.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"GameStart", L"Sprite\\UI\\GameStart.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"GameEnd", L"Sprite\\UI\\GameEnd.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Setting", L"Sprite\\UI\\Setting.bmp", RGB(55, 255, 0));

	// Title 추가
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Title");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Title");
		fb->SetInfo({ texture, L"FB_Title", { 545, 339 }, 0, 3, 0, 0.5f, true });

		FlipbookUI* title = new FlipbookUI();
		title->SetPos({ 350, 250 });
		title->SetSize({ 545, 339 });
		title->SetFilpbook(fb);
		AddChild(title);
	}

	// 게임 시작 Button 추가
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GameStart");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GameStartDefault");
			fb->SetInfo({ texture, L"FB_GameStartDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GameStartHovered");
			fb->SetInfo({ texture, L"FB_GameStartHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 1100, 400 });
		button->SetSize({ 163, 60 });
		button->AddOnClickDelegate(this, &TitlePanel::OnClickStartButton);
		AddChild(button);
	}

	// 설정 Button 추가
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


		button->SetPos({ 1100, 500 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &TitlePanel::OnClickSettingButton);
		AddChild(button);
	}

	// 게임 종료 Button 추가
	{
		Button* button = new Button();

		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GameEnd");

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GameEndDefault");
			fb->SetInfo({ texture, L"FB_GameEndDefalt", {163, 60}, 0, 0, 0, 0.5f, false });
			button->SetFlipbook(fb, BS_Default);
		}

		{
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_GameEndHover");
			fb->SetInfo({ texture, L"FB_GameEndHovered", {163, 60}, 0, 3, 1, 0.5f, true });
			button->SetFlipbook(fb, BS_Hovered);
		}

		button->SetPos({ 1100, 600 });
		button->SetSize({ 163, 60 });

		button->AddOnClickDelegate(this, &TitlePanel::OnClickEndButton);
		AddChild(button);
	}

	Super::BeginPlay();
}

void TitlePanel::Tick()
{
	Super::Tick();
}

void TitlePanel::Render(HDC hdc)
{
	Super::Render(hdc);
}

// CallBack 함수
void TitlePanel::OnClickStartButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void TitlePanel::OnClickSettingButton()
{
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::SettingScene);
}

void TitlePanel::OnClickEndButton()
{
	// 추후 게임을 종료할 것인지 물어보는 메세지 창을 추가할 예정.
	// 일단은 바로 종료되게 설정.
	::PostQuitMessage(0);
}