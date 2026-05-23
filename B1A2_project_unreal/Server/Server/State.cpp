#include "pch.h"
#include "State.h"
#include "Room.h"
#include "Cube.h"
#include "Door.h"
#include "Global.h"
#include "Spider.h"
#include "EmotionGame.h"
#include "Ghost.h"
#include "PollutionMonitor.h"
#include "TrashCollector.h"

void State::Tick(Monster* monster)
{
	if (monster->IsReadyNextState())
		monster->SetState(monster->GetStateTable().at(monster->GetState()));
}

IdleState* g_idleState = new IdleState();
RoamingState* g_roamingState = new RoamingState();
ChaseState* g_chaseState = new ChaseState();
ReturnState* g_returnState = new ReturnState();
AttackState* g_attackState = new AttackState();
HitState* g_hitState = new HitState();
DeadState* g_deadState = new DeadState();
MakeWebState* g_makeWebState = new MakeWebState();
Teleport* g_teleportState = new Teleport();
Grab* g_grabState = new Grab();
Play* g_playState = new Play();
Release* g_releaseState = new Release();
Absent* g_absentState = new Absent();
Staring* g_staringState = new Staring();
Vanishing* g_vanishingState = new Vanishing();
CheckState* g_checkState = new CheckState();
SpawnState* g_spawnState = new SpawnState();
AllAttackState* g_allAttackState = new AllAttackState();

//--------------Idle--------------
void IdleState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void IdleState::Exit(Monster* monster)
{
	monster->InitSumTime();
}

//--------------Roaming--------------
void RoamingState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	// 최종 목적지 갱신
	if (!monster->GetTargetPos())
	{
		const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
		const CubeRef currentCube = cubes[monster->GetCurrentCubeID()];
		const CubeRef goalCube = monster->SelectRandomConnectedCube();
		
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
	const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
	monster->SetPos(path[0]);
	monster->SetCurrentCubeID();
	path.pop_front();

	// Broadcast
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendMovePacket(monster, p->GetClient());
	}
}

void RoamingState::Exit(Monster* monster)
{
	monster->InitSumTime();
	monster->ClearPath();
}

//--------------Chase--------------
void ChaseState::Enter(Monster* monster)
{
	monster->SetReturnPos(monster->GetPos());
	monster->SetReturnCubeID(monster->GetCurrentCubeID());
}

