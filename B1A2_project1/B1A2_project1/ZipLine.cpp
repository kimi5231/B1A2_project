#include "pch.h"
#include "ZipLine.h"
#include "ResourceManager.h"

// 1. ¤���� - ��ư�� �ִ� ������ ��ư ���� ¤���θ� �ִ� ����
// 2. ¤���� ��ư - Player�� �浹 ó���Ǹ� ��ȣ�ۿ� �Է��� �޾� ¤���� Ȱ��ȭ
// 3. ¤���� ������ - ��ư Ȱ��ȭ�Ǹ� Render

ZipLine::ZipLine(ZipLineType zipLineType)
{
	_flipbookZipLine = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_ZipLine");

	if (zipLineType == ZipLineType::ZipLineWithButton)
	{
		_flipbookButton;
		_flipbookDisplay;
	}
}

ZipLine::~ZipLine()
{
}

void ZipLine::BeginPlay()
{
}

void ZipLine::Tick()
{
}

void ZipLine::Render(HDC hdc)
{
}

void ZipLine::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
}

void ZipLine::OnComponentEndOverlap(Collider* collider, Collider* other)
{
}
