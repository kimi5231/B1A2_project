#include "pch.h"
#include "GameObject.h"
#include "Global.h"
#include "Utils.h"
#include "Room.h"
#include "Cube.h"

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

bool GameObject::CheckInclude(Vector targetPos, float range, float angle, float height)
{
	float heightDiff = abs(targetPos.z - _pos.z);
	if (heightDiff > height)
		return false;

	// 거리 내에 있는지 확인
	Vector diff = targetPos - _pos;
	diff.z = 0; // 높이 차이 무시

	float disSquare = diff.LengthSquared();
	if (disSquare > range * range)
		return false;

	// 각도 내에 있는지 확인
	Vector forward = GetForwardVector(_rotation.pitch, _rotation.yaw);
	Vector target = diff / sqrt(disSquare);

	float dot = forward.Dot(target);

	float cosHalf = cos((angle * 0.5f) * (3.14159265f / 180.0f));

	return dot >= cosHalf;
}

void GameObject::SetPos(Vector pos)
{
	_pos = pos;
	// 방향 나중에 바꾸기
	_box.SetOwnerPos(pos, Front);
	SetCurrentCubeID();
}

bool GameObject::SetState(ObjectState state, bool isSend)
{
	if(_state == state)
		return false;

	_state = state;

	// Broadcast
	for (auto& p : _ownerRoom->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendUpdateObjectStatePacket(this, p->GetClient());
	}
	
	return true;
}

void GameObject::SetObjectPoolState(ObjectPoolState objectPoolState)
{
	if (_objectPoolState == objectPoolState)
		return;

	_objectPoolState = objectPoolState;

	if (_objectPoolState == ObjectPoolState::Reusable)
	{
		// Broadcast
		for (auto& p : _ownerRoom->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			g_network->SendRemoveObjectPacket(_type, _id, p->GetClient());
		}
	}
}

void GameObject::SetCurrentCubeID()
{
	const std::vector<CubeRef>& cubes = _ownerRoom->GetCubes();
	if (cubes.empty())
		return;

	// 최초로 지정하는 것이라면 전부 확인
	if (_currentCubeID == -1)
	{
		for (const auto& cube : cubes)
		{
			if (cube->GetBoundingBox().CheckInclude(_pos))
			{
				_currentCubeID = cube->GetID();
				return;
			}
		}
	}

	//for (const auto& cube : cubes[_currentCubeID]->GetConnectedCubes())
	for (const auto& cube : cubes)
	{
		if (cube->GetBoundingBox().CheckInclude(_pos))
		{
			_currentCubeID = cube->GetID();
			return;
		}
	}
}