void ChaseState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	// 최종 목적지 갱신
	if (!monster->GetTargetPos())
	{
		const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
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
		const std::vector<Door*>& doors = monster->GetOwnerRoom()->GetDoors();
		Door* door{};
		for (int doorID : cubePath[0]->GetDoors())
		{
			if (doors[doorID ]->GetConnectedCubeID() == cubePath[1]->GetID() ||
				doors[doorID]->GetOwnerCubeID() == cubePath[1]->GetID())
			{
				door = doors[doorID];
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
			case Back:
				if(doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
			case Left:
				if(doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
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
				monster->SetTargetPos(std::nullopt);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}

	std::deque<VectorInt>& path = monster->GetPath();
	if (!path.empty())
	{
		Vector targetPos = path[0];
		Vector currentPos = monster->GetPos();

		// 2. 방향 및 거리 계산
		Vector dir = targetPos - currentPos;
		float distance = dir.Length(); // 현재 타겟까지 남은 거리

		// 3. 이동 속도 적용
		float moveDist = monster->GetChaseSpeed() * g_timer->GetDeltaTime();

		if (distance <= moveDist)
		{
			// 이번 프레임에 타겟 타일에 도착할 수 있다면
			monster->SetPos(targetPos); // 딱 맞춰서 도착
			path.pop_front();           // 도착했으니 다음 경로로
		}
		else
		{
			// 아직 가는 중이라면 방향벡터만큼 조금만 이동
			dir.Normalize();

			float angleRad = std::atan2(dir.y, dir.x);
			float angleDeg = angleRad * (180.0f / 3.14159265f); // 라디안 -> 디그리 변환

			Rotation newRot = { 0.f, angleDeg, 0.f }; // 바닥에서만 도니까 Roll, Pitch는 0

			monster->SetRotation(newRot);
			monster->SetPos(currentPos + (dir * moveDist));
		}

		// Broadcast
		for (auto& p : monster->GetOwnerRoom()->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			g_network->SendMovePacket(monster, p->GetClient());
		}
	}

	// 최종 목적지 도달 체크
	if (path.empty())
	{
		monster->SetTargetPos(std::nullopt);
	}
}

void ChaseState::Exit(Monster* monster)
{
	monster->InitSumTime();
	monster->ClearPath();
}

//--------------Return----------------
void ReturnState::Tick(Monster* monster)
{
	State::Tick(monster);

	// returnPos로 목적지 설정
	if (monster->GetPath().empty())
	{
		const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
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
		const std::vector<Door*>& doors = monster->GetOwnerRoom()->GetDoors();
		Door* door{};
		for (int doorID : cubePath[0]->GetDoors())
		{
			if (doors[doorID]->GetConnectedCubeID() == cubePath[1]->GetID() ||
				doors[doorID]->GetOwnerCubeID() == cubePath[1]->GetID())
			{
				door = doors[doorID];
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
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
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
	const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
	monster->SetPos(path[0]);
	path.pop_front();

	// Broadcast
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendMovePacket(monster, p->GetClient());
	}
}

void ReturnState::Exit(Monster* monster)
{
	monster->ClearPath();
}

//--------------Attack--------------
void AttackState::Enter(Monster* monster)
{
	monster->GetTarget()->TackDamage(monster->GetDamage());

	// Broadcast
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendUpdateHpPacket(monster->GetTarget()->GetID(), monster->GetTarget()->GetHP(), p->GetClient());
	}

	std::cout << "Player " << monster->GetTarget()->GetID() << " HP: " << monster->GetTarget()->GetHP() << "\n";
}

void AttackState::Tick(Monster* monster)
{
	State::Tick(monster);
}

void AttackState::Exit(Monster* monster)
{
	monster->UpdateNextAttackTime();
}

//--------------Hit--------------
void HitState::Tick(Monster* monster)
{
	State::Tick(monster);
}
 
//--------------Dead--------------
void DeadState::Enter(Monster* monster)
{
	monster->SetObjectPoolState(ObjectPoolState::Reusable);
}

// Spider State
//--------------MakeWeb----------------
void MakeWebState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void MakeWebState::Exit(Monster* monster)
{
	Spider* spider = dynamic_cast<Spider*>(monster);

	// 거미줄 생성
	spider->CreateWeb();

	spider->InitSumTime();
}

// EmotionGame State
//--------------Teleport----------------
void Teleport::Tick(Monster* monster)
{
	State::Tick(monster);
}

void Teleport::Exit(Monster* monster)
{
	std::vector<CubeRef> cubes = monster->GetOwnerRoom()->GetCubes();

	std::uniform_int_distribution<int> selectCube(0, cubes.size() - 1);
	CubeRef cube = cubes[selectCube(gen)];
	while (cube->GetID() == monster->GetCurrentCubeID() || cube->GetCubeType() == CubeType::Base)
		cube = cubes[selectCube(gen)];
	
	// 랜덤한 위치로 순간이동
	Vector pos = monster->SelectRandomPosInCube(cube);
	monster->SetPos(pos);
	std::cout << "EmotionGame " << monster->GetID() << " " << pos.x << " " << pos.y << " " << pos.z << std::endl;
	
	// Broadcast
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendMovePacket(monster, p->GetClient());
	}
}

//--------------Grab----------------
void Grab::Enter(Monster* monster)
{
	// Target Player 못움직이게 설정
	monster->GetTarget()->SetIsCanMove(false);
}

void Grab::Tick(Monster* monster)
{
	State::Tick(monster);
}

void Grab::Exit(Monster* monster)
{
	// 타겟의 위치 + 보정값으로 순간이동
	const std::vector<CubeRef> cubes = monster->GetOwnerRoom()->GetCubes();
	Vector cubePos = cubes[monster->GetTarget()->GetCurrentCubeID()]->GetPos();
	Vector pos = monster->GetTarget()->GetPos();
	pos.z = cubePos.z + TileSize;
	monster->SetPos(pos);

	// 타겟의 위치도 몬스터의 내부로 보정
	pos.z += 26;
	monster->GetTarget()->SetPos(pos);

	// Broadcast
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendMovePacket(monster, p->GetClient());
		g_network->SendMovePacket(monster->GetTarget(), p->GetClient());
	}
}

//--------------Play----------------
void Play::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void Play::Exit(Monster* monster)
{
	EmotionGame* emotionGame = dynamic_cast<EmotionGame*>(monster);
	Emotion emotion = emotionGame->SelectEmotion();
	Emotion targetEmotion = emotionGame->GetTarget()->GetCurrentEmotion();
	emotionGame->SetEmotion(emotion);
	emotionGame->SetResult(EmotionGameResult::Draw);

	// Monster가 이겼을 때
	if(emotion == Emotion::Happy && targetEmotion == Emotion::Sad ||
		emotion == Emotion::Sad && targetEmotion == Emotion::Neutral ||
		emotion == Emotion::Neutral && targetEmotion == Emotion::Happy)
	{
		emotionGame->GetTarget()->TackDamage(emotionGame->GetDamage());
		emotionGame->SetResult(EmotionGameResult::Lose);
	}
	// Monster가 졌을 때
	else if (emotion == Emotion::Happy && targetEmotion == Emotion::Neutral ||
		emotion == Emotion::Sad && targetEmotion == Emotion::Happy ||
		emotion == Emotion::Neutral && targetEmotion == Emotion::Sad)
	{
		emotionGame->AddLoseCount();
		emotionGame->GetTarget()->TackHeal(emotionGame->GetHealValue());
		emotionGame->SetResult(EmotionGameResult::Win);
	}

	// 게임결과 통지
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendEmotionGameResultPacket(monster->GetTarget()->GetID(), monster->GetTarget()->GetHP(), emotionGame, p->GetClient());
	}

	emotionGame->InitSumTime();
}

//--------------Release----------------
void Release::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void Release::Exit(Monster* monster)
{
	// Target Player 다시 움직일 수 있게 설정
	monster->GetTarget()->SetIsCanMove(true);

	monster->SetTarget(nullptr);
	monster->InitSumTime();
}

//--------------Abesnt----------------
void Absent::Enter(Monster* monster)
{
	// 타겟 지정
	Player* player = monster->GetOwnerRoom()->SelectPlayerForGhost();
	monster->SetTarget(player);
}

void Absent::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
	
	Ghost* ghost = dynamic_cast<Ghost*>(monster);
	if (ghost->GetAbsentTime() < ghost->GetSumTime())
	{
		monster->InitSumTime();

		Player* target = monster->GetTarget();
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

		// 이거 나중에 층수 고려해서 수정
		pos.z = targetCube->GetPos().z + TileSize;

		// 같은 방이고, 갈 수 있는 곳이라면 이동
		if (monster->IsCanGo(monster->PosToIndex(pos, targetCube), targetCube))
			monster->SetTargetPos(pos);
	}
}

