#pragma once
#include "UI.h"

class Flipbook;

enum ButtonState
{
	BS_Default,
	BS_Hovered,
	BS_Pressed,
	BS_Clicked,

	BS_MaxCount
};

class Button : public UI
{
	using Super = UI;
public:
	Button();
	virtual ~Button() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

public:
	RECT GetRect();
	bool IsMouseInRect();

	void SetButtonState(ButtonState state);
	void SetFlipbook(Flipbook* flipbook, ButtonState state);
	void SetCurrentFlipbook(ButtonState state) { _currentFlipbook = _flipbooks[state]; }
	void Reset();

private:
	ButtonState _state;
	Flipbook* _flipbooks[BS_MaxCount]{};
	Flipbook* _currentFlipbook = nullptr;
	int32 _idx = 0;
	float _sumTime = 0.f;

public:
	// CallBack 함수 연결을 위한 템플릿 함수
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	std::function<void(void)> _onClick = nullptr;
};