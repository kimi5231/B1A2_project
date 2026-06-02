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
TeleportState* g_teleportState = new TeleportState();
GrabState* g_grabState = new GrabState();
PlayState* g_playState = new PlayState();
ReleaseState* g_releaseState = new ReleaseState();
AbsentState* g_absentState = new AbsentState();
StaringState* g_staringState = new StaringState();
VanishingState* g_vanishingState = new VanishingState();
CheckState* g_checkState = new CheckState();
SpawnState* g_spawnState = new SpawnState();
AllAttackState* g_allAttackState = new AllAttackState();
MoveState* g_moveState = new MoveState();
CollectState* g_collectState = new CollectState();
EscapeState* g_escapeState = new EscapeState();

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
	
	const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
	monster->UpdatePath(SelectRandomPosInCube(cubes[monster->GetCurrentCubeID()]), monster->SelectRandomConnectedCube());
	monster->Move(monster->GetRoamingSpeed(), ObjectState::ROAMING);
}

void RoamingState::Exit(Monster* monster)
{
	monster->InitSumTime();
	monster->ClearPath();
}

//--------------Chase--------------
void ChaseState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());

	const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
	monster->UpdatePath(monster->GetTarget()->GetPos(), cubes[monster->GetTarget()->GetCurrentCubeID()]);
	monster->Move(monster->GetChaseSpeed(), ObjectState::CHASE);
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

	const std::vector<CubeRef>& cubes = monster->GetOwnerRoom()->GetCubes();
	monster->UpdatePath(monster->GetReturnPos(), cubes[monster->GetReturnCubeID()]);
	monster->Move(monster->GetReturnSpeed(), ObjectState::RETURN);
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
void TeleportState::Tick(Monster* monster)
{
	State::Tick(monster);
}

void TeleportState::Exit(Monster* monster)
{
	std::vector<CubeRef> cubes = monster->GetOwnerRoom()->GetCubes();

	std::uniform_int_distribution<int> selectCube(0, cubes.size() - 1);
	CubeRef cube = cubes[selectCube(gen)];
	while (cube->GetID() == monster->GetCurrentCubeID() || cube->GetCubeType() == CubeType::Base)
		cube = cubes[selectCube(gen)];
	
	// 랜덤한 위치로 순간이동
	Vector pos = SelectRandomPosInCube(cube);
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
void GrabState::Enter(Monster* monster)
{
	// Target Player 못움직이게 설정
	monster->GetTarget()->SetIsCanMove(false);
}

void GrabState::Tick(Monster* monster)
{
	State::Tick(monster);
}

void GrabState::Exit(Monster* monster)
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
void PlayState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void PlayState::Exit(Monster* monster)
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
void ReleaseState::Tick(Monster* monster)
{
	State::Tick(monster);

	monster->AddDeltaTime(g_timer->GetDeltaTime());
}

void ReleaseState::Exit(Monster* monster)
{
	// Target Player 다시 움직일 수 있게 설정
	monster->GetTarget()->SetIsCanMove(true);

	monster->SetTarget(nullptr);
	monster->InitSumTime();
}

//--------------Abesnt----------------
void AbsentState::Enter(Monster* monster)
{
	// 타겟 지정
	Player* player = monster->GetOwnerRoom()->SelectPlayerForGhost();
	monster->SetTarget(player);
}

void AbsentState::Tick(Monster* monster)
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
		if (monster->IsCanGo(PosToIndex(pos, targetCube), targetCube))
			monster->SetTargetPos(pos);
	}
}

void AbsentState::Exit(Monster* monster)
{
	monster->InitSumTime();
}

//--------------Staring----------------
void StaringState::Enter(Monster* monster)
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

void StaringState::Tick(Monster* monster)
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

void StaringState::Exit(Monster* monster)
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
void VanishingState::Tick(Monster* monster)
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

	TrashCollector* trashCollector = dynamic_cast<TrashCollector*>(monster);
	const std::vector<CubeRef>& cubes = trashCollector->GetOwnerRoom()->GetCubes();
	trashCollector->UpdatePath(trashCollector->GetTargetScrap()->GetPos(), cubes[trashCollector->GetTargetScrap()->GetCurrentCubeID()]);
	trashCollector->Move(trashCollector->GetMoveSpeed(), ObjectState::MOVE);
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
	// 거리가 되는 Cube 찾기 (Base 제외)
	std::uniform_int_distribution<int> selecCube(1, cubes.size() - 1);
	CubeRef goalCube = cubes[selecCube(gen)];

	while ((goalCube->GetPos() - currentCube->GetPos()).Length() < trashCollector->GetEscapeDistance())
		goalCube = cubes[selecCube(gen)];
	
	trashCollector->SetEscapeCube(goalCube);
}

void EscapeState::Tick(Monster* monster)
{
	State::Tick(monster);
	  
	TrashCollector* trashCollector = dynamic_cast<TrashCollector*>(monster);
	CubeRef goalCube = trashCollector->GetEscapeCube();
	trashCollector->UpdatePath(SelectRandomPosInCube(goalCube), goalCube);
	trashCollector->Move(trashCollector->GetEscapeSpeed(), ObjectState::ESCAPE);
}