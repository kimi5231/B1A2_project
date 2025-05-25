#include "pch.h"
#include "Button.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "ValueManager.h"
#include "Flipbook.h"
#include "Texture.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::BeginPlay()
{
	Super::BeginPlay();

	SetButtonState(BS_Default);
}

void Button::Tick()
{
	Super::Tick();

	if (IsMouseInRect())
	{
		SetButtonState(BS_Hovered);

		if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
		{
			if(_onClick)
				_onClick();
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}

	if (!_currentFlipbook)
		return;

	const FlipbookInfo& info = _currentFlipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	int32 frameCount = info.end - info.start + 1;
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void Button::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	if (!_currentFlipbook)
	{
		Utils::DrawRect(hdc, 
			{ _pos.x * ((float)winSize.x / (float)DefaultWinSizeX),
			_pos.y * ((float)winSize.y / (float)DefaultWinSizeY) },
			{ (int32)(_size.x * ((float)winSize.x / (float)DefaultWinSizeX)),
			(int32)(_size.y * ((float)winSize.y / (float)DefaultWinSizeY)) });
	}
	else
	{
		const FlipbookInfo& info = _currentFlipbook->GetInfo();

		::TransparentBlt(hdc,
			((int32)_pos.x - info.size.x / 2) * ((float)winSize.x / (float)DefaultWinSizeX),
			((int32)_pos.y - info.size.y / 2) * ((float)winSize.y / (float)DefaultWinSizeY),
			info.size.x * ((float)winSize.x / (float)DefaultWinSizeX),
			info.size.y * ((float)winSize.y / (float)DefaultWinSizeY),
			info.texture->GetDC(),
			(info.start + _idx) * info.size.x,
			info.line * info.size.y,
			info.size.x,
			info.size.y,
			info.texture->GetTransparent());
	}
}

RECT Button::GetRect()
{
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	RECT rect = {
		(_pos.x - _size.x)* ((float)winSize.x / (float)DefaultWinSizeX),
		(_pos.y - _size.y)* ((float)winSize.x / (float)DefaultWinSizeX),
		(_pos.x + _size.x)* ((float)winSize.x / (float)DefaultWinSizeX),
		(_pos.y + _size.y)* ((float)winSize.x / (float)DefaultWinSizeX)
	};

	return rect;
}

bool Button::IsMouseInRect()
{
	RECT rect = GetRect();
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	return ::PtInRect(&rect, mousePos);
}

void Button::SetButtonState(ButtonState state)
{
	if (_state == state)
		return;

	_state = state;

	SetCurrentFlipbook(state);
	Reset();
}

void Button::SetFlipbook(Flipbook* flipbook, ButtonState state)
{
	if (!flipbook)
		return;

	_flipbooks[state] = flipbook;

	Reset();
}

void Button::Reset()
{
	_idx = 0;
	_sumTime = 0.f;
}