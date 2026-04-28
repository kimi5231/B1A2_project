#include "pch.h"
#include "State.h"
#include "Room.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"
#include "Spider.h"

void State::Tick(MonsterRef monster, Room* room)
{
	if (monster->IsReadyNextState())
		monster->SetState(monster->GetStateTable().at(monster->GetState()));
}

IdleState* g_idleState = new IdleState();
RoamingState* g_roamingState = new RoamingState();
MakeWebState* g_makeWebState = new MakeWebState();
ChaseState* g_chaseState = new ChaseState();
AttackState* g_attackState = new AttackState();
HitState* g_hitState = new HitState();
DeadState* g_deadState = new DeadState();
ReturnState* g_returnState = new ReturnState();

//--------------Idle--------------
void IdleState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void IdleState::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}

//--------------Roaming--------------
void RoamingState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

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
			monster->SetTargetPos(goal);
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
			monster->SetTargetPos(std::nullopt);
			return;
		}

		// 경로 찾기
		VectorInt goal = monster->SelectRandomPosInCube(cubePath[1]);
		monster->FindPath(goal, cubePath[0]);
		monster->SetTargetPos(goal);

		// 경로를 찾지 못했다면 목적지 재설정
		if (monster->GetPath().empty())
		{
			monster->SetTargetPos(std::nullopt);
			return;
		}

		// 지나온 큐브는 경로에서 제외
		cubePath.pop_front();
	}

	// 최종 목적지까지 도달했다면, 타겟 리셋
	std::deque<VectorInt>& path = monster->GetPath();
	if (monster->GetTargetPos() == path[0])
		monster->SetTargetPos(std::nullopt);

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
	monster->ClearPath();
}

//--------------Chase--------------
void ChaseState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	// 최종 목적지 갱신
	if (!monster->GetTargetPos())
	{
		const std::vector<CubeRef>& cubes = room->GetCubes();
		const CubeRef currentCube = cubes[monster->GetCurrentCubeID()];
		const CubeRef goalCube = cubes[monster->GetTarget()->GetCurrentCubeID()];

		// 같은 큐브에 있다면 target의 위치로 바로 경로 갱신
		if (goalCube == currentCube)
		{
			VectorInt goalIndex = monster->PosToIndex(monster->GetTarget()->GetPos(), currentCube);
			VectorInt goal = monster->IndexToPos(goalIndex, currentCube);
			monster->FindPath(goal, currentCube);
			monster->SetTargetPos(goal);
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
			monster->SetTargetPos(std::nullopt);
			return;
		}

		// 넘어갈 큐브와 연결된 문 찾기
		const std::vector<DoorRef>& doors = room->GetDoors();
		DoorRef door;
		for (int doorID : cubePath[0]->GetDoors())
		{
			if (doors[doorID - 1]->GetConnectedCubeID() == cubePath[1]->GetID() ||
				doors[doorID - 1]->GetRoomID() == cubePath[1]->GetID())
			{
				door = doors[doorID - 1];
				break;
			}
		}

		// 지나갈 문이 닫혀있으면 문 앞까지만 경로 찾기
		if (door->GetState() == ObjectState::CLOSE || door->GetState() == ObjectState::LOCK)
		{
			Vector doorPos = door->GetPos();
			Vector mosnterPos = monster->GetPos();
			Vector monsterSize = monster->GetSize();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
				goal = { doorPos.x, doorPos.y + monsterSize.y / 2, mosnterPos.z };
				break;
			case Right:
				goal = { doorPos.x - monsterSize.x / 2, doorPos.y, mosnterPos.z };
				break;
			case Back:
				goal = { doorPos.x, doorPos.y - monsterSize.y / 2, mosnterPos.z };
				break;
			case Left:
				goal = { doorPos.x + monsterSize.x / 2, doorPos.y, mosnterPos.z };
				break;
			}

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (monster->GetPath().empty())
			{
				monster->SetTargetPos(std::nullopt);
				return;
			}
		}

		// 지나갈 문이 열려 있으면 문 너머 좌표까지 경로 찾기
		if (door->GetState() == ObjectState::OPEN)
		{
			Vector goal{ cubePath[1]->GetPos().x, cubePath[1]->GetPos().y, monster->GetPos().z };

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (monster->GetPath().empty())
			{
				monster->SetTargetPos(std::nullopt);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}

	// 최종 목적지까지 도달했다면, 타겟 리셋
	std::deque<VectorInt>& path = monster->GetPath();
	if (monster->GetTargetPos() == path[0])
		monster->SetTargetPos(std::nullopt);

	// 경로	따라 이동
	const std::vector<CubeRef>& cubes = room->GetCubes();
	monster->SetPos(path[0]);
	monster->SetCurrentCubeID(cubes);
	path.pop_front();
	g_framework->SendMovePacket(std::shared_ptr<GameObject>(monster), true);
}

void ChaseState::Exit(MonsterRef monster)
{
	monster->InitSumTime();
	monster->ClearPath();
}

//--------------Attack--------------
void AttackState::Enter(MonsterRef monster)
{
	monster->GetTarget()->TackDamage(monster->GetDamage());
}

// Spider State
//--------------MakeWeb----------------
void MakeWebState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void MakeWebState::Exit(MonsterRef monster)
{
	SpiderRef spider = std::dynamic_pointer_cast<Spider>(monster);

	// 거미줄 생성
	//spider->CreateWeb(room);

	spider->InitSumTime();
}