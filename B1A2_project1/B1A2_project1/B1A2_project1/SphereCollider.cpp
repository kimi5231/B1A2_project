#include "pch.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "Actor.h"
#include "BoxCollider.h"
#include "ValueManager.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere)
{

}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::BeginPlay()
{
	Super::BeginPlay();


}

void SphereCollider::TickComponent()
{
	Super::TickComponent();


}

void SphereCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_showDebug == false)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

	Vec2 pos = GetOwner()->GetPos();
	pos.x -= (cameraPos.x - winSize.x / 2);
	pos.y -= (cameraPos.y - winSize.y / 2);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawCircle(hdc, pos, _radius);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionSphere2Box(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphere2Sphere(this, static_cast<SphereCollider*>(other));
	}

	return false;
}
