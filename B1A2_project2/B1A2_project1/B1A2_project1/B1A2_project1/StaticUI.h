#pragma once
#include "UI.h"

// ������ UI�� ǥ���ϱ� ���� Ŭ����.
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