void Absent::Exit(Monster* monster)
{
	monster->InitSumTime();
}

//--------------Staring----------------
void Staring::Enter(Monster* monster)
{
	// target 위치로 이동
	Ghost* ghost = dynamic_cast<Ghost*>(monster);
	ghost->SetPos(ghost->GetTargetPos().value());
	ghost->SetTargetPos(std::nullopt);

	if (ghost->GetTarget()->GetClient())
	{
		g_network->SendMovePacket(ghost, ghost->GetTarget()->GetClient());
		std::cout << "Ghost Move\n";
	}
	
	// 조건 검사
	std::uniform_real_distribution<float> dis(0.0, 1.0);
	if (ghost->GetLookCount() >= 4)
	{
		if (dis(gen) <= 0.85)
		{
			ghost->SetState(ObjectState::CHASE);
			return;
		}
	}

	if (ghost->GetUnlookCount() >= 3)
	{
		if (dis(gen) <= 0.85)
		{
			ghost->SetState(ObjectState::CHASE);
			return;
		}
	}
}

void Staring::Tick(Monster* monster)
{
	// 타겟과의 거리가 지정거리 이하면 Chase로 상태 전환
	Player* target = monster->GetTarget();
	if ((target->GetPos() - monster->GetPos()).Length() <= 150)
	{
		monster->SetState(ObjectState::CHASE);
		return;
	}

	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	// Player 시야에 Ghost가 들어갔는지 체크
	Ghost* ghost = dynamic_cast<Ghost*>(monster);
	if (!ghost->GetCheckLooking())
	{
		if (target->CheckInclude(ghost->GetPos(), target->GetLookRange(), target->GetLookAngle(), target->GetLookHeight()))
			ghost->SetCheckLooking(true);
	}
}

