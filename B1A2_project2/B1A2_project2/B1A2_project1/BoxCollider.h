#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
	using Super = Collider;

public:
	BoxCollider();
	virtual ~BoxCollider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	Vec2 GetSize() { return _size; }
	void SetSize(Vec2 size) { _size = size; }
	
	Vec2 GetPos() { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

	RECT GetRect();

	void SetManual(bool isManual) { _isManual = isManual; }

private:
	Vec2 _size{};

	bool _isManual = false;		// 발판 전용 - Collider 2개 생성하는데, 1개만 위치 수정 필요해서 사용
};

