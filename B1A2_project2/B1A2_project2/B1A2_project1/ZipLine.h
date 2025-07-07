#pragma once
#include "Structure.h"

class ZipLineButtonAndDisplay;
class BoxCollider;
class Player;

class ZipLine : public Structure
{
	using Super = Structure;
public:
	ZipLine();
	virtual ~ZipLine() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void LineRender(HDC hdc);
	void GripRender(HDC hdc);

protected:
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetZipLineType(ZipLineType type) { _zipLineType = type; }
	ZipLineType GetZipLineType() { return _zipLineType; }
	void SetZipLineRenderType(ZipLineRenderType type) { _renderType = type; }
	ZipLineRenderType GetZipLineRenderType() { return _renderType; }

	ObjectState GetZipLineState() { return _state; }

	void SetZipLineButtonAndDisplay(ZipLineButtonAndDisplay* object) { _zipLineButtonAndDisplay = object; }
	ZipLineButtonAndDisplay* GetZipLineButtonAndDisplay() { return _zipLineButtonAndDisplay; }

	Vec2 GetPos() { return _pos; }

	void SetBeginPos(Vec2 pos) { _beginPos = pos; }
	Vec2 GetBeginPos() { return _beginPos; }
	void SetEndPos(Vec2 pos) { _endPos = pos; }
	Vec2 GetEndPos() { return _endPos; }
	void SetMidPos(Vec2 pos) { _midPos = pos; }
	Vec2 GetMidPos() { return _midPos; }

	BoxCollider* GetPlayerDetectCollider() { return _playerDetectCollider; }

	void SetPlayer(Player* player) { _player = player; }
	Player* GetPlayer() { return _player; }

private:
	Flipbook* _flipbookZipLine = nullptr;

	ZipLineType _zipLineType;
	ZipLineRenderType _renderType = ZipLineRenderType::None;

	ZipLineButtonAndDisplay* _zipLineButtonAndDisplay = nullptr;

	ObjectState _state = OFF;

	BoxCollider* _playerDetectCollider = nullptr;

	Player* _player = nullptr;

	Vec2 _beginPos;
	Vec2 _endPos;
	Vec2 _midPos = {};
};

class ZipLineButtonAndDisplay : public Structure
{
	using Super = Structure;
public:
	ZipLineButtonAndDisplay();
	virtual ~ZipLineButtonAndDisplay() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void UpdateAnimation();

public:
	virtual float GetSpeed() { return 0.f; }

private:
	virtual void OnComponentBeginOverlap(Collider* collider, Collider* other);
	virtual void OnComponentEndOverlap(Collider* collider, Collider* other);

public:
	void SetOwner(ZipLine* zipLine) { _owner = zipLine; }

	void SetDisplayPos(Vec2 pos) { _displayPos = pos; }

	ObjectState GetState() { return _info.state(); }

private:
	Flipbook* _flipbookButtonOff = nullptr;
	Flipbook* _flipbookButtonOn = nullptr;
	Flipbook* _flipbookDisplayOff = nullptr;
	Flipbook* _flipbookDisplayOn = nullptr;

private:
	ZipLine* _owner = nullptr;

	// Display
	Vec2 _displayPos;

	bool _isCollide = false;	// Player와 충돌 중인지 확인
};
