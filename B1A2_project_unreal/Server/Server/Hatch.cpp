#include "pch.h"
#include "Hatch.h"
#include "Global.h"

Hatch::Hatch(Vector pos, Dir dir, int ownerCubeID, Dir cubeDir)
	: Door(pos, dir, ownerCubeID, cubeDir)
{
	_doorType = DoorType::Hatch;
	_changeStateTime = 20.f;
	_sumTime = 0.f;
}

void Hatch::Update()
{
	_sumTime += g_timer->GetDeltaTime();

	if(_sumTime >= _changeStateTime)
	{
		if (_state == ObjectState::OPEN)
			SetState(ObjectState::CLOSE, true);
		else
			SetState(ObjectState::OPEN, true);
	}
}

bool Hatch::SetState(ObjectState state, bool isSend)
{
	if (!GameObject::SetState(state, isSend))
		return false;
	
	// 상태가 전환될 때마다 시간 초기화
	_sumTime = 0.f;

	return true;
}