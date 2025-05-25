#include "pch.h"
#include "InGamePanel.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include "StaticUI.h"
#include "Player.h"

InGamePanel::InGamePanel()
{

}

InGamePanel::~InGamePanel()
{
}

void InGamePanel::BeginPlay()
{
	Super::BeginPlay();

	// InGame UI Texture Load
	GET_SINGLE(ResourceManager)->LoadTexture(L"HpBar", L"Sprite\\UI\\HpBar.bmp", RGB(55, 255, 0));
	GET_SINGLE(ResourceManager)->LoadTexture(L"HpPoint", L"Sprite\\UI\\HpPoint.bmp", RGB(55, 255, 0));

	// HP bar
	{
		Texture* texutre = GET_SINGLE(ResourceManager)->GetTexture(L"HpBar");

		StaticUI* HpBar = new StaticUI();
		HpBar->SetPos({ 15, 10 });
		HpBar->SetSize({ 119, 25 });
		AddChild(HpBar);
	}

	// HP point
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"HpPoint");

		StaticUI* HpPoint = new StaticUI();
		HpPoint->SetPos({ 27, 13 });
		HpPoint->SetSize({ 100, 25 });
		AddChild(HpPoint);
	}

}

void InGamePanel::Tick()
{
	Super::Tick();
}

void InGamePanel::Render(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// HP Point
	{
		Texture* hpPoint = GET_SINGLE(ResourceManager)->GetTexture(L"HpPoint");

		::TransparentBlt(hdc,
			48 * winSizeAdjustmemt.x,
			15 * winSizeAdjustmemt.y,
			_hp * winSizeAdjustmemt.x,		// hp에 따라 변경
			hpPoint->GetSize().y * winSizeAdjustmemt.y,	
			hpPoint->GetDC(),
			0,
			0,
			hpPoint->GetSize().x,
			hpPoint->GetSize().y,
			hpPoint->GetTransparent());
	}

	// HP Bar
	{
		Texture* hpBar = GET_SINGLE(ResourceManager)->GetTexture(L"HpBar");
		
		::TransparentBlt(hdc,
			15 * winSizeAdjustmemt.x,
			10 * winSizeAdjustmemt.y,
			hpBar->GetSize().x * winSizeAdjustmemt.x,	
			hpBar->GetSize().y * winSizeAdjustmemt.y,
			hpBar->GetDC(),
			0,
			0,
			hpBar->GetSize().x,
			hpBar->GetSize().y,
			hpBar->GetTransparent());
	}
}

void InGamePanel::UpdateHealthPoint(int32 health)
{
	_hp = health;
}

