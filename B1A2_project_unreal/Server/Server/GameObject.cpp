#include "pch.h"
#include "GameObject.h"
#include "Global.h"

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