void Staring::Exit(Monster* monster)
{
	// Player가 Ghost를 봤는지 안봤는지 체크
	Ghost* ghost = dynamic_cast<Ghost*>(monster);
	if (ghost->GetCheckLooking())
		ghost->AddLookCount();
	else
		ghost->AddUnlookCount();

	// 초기화
	ghost->SetCheckLooking(false);
	ghost->InitSumTime();
}

//--------------Vanishing----------------
void Vanishing::Tick(Monster* monster)
{
	State::Tick(monster);
} 

//--------------Check----------------
void CheckState::Tick(Monster* monster)
{
	// Spawn 조건이 충족됐는지 확인
	Room* room = monster->GetOwnerRoom();
	if (room->GetCurrentFearCount() + room->GetCurrentSurpriseCount() < 5)
		return;

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	// 조건이 충족됐다면 지정된 시간마다 Spawn 할지 말지 확률 적용
	PollutionMonitor* pollutionMonitor = dynamic_cast<PollutionMonitor*>(monster);
	if (pollutionMonitor->GetCheckTime() < pollutionMonitor->GetSumTime())
	{
		pollutionMonitor->InitSumTime();

 		std::uniform_real_distribution<float> dis(0.0, 1.0);
		if (dis(gen) <= 0.3)
		{
			pollutionMonitor->SetState(ObjectState::SPAWN);
			return;
		}
	}
}

