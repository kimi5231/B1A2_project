#include "pch.h"
#include "State.h"
#include "Room.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"
#include "Spider.h"
#include "EmotionGame.h"
#include "Ghost.h"

void State::Tick(MonsterRef monster, Room* room)
{
	if (monster->IsReadyNextState())
		monster->SetState(monster->GetStateTable().at(monster->GetState()));
}

IdleState* g_idleState = new IdleState();
RoamingState* g_roamingState = new RoamingState();
MakeWebState* g_makeWebState = new MakeWebState();
ChaseState* g_chaseState = new ChaseState();
ReturnState* g_returnState = new ReturnState();
AttackState* g_attackState = new AttackState();
HitState* g_hitState = new HitState();
DeadState* g_deadState = new DeadState();
Teleport* g_teleportState = new Teleport();

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
			Vector monsterPos = monster->GetPos();
			Vector monsterSize = monster->GetSize();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
				if(doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
				if(doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			case Back:
				if(doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				break;
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
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
			Vector doorPos = door->GetPos();
			Vector monsterPos = monster->GetPos();
			Vector monsterSize = monster->GetSize();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				break;
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			}

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

//--------------Return----------------
void ReturnState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	// returnPos로 목적지 설정
	if (monster->GetPath().empty())
	{
		const std::vector<CubeRef>& cubes = room->GetCubes();
		const CubeRef currentCube = cubes[monster->GetCurrentCubeID()];
		const CubeRef goalCube = cubes[monster->GetReturnCubeID()];

		// 같은 큐브에 있다면 returnPos의 위치로 바로 경로 갱신
		if (goalCube == currentCube)
		{
			VectorInt goalIndex = monster->PosToIndex(monster->GetReturnPos(), currentCube);
			VectorInt goal = monster->IndexToPos(goalIndex, currentCube);
			monster->FindPath(goal, currentCube);
		}
		else // 목적 큐브까지 경로 찾기
			monster->FindCubePath(goalCube, currentCube, cubes);
	}

	// 세부 경로 찾기
	if (monster->GetPath().empty())
	{
		std::deque<CubeRef>& cubePath = monster->GetCubePath();
		if (cubePath.size() <= 1)
		{
			//monster->SetReturnPos(std::nullopt);
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
			Vector monsterPos = monster->GetPos();
			Vector monsterSize = monster->GetSize();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				break;
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			}

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (monster->GetPath().empty())
			{
				//monster->SetReturnPos(std::nullopt);
				return;
			}
		}

		// 지나갈 문이 열려 있으면 문 너머 좌표까지 경로 찾기
		if (door->GetState() == ObjectState::OPEN)
		{
			Vector doorPos = door->GetPos();
			Vector monsterPos = monster->GetPos();
			Vector monsterSize = monster->GetSize();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			}

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (monster->GetPath().empty())
			{
				//monster->SetReturnPos(std::nullopt);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}

	std::deque<VectorInt>& path = monster->GetPath();

	// 경로	따라 이동
	const std::vector<CubeRef>& cubes = room->GetCubes();
	monster->SetPos(path[0]);
	monster->SetCurrentCubeID(cubes);
	path.pop_front();
	g_framework->SendMovePacket(std::shared_ptr<GameObject>(monster), true);
}

void ReturnState::Exit(MonsterRef monster)
{
	monster->ClearPath();
}

//--------------Attack--------------
void AttackState::Enter(MonsterRef monster)
{
	monster->GetTarget()->TackDamage(monster->GetDamage());
	std::cout << "Player " << monster->GetTarget()->GetID() << " HP: " << monster->GetTarget()->GetHP() << "\n";
}

void AttackState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);
}

void AttackState::Exit(MonsterRef monster)
{
	monster->UpdateNextAttackTime();
}

//--------------Hit--------------
void HitState::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);
}

//--------------Dead--------------
void DeadState::Enter(MonsterRef monster)
{
	monster->SetObjectPoolState(ObjectPoolState::Reusable);
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
	spider->CreateWeb();

	spider->InitSumTime();
}

// EmotionGame State
//--------------Teleport----------------
void Teleport::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);
}

