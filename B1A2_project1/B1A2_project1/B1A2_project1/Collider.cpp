#include "pch.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Actor.h"

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType)
{
}

Collider::~Collider()
{
}

void Collider::BeginPlay()
{
}

void Collider::TickComponent()
{
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
	// 충돌 의지가 있는지 확인
	uint8 layer = other->GetCollisionLayer();	// 상대방이 어떤 충돌 타입인지 갖고 와서
	if (_collisionFlag & (1 << layer))		// 내 flag에서 상대방 것이 켜져 있는가 확인
		return true;

	return false;
}

void Collider::AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag |= (1 << layer);		// | : 비트 켜기
}

void Collider::RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer)
{
	_collisionFlag &= ~(1 << layer);	// &~ : 비트 끄기
}

bool Collider::CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2)
{
	RECT r1 = b1->GetRect();
	RECT r2 = b2->GetRect();
	RECT intersect = {};

	return ::IntersectRect(&intersect, &r1, &r2);
}

bool Collider::CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2)
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2)
{
	Vec2 p1 = s1->GetOwner()->GetPos();
	float r1 = s1->GetRadius();

	Vec2 p2 = s2->GetOwner()->GetPos();
	float r2 = s2->GetRadius();

	Vec2 dir = p1 - p2;
	float dist = dir.Length();

	return dist <= r1 + r2;
}
