#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
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