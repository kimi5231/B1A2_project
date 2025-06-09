#pragma once
#include "Structure.h"

class FootHold;

class FootHoldAndZipLineButton : public Structure
{
	using Super = Structure;
public:
	FootHoldAndZipLineButton();
	virtual ~FootHoldAndZipLineButton() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void TickOn() {};
	virtual void TickOn2();
	virtual void TickOff() {};
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	ObjectState GetState() { return _state; }

	void SetZipLinePos(Vec2 pos) { _zipLinePos = pos; }
	Vec2 GetZipLinePos() { return _zipLinePos; }
	void SetZipLineBegin(Vec2 pos) { _zipLineBegin = pos; }
	void SetZipLineEnd(Vec2 pos) { _zipLineEnd = pos; }
private:

	Flipbook* _flipbookFootHoldAndZipLineButtonOff = nullptr;
	Flipbook* _flipbookFootHoldAndZipLineButtonOn1 = nullptr;
	Flipbook* _flipbookFootHoldAndZipLineButtonOn2 = nullptr;

	Vec2 _zipLinePos = {};
	Vec2 _zipLineBegin = {};
	Vec2 _zipLineEnd = {};
};

/////////////////////////////////////////////////////////////////////////////////

class FootHold : public Structure
{
	using Super = Structure;
public:
	FootHold();
	virtual ~FootHold();
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void UpdateAnimation();
	
	virtual void TickOff();
	virtual void TickOn() {};
	void TickReady();
public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetFootHoldAndZipLineButton(FootHoldAndZipLineButton* button) { _footHoldAndZipLineButton = button; }
	FootHoldAndZipLineButton* GetFootHoldAndZipLineButton() { return _footHoldAndZipLineButton; }

private:
	Flipbook* _flipbookFootHold = nullptr;

	ObjectState _state = OFF;

	FootHoldAndZipLineButton* _footHoldAndZipLineButton = nullptr;
};

