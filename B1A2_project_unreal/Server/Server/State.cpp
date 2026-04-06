#include "pch.h"
#include "State.h"
#include "Monster.h"
#include "Room.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"

//--------------Idle--------------
void IdleState::Enter(MonsterRef monster)
{
	monster->SetState(ObjectState::IDLE);
}

//--------------Roaming--------------
void RoamingState::Enter(MonsterRef monster)
{
	monster->SetState(ObjectState::ROAMING);
	_start = std::chrono::steady_clock::now();
}

void RoamingState::Tick(MonsterRef monster, Room* room)
{
	// 최종 목적지 갱신
	if (!monster->GetTargetPos())
	{
		const std::vector<CubeRef>& cubes = room->GetCubes();
		const CubeRef currentCube = cubes[monster->GetCurrentCubeID()];
		const CubeRef goalCube = monster->SelectRandomConnectedCube(room);
		
		// 갈 수 있는 큐브가 없으면 큐브 내에서 목적지 설정
		if (goalCube == currentCube)
		{
			VectorInt goal = monster->SelectRandomPosInCube(currentCube);
			_path = monster->FindPath(goal, currentCube);
			monster->SetTargetPos(&goal);
		}
		else // 목적 큐브까지 경로 찾기
			_cubePath = monster->FindCubePath(goalCube, currentCube, cubes);
	}
	
	// 경로 갱신
	if (_path.empty())
	{
		if (_cubePath.size() <= 1)
		{
			monster->SetTargetPos(nullptr);
			return;
		}

		// 경로 찾기
		/*const std::vector<CubeRef>& cubes = room->GetCubes();
		const CubeRef currentCube = cubes[monster->GetCurrentCubeID()];*/
		VectorInt goal = monster->SelectRandomPosInCube(_cubePath[1]);
		_path = monster->FindPath(goal, _cubePath[0]);
		monster->SetTargetPos(&goal);

		// 경로를 찾지 못했다면 목적지 재설정
		if (_path.empty())
		{
			monster->SetTargetPos(nullptr);
			return;
		}

		// 지나온 큐브는 경로에서 제외
		_cubePath.pop_front();
	}

	// 최종 목적지까지 도달했다면, 타겟 리셋
	if (*(monster->GetTargetPos()) == _path[0])
		monster->SetTargetPos(nullptr);

	// 경로	따라 이동
	const std::vector<CubeRef>& cubes = room->GetCubes();
	monster->SetPos(_path[0]);
	monster->SetCurrentCubeID(cubes);
	_path.pop_front();
	g_framework->SendMovePacket(std::shared_ptr<GameObject>(monster), true);
}

// Spider State
//--------------Pause----------------

void PauseState::Enter(MonsterRef monster)
{
	monster->SetState(ObjectState::PAUSE);
	_start = std::chrono::steady_clock::now();
}