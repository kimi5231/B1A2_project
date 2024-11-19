#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{
}

void CameraComponent::TickComponent()
{
	if (_owner == nullptr)
		return;

	Vec2 pos = _owner->GetPos();

	// TEMP
	// *�� ���ҽ� ���� �Ǹ�, �� ũ�� ������ ���� 
	// ���) �� ũ�⿡ ���� ������ �ٸ��� �־���� �ϴµ� if������ �ٲ�� �ұ�? 
	pos.x = std::clamp(pos.x, (float)GWinSizeX / 2, (float)mapX - (float)GWinSizeX / 2);	// const�� ���� �������� �ʰڴٴ� �������, Ÿ�� ��ȯ�� ���� ����.
	pos.y = std::clamp(pos.y, (float)GWinSizeY / 2, (float)mapY - (float)GWinSizeY / 2);

	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}
