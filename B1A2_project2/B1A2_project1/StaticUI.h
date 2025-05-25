#pragma once
#include "UI.h"

// 정적인 UI를 표현하기 위한 클래스.
class StaticUI : public UI
{
	using Super = UI;
public:
	StaticUI();
	virtual ~StaticUI() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
};