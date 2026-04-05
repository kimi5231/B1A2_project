#include "pch.h"
#include "GameObject.h"
#include "Global.h"
#include "Utils.h"

GameObject::GameObject()
{
	_objectPoolState = ObjectPoolState::Reusable;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

}

bool GameObject::CheckInclude(Vector targetPos, float range, float angle)
{
	// 거리 내에 있는지 확인
	Vector diff = targetPos - _pos;
	diff.z = 0; // 높이 차이 무시

	float disSquare = diff.LengthSquared();
	if (disSquare > range * range)
		return false;

	// 각도 내에 있는지 확인
	//
	Vector forward = GetForwardVector(_rotation.pitch, _rotation.yaw);
	Vector target = diff / sqrt(disSquare);

	float dot = forward.Dot(target);

	float cosHalf = cos((angle * 0.5f) * (3.14159265f / 180.0f));

	// 로그 찍기
	printf("Yaw: %.1f | Dot: %.3f | CosHalf: %.3f\n", _rotation.yaw, dot, cosHalf);

	return dot >= cosHalf;
}

void GameObject::SetPos(Vector pos)
{
	_pos = pos;
	// 방향 나중에 바꾸기
	_box.SetOwnerPos(pos, Front);
}

void GameObject::SetState(ObjectState state)
{
	if(_state == state)
		return;

	_state = state;
	g_framework->SendUpdateObjectStatePacket(shared_from_this(), true);
}

void GameObject::SetObjectPoolState(ObjectPoolState objectPoolState)
{
	if (_objectPoolState == objectPoolState)
		return;

	_objectPoolState = objectPoolState;

	if(_objectPoolState == ObjectPoolState::Reusable)
		g_framework->SendRemoveObjectPacket(_type, _id, true);
}