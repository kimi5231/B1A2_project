#include "pch.h"
#include "StaticUI.h"
#include "ValueManager.h"

StaticUI::StaticUI()
{
}

StaticUI::~StaticUI()
{
}

void StaticUI::BeginPlay()
{
	Super::BeginPlay();
}

void StaticUI::Tick()
{
	Super::Tick();
}

void StaticUI::Render(HDC hdc)
{
	Super::Render(hdc);

	// ȭ�� �ػ󵵿� ���� ��ġ ����
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();
	_pos.x *= (float(winSize.x) / float(DefaultWinSizeX));
	_pos.y *= (float(winSize.y) / float(DefaultWinSizeY));

	Utils::DrawRect(hdc, _pos, _size);
}