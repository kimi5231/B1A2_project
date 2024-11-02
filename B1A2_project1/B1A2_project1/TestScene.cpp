#include "pch.h"
#include "TestScene.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Texture.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");
}

void TestScene::Update()
{
	//Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
}

void TestScene::Render(HDC hdc)
{
	//Super::Render(hdc);

	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"Stage01");

	::BitBlt(hdc,
		0, 0,	// �����ϴ� ��ġ (0, 0)
		GWinSizeX, GWinSizeY,
		tex->GetDC(),
		0, 0,	// ���� �ؽ�ó�� ��ġ ���� ������
		SRCCOPY);
}