//--------------Spawn----------------
void SpawnState::Tick(Monster* monster)
{
	State::Tick(monster);
	
	// 이 누적 시간은 몬스터가 죽을 때까지 초기화하지 않음
	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

//--------------AllAttack----------------
void AllAttackState::Enter(Monster* monster)
{
	// 모든 Player 공격
	for (auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		// Base에 있으면 제외
		if (p->GetCurrentCubeID() == 0)
			continue;

		p->TackDamage(monster->GetDamage());
		g_network->SendUpdateHpPacket(p->GetID(), p->GetHP(), p->GetClient());
		std::cout << "Player " << p->GetID() << " HP: " << p->GetHP() << "\n";
	}
}

void AllAttackState::Tick(Monster* monster)
{
	State::Tick(monster);
}

//--------------Move----------------
void MoveState::Tick(Monster* monster)
{
	State::Tick(monster);

	// 최종 목적지 갱신
	TrashCollector* trashCollector = dynamic_cast<TrashCollector*>(monster);
	if (!trashCollector->GetTargetPos())
	{
		const std::vector<CubeRef>& cubes = trashCollector->GetOwnerRoom()->GetCubes();
		const CubeRef currentCube = cubes[trashCollector->GetCurrentCubeID()];
		const CubeRef goalCube = cubes[trashCollector->GetTargetScrap()->GetCurrentCubeID()];

		// 같은 큐브에 있다면 target scrap의 위치로 바로 경로 갱신
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
		const std::vector<Door*>& doors = monster->GetOwnerRoom()->GetDoors();
		Door* door{};
		for (int doorID : cubePath[0]->GetDoors())
		{
			if (doors[doorID]->GetConnectedCubeID() == cubePath[1]->GetID() ||
				doors[doorID]->GetOwnerCubeID() == cubePath[1]->GetID())
			{
				door = doors[doorID];
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
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			}

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (monster->GetPath().empty())
			{
				monster->SetTargetPos(std::nullopt);
				return;
			}

			monster->SetTargetDoor(door);
			monster->SetIsNeedDoorOpen(true);
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
				monster->SetTargetPos(std::nullopt);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}

	std::deque<VectorInt>& path = monster->GetPath();
	if (!path.empty())
	{
		Vector targetPos = path[0];
		Vector currentPos = monster->GetPos();

		// 2. 방향 및 거리 계산
		Vector dir = targetPos - currentPos;
		float distance = dir.Length(); // 현재 타겟까지 남은 거리

		// 3. 이동 속도 적용
		float moveDist = monster->GetChaseSpeed() * g_timer->GetDeltaTime();

		if (distance <= moveDist)
		{
			// 이번 프레임에 타겟 타일에 도착할 수 있다면
			monster->SetPos(targetPos); // 딱 맞춰서 도착
			path.pop_front();           // 도착했으니 다음 경로로
		}
		else
		{
			// 아직 가는 중이라면 방향벡터만큼 조금만 이동
			dir.Normalize();

			float angleRad = std::atan2(dir.y, dir.x);
			float angleDeg = angleRad * (180.0f / 3.14159265f); // 라디안 -> 디그리 변환

			Rotation newRot = { 0.f, angleDeg, 0.f }; // 바닥에서만 도니까 Roll, Pitch는 0

			monster->SetRotation(newRot);
			monster->SetPos(currentPos + (dir * moveDist));
		}

		// Broadcast
		for (auto& p : monster->GetOwnerRoom()->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			g_network->SendMovePacket(monster, p->GetClient());
		}
	}

	// 최종 목적지 도달 체크
	if (path.empty())
	{
		monster->SetTargetPos(std::nullopt);
		if (monster->GetIsNeedDoorOpen())
		{
			monster->GetTargetDoor()->SetState(ObjectState::OPEN);

			for (auto& p : monster->GetOwnerRoom()->GetPlayers())
			{
				if (!p->GetClient())
					continue;

				g_network->SendUpdateObjectStatePacket(monster->GetTargetDoor(), p->GetClient());
			}

			monster->SetTargetDoor(nullptr);
			monster->SetIsNeedDoorOpen(false);
		}
	}
}

void MoveState::Exit(Monster* monster)
{
	monster->ClearPath();
}

//--------------Collect----------------
void CollectState::Enter(Monster* monster)
{
	TrashCollector* trashCollector = dynamic_cast<TrashCollector*>(monster);
	Item* scrap = trashCollector->GetTargetScrap();
	if (!scrap)
	{
		trashCollector->SetTargetScrap(nullptr);
		return;
	}
		
	trashCollector->AddScrap(scrap->GetID());
	scrap->SetObjectPoolState(ObjectPoolState::InInventory);
	trashCollector->SetTargetScrap(nullptr);

	for(auto& p : monster->GetOwnerRoom()->GetPlayers())
	{
		if (!p->GetClient())
			continue;

		g_network->SendRemoveObjectPacket(ObjectType::Item, scrap->GetID(), p->GetClient());
	}
}

void CollectState::Tick(Monster* monster)
{
	State::Tick(monster);
}

//--------------Escape----------------
void EscapeState::Enter(Monster* monster)
{
	// 목적지 설정
	TrashCollector* trashCollector = dynamic_cast<TrashCollector*>(monster);
	const std::vector<CubeRef>& cubes = trashCollector->GetOwnerRoom()->GetCubes();
	const CubeRef currentCube = cubes[trashCollector->GetCurrentCubeID()];
	// 거리가 되는 Cube 찾기
	std::uniform_int_distribution<int> selecCube(2, cubes.size() - 1);
	CubeRef goalCube = cubes[selecCube(gen)];

	while ((goalCube->GetPos() - currentCube->GetPos()).Length() < trashCollector->GetEscapeDistance())
		goalCube = cubes[selecCube(gen)];
	
	monster->FindCubePath(goalCube, currentCube, cubes);
}

void EscapeState::Tick(Monster* monster)
{
	State::Tick(monster);

	// 경로 갱신
	if (monster->GetPath().empty())
	{
		std::deque<CubeRef>& cubePath = monster->GetCubePath();
		
		// 넘어갈 큐브와 연결된 문 찾기
		const std::vector<Door*>& doors = monster->GetOwnerRoom()->GetDoors();
		Door* door{};
		for (int doorID : cubePath[0]->GetDoors())
		{
			if (doors[doorID]->GetConnectedCubeID() == cubePath[1]->GetID() ||
				doors[doorID]->GetOwnerCubeID() == cubePath[1]->GetID())
			{
				door = doors[doorID];
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
			case Back:
				if (doorPos.y < monsterPos.y)
					goal = { doorPos.x, doorPos.y + monsterSize.y / 2, monsterPos.z };
				else
					goal = { doorPos.x, doorPos.y - monsterSize.y / 2, monsterPos.z };
				break;
			case Right:
			case Left:
				if (doorPos.x < monsterPos.x)
					goal = { doorPos.x + monsterSize.x / 2, doorPos.y, monsterPos.z };
				else
					goal = { doorPos.x - monsterSize.x / 2, doorPos.y, monsterPos.z };
				break;
			}

			monster->FindPath(goal, cubePath[0]);

			// 경로를 찾기 못하면 State 전환
			if (monster->GetPath().empty())
			{
				monster->SetState(ObjectState::ROAMING);
				return;
			}

			monster->SetTargetDoor(door);
			monster->SetIsNeedDoorOpen(true);
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

			// 경로를 찾기 못하면 State 전환
			if (monster->GetPath().empty())
			{
				monster->SetState(ObjectState::ROAMING);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}

	std::deque<VectorInt>& path = monster->GetPath();
	if (!path.empty())
	{
		Vector targetPos = path[0];
		Vector currentPos = monster->GetPos();

		// 2. 방향 및 거리 계산
		Vector dir = targetPos - currentPos;
		float distance = dir.Length(); // 현재 타겟까지 남은 거리

		// 3. 이동 속도 적용
		float moveDist = monster->GetChaseSpeed() * g_timer->GetDeltaTime();

		if (distance <= moveDist)
		{
			// 이번 프레임에 타겟 타일에 도착할 수 있다면
			monster->SetPos(targetPos); // 딱 맞춰서 도착
			path.pop_front();           // 도착했으니 다음 경로로
		}
		else
		{
			// 아직 가는 중이라면 방향벡터만큼 조금만 이동
			dir.Normalize();

			float angleRad = std::atan2(dir.y, dir.x);
			float angleDeg = angleRad * (180.0f / 3.14159265f); // 라디안 -> 디그리 변환

			Rotation newRot = { 0.f, angleDeg, 0.f }; // 바닥에서만 도니까 Roll, Pitch는 0

			monster->SetRotation(newRot);
			monster->SetPos(currentPos + (dir * moveDist));
		}

		// Broadcast
		for (auto& p : monster->GetOwnerRoom()->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			g_network->SendMovePacket(monster, p->GetClient());
		}
	}

	// 최종 목적지 도달 체크
	if (path.empty())
	{
		monster->SetTargetPos(std::nullopt);
		if (monster->GetIsNeedDoorOpen())
		{
			monster->GetTargetDoor()->SetState(ObjectState::OPEN);

			for (auto& p : monster->GetOwnerRoom()->GetPlayers())
			{
				if (!p->GetClient())
					continue;

				g_network->SendUpdateObjectStatePacket(monster->GetTargetDoor(), p->GetClient());
			}

			monster->SetTargetDoor(nullptr);
			monster->SetIsNeedDoorOpen(false);
		}
	}
}