void Teleport::Exit(MonsterRef monster)
{
	std::vector<CubeRef> cubes = monster->GetOwnerRoom()->GetCubes();

	std::uniform_int_distribution<int> selectCube(0, cubes.size() - 1);
	CubeRef cube = cubes[selectCube(gen)];
	while (cube->GetID() == monster->GetCurrentCubeID())
		cube = cubes[selectCube(gen)];
	
	// 랜덤한 위치로 순간이동
	Vector pos = monster->SelectRandomPosInCube(cube);
	monster->SetPos(pos);
}

//--------------Grab----------------
void Grab::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);
}

void Grab::Exit(MonsterRef monster)
{
	// 타겟의 위치로 순간이동
	monster->SetPos(monster->GetTarget()->GetPos());

	// 보정 필요하면 보정하기
}

//--------------Play----------------
void Play::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void Play::Exit(MonsterRef monster)
{
	EmotionGameRef emotionGame = std::dynamic_pointer_cast<EmotionGame>(monster);
	Emotion emotion = emotionGame->SelectEmotion();
	Emotion targetEmotion = emotionGame->GetTarget()->GetCurrentEmotion();
	emotionGame->SetResult(EmotionGameResult::Draw);

	// Monster가 이겼을 때
	if(emotion == Emotion::Happy && targetEmotion == Emotion::Sad ||
		emotion == Emotion::Sad && targetEmotion == Emotion::Neutral ||
		emotion == Emotion::Neutral && targetEmotion == Emotion::Happy)
	{
		emotionGame->GetTarget()->TackDamage(emotionGame->GetDamage());
		emotionGame->SetResult(EmotionGameResult::Win);
	}
	// 졌을 때
	else if (emotion == Emotion::Happy && targetEmotion == Emotion::Neutral ||
		emotion == Emotion::Sad && targetEmotion == Emotion::Happy ||
		emotion == Emotion::Neutral && targetEmotion == Emotion::Sad)
	{
		emotionGame->AddLoseCount();
		emotionGame->GetTarget()->TackHeal(emotionGame->GetHealValue());
		emotionGame->SetResult(EmotionGameResult::Lose);
	}

	// 결과 패킷 보내기


	emotionGame->InitSumTime();
}

//--------------Release----------------
void Release::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void Release::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}

//--------------Abesnt----------------
void Abesnt::Enter(MonsterRef monster)
{
	// 일단 랜덤으로. 추후, Fear 수치 활용할 것.
	const std::unordered_map<uint, PlayerRef>& players = monster->GetOwnerRoom()->GetPlayers();
	std::uniform_int_distribution<int> selectCube(0, players.size() - 1);
	PlayerRef player = players.at(selectCube(gen));
	monster->SetTarget(player);
}

void Abesnt::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
	
	GhostRef ghost = std::dynamic_pointer_cast<Ghost>(monster);
	if (ghost->GetAbsentTime() < ghost->GetSumTime())
	{
		monster->InitSumTime();

		PlayerRef target = monster->GetTarget();
		Vector targetPos = target->GetPos();
		Rotation rotation = target->GetRotation();
		Vector targetForward = GetForwardVector(rotation.pitch, rotation.yaw);
		// Player가 바라보는 방향의 반대에서 4m 떨어진 위치 구하기
		Vector pos = (targetForward * -400) + targetPos;
		
		// Player랑 같은 방의 위치인지 확인
		std::vector<CubeRef> cubes = monster->GetOwnerRoom()->GetCubes();
		CubeRef targetCube = cubes[target->GetCurrentCubeID()];
		if (!monster->IsPointInCube(pos, targetCube))
			return;

		// 같은 방이고, 갈 수 있는 곳이라면 이동
		if (monster->IsCanGo(pos, targetCube))
			monster->SetTargetPos(pos);
	}
}

void Abesnt::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}

//--------------Staring----------------
void Staring::Enter(MonsterRef monster)
{
	// target로 이동
	monster->SetPos(monster->GetTargetPos().value());
	monster->SetTargetPos(std::nullopt);
}

void Staring::Tick(MonsterRef monster, Room* room)
{
	State::Tick(monster, room);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void Staring::Exit(MonsterRef monster)
{
	monster->InitSumTime();
}