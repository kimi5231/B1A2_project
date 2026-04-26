#include "pch.h"
#include "State.h"
#include "Room.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"
#include "Spider.h"

IdleState* g_idleState = new IdleState();
RoamingState* g_roamingState = new RoamingState();

//--------------Idle--------------
void IdleState::Tick(MonsterRef monster, Room* room)
{
	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void IdleState::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}

//--------------Roaming--------------
void RoamingState::Tick(MonsterRef monster, Room* room)
{
	monster->AddDeltaTime(g_timer->GetDeltaTime());

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
			monster->FindPath(goal, currentCube);
			monster->SetTargetPos(&goal);
		}
		else // 목적 큐브까지 경로 찾기
			monster->FindCubePath(goalCube, currentCube, cubes);
	}
	
	// 경로 갱신
	if (monster->GetPath().empty())
	{
		std::deque<CubeRef>& cubePath = monster->GetCubePath();
		if (cubePath.size() <= 1)
		{
			monster->SetTargetPos(nullptr);
			return;
		}

		// 경로 찾기
		VectorInt goal = monster->SelectRandomPosInCube(cubePath[1]);
		monster->FindPath(goal, cubePath[0]);
		monster->SetTargetPos(&goal);

		// 경로를 찾지 못했다면 목적지 재설정
		if (monster->GetPath().empty())
		{
			monster->SetTargetPos(nullptr);
			return;
		}

		// 지나온 큐브는 경로에서 제외
		cubePath.pop_front();
	}

	// 최종 목적지까지 도달했다면, 타겟 리셋
	std::deque<VectorInt>& path = monster->GetPath();
	if (*(monster->GetTargetPos()) == path[0])
		monster->SetTargetPos(nullptr);

	// 경로	따라 이동
	const std::vector<CubeRef>& cubes = room->GetCubes();
	monster->SetPos(path[0]);
	monster->SetCurrentCubeID(cubes);
	path.pop_front();
	g_framework->SendMovePacket(std::shared_ptr<GameObject>(monster), true);
}

void RoamingState::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}

// Spider State
//--------------MakeWeb----------------
void MakeWebState::Tick(MonsterRef monster, Room* room)
{
	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void MakeWebState::Exit(MonsterRef monster)
{
	SpiderRef spider = std::dynamic_pointer_cast<Spider>(monster);
	// 거미줄 생성 알림
	//spider->CreateWeb(room);
	spider->AddWebCount();

	spider->InitSumTime();
}