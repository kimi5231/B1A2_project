#include "pch.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "ValueManager.h"

SpriteActor::SpriteActor()
{
}

SpriteActor::~SpriteActor()
{
}

void SpriteActor::BeginPlay()
{
	Super::BeginPlay();
}

void SpriteActor::Tick()
{
	Super::Tick();
}

void SpriteActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (!_sprite)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 cameraPosAdjustment = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	::TransparentBlt(hdc,
		((int32)_pos.x - size.x / 2) * winSizeAdjustment.x - cameraPosAdjustment.x,
		((int32)_pos.y - size.y / 2) * winSizeAdjustment.y - cameraPosAdjustment.y,
		size.x * winSizeAdjustment.x,
		size.y * winSizeAdjustment.y,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());
}