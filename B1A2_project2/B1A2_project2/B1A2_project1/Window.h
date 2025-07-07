#pragma once
#include "Structure.h"

class Window : public Structure
{
	using Super = Structure;
public:
	Window();
	virtual ~Window() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickOn();
	virtual void TickOff();
	virtual  void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }
	ObjectState GetState() { return _info.state(); }

	void SetFlickeringDuration(float duration) { _flickeringDuration = duration; }
	void SetFlickeringCycle(float cycle) { _flickeringCycle = cycle; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

private:
	Flipbook* _flipbookOn = nullptr;
	Flipbook* _flipbookOff = nullptr;

	float _flickeringDuration = 0.f;
	float _flickeringCycle = 0.f;
};

