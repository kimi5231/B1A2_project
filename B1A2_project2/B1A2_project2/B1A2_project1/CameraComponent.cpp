#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
#include "ValueManager.h"

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
	if (!_owner)
		return;

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();
	Vec2Int mapSize = GET_SINGLE(ValueManager)->GetMapSize();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	Vec2 pos = _owner->GetPos();
	pos.x *= winSizeAdjustment.x;
	pos.y *= winSizeAdjustment.y;

	pos.x = std::clamp(pos.x, (float)winSize.x / 2, (mapSize.x * winSizeAdjustment.x) - (float)winSize.x / 2);	// const는 값을 변경하지 않겠다는 약속이지, 타입 변환을 막지 않음.
	pos.y = std::clamp(pos.y, (float)winSize.y / 2, (mapSize.y * winSizeAdjustment.y) - (float)winSize.y / 2);
	
	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}