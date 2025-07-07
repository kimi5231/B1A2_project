#include "pch.h"
#include "BossStagePanel.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include "StaticUI.h"
#include "FinalBoss.h"

BossStagePanel::BossStagePanel()
{
}

BossStagePanel::~BossStagePanel()
{
}

void BossStagePanel::BeginPlay()
{
	Super::BeginPlay();

	// HP
	{
		// Bar
		{
			Texture* texutre = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBoss_HpBar");

			StaticUI* HpBar = new StaticUI();
			HpBar->SetPos({ 430, 10 });
			HpBar->SetSize({ 549, 40 });
			AddChild(HpBar);
		}

		// HP point
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBoss_HpPoint");

			StaticUI* HpPoint = new StaticUI();
			HpPoint->SetPos({ 474, 13 });
			HpPoint->SetSize({ 500, 28 });
			AddChild(HpPoint);
		}
	}
}

void BossStagePanel::Tick()
{
	Super::Tick();
}

void BossStagePanel::Render(HDC hdc)
{
	Vec2 winSizeAdjustmemt = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	// HP Bar
	{
		Texture* hpBar = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBoss_HpBar");

		::TransparentBlt(hdc,
			430 * winSizeAdjustmemt.x,
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

	// HP Point
	{
		Texture* hpPoint = GET_SINGLE(ResourceManager)->GetTexture(L"FinalBoss_HpPoint");

		float hpRatio = (_hp / 2000.0f) * 500;

		::TransparentBlt(hdc,
			474 * winSizeAdjustmemt.x,
			16 * winSizeAdjustmemt.y,
			hpRatio * winSizeAdjustmemt.x,     // 계산된 hpRatio 사용
			hpPoint->GetSize().y * winSizeAdjustmemt.y,
			hpPoint->GetDC(),
			0,
			0,
			hpPoint->GetSize().x,
			hpPoint->GetSize().y,
			hpPoint->GetTransparent());
	}
}

void BossStagePanel::UpdateHealthPoint(int32 health)
{
	SetHealthPoint(health);
}