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

	// HP
	{
		// Bar
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

	// Skill Point
	{
		// Bar
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SkillPointBar");

			StaticUI* skillPointBar = new StaticUI();
			skillPointBar->SetPos({ 1100, 640 });
			skillPointBar->SetSize({ 159, 40 });
			AddChild(skillPointBar);
		}

		// Skill Point
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SkillPoint");

			StaticUI* skillPoint = new StaticUI();
			skillPoint->SetPos({ 1100, 640 });
			skillPoint->SetSize({ 160, 40 });
			AddChild(skillPoint);
		}
	}
}

void InGamePanel::Tick()
{
	Super::Tick();
}

void InGamePanel::Render(HDC hdc)
{
	HpRender(hdc);

	SkillPointRender(hdc);
}

void InGamePanel::HpRender(HDC hdc)
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

void InGamePanel::SkillPointRender(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// SkillPoint Bar
	{
		Texture* SkillPointBar = GET_SINGLE(ResourceManager)->GetTexture(L"SkillPointBar");

		::TransparentBlt(hdc,
			1100 * winSizeAdjustmemt.x,
			640 * winSizeAdjustmemt.y,
			SkillPointBar->GetSize().x * winSizeAdjustmemt.x,
			SkillPointBar->GetSize().y * winSizeAdjustmemt.y,
			SkillPointBar->GetDC(),
			0,
			0,
			SkillPointBar->GetSize().x,
			SkillPointBar->GetSize().y,
			SkillPointBar->GetTransparent());
	}

	// SkillPoint
	{
		Texture* SkillPoint = GET_SINGLE(ResourceManager)->GetTexture(L"SkillPoint");

		::TransparentBlt(hdc,
			1100 * winSizeAdjustmemt.x,
			640 * winSizeAdjustmemt.y,
			_skillPoint * 32 * winSizeAdjustmemt.x,
			SkillPoint->GetSize().y * winSizeAdjustmemt.y,
			SkillPoint->GetDC(),
			0,
			0,
			_skillPoint * 32 * winSizeAdjustmemt.x,
			SkillPoint->GetSize().y,
			SkillPoint->GetTransparent());
	}
}

void InGamePanel::UpdateHealthPoint(int32 health)
{
	SetHealthPoint(health);
}

void InGamePanel::UpdateSkillPoint(int32 sp)
{
	SetSkillPoint(sp);
}