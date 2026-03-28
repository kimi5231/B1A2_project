#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Room.h"
#include "Cube.h"
#include "DataManager.h"
#include "FSM.h"

Monster::Monster()
{
	// FSM 생성
	_fsm = new FSM();

	// State 생성
	_idle = new IdleState();
	_roaming = new RoamingState();
	_openDoor = new OpenDoorState();
	_chase = new ChaseState();
	_attack = new AttackState();
	_hit = new HitState();
	_dead = new DeadState();

	_pos = {0, 200, 100};
	_size = { 80, 80, 80 };
	_rotation = { 0, 0, 0 };
	_type = ObjectType::Monster;
	// 나중에 방향 조절하기
	_box.SetBounds(_pos, _size, Front);
} 

Monster::~Monster()
{
}

void Monster::Update(const std::vector<CubeRef>& gameRooms)
{
	_fsm->Update();

	std::vector<CubeRef> path = FindCubePath({ 0, 0, 0 }, gameRooms);

	{
		// 현재 위치한 방이 어디인지 확인
		CubeRef currentCube;
		for (const CubeRef gameRoom : gameRooms)
		{
			if (gameRoom->GetBoundingBox().CheckInclude(_pos))
			{
				currentCube = gameRoom;
				break;
			}
		}

		if (!currentCube)
			return;

		// 현재 위치한 방의 타일맵 가져오기
		const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetCubeType());

		// 타일맵의 시작점 계산(FrontLeftButtom)
		Vector cubePos = currentCube->GetPos();
		Vector cubeSize = currentCube->GetSize();
		Vector start{ cubePos.x - cubeSize.x / 2, cubePos.y - cubeSize.y / 2, cubePos.z };
		switch (currentCube->GetCubeType())
		{
		case CubeType::GapRoom:	// 입구가 2층
		case CubeType::RailCatwalk:
		case CubeType::StorageRoom_Step:
		case CubeType::CabinetRoom:
		case CubeType::FactoryRoom:
			start.z -= 600;
			break;
		}

		// 일단은 랜덤한 방향으로 이동하도록, 추후 수정
		std::uniform_int_distribution<int> selectDir(static_cast<int>(Front), static_cast<int>(Left));
		Dir dir = static_cast<Dir>(selectDir(gen));

		// 이동할 좌표 계산
		Vector pos = _pos;
		// 타일 한칸씩 이동
		_pos.y += TileSize;

		SetPos(_pos);

		// 해당 타일로 이동이 가능한지 확인
		// 몬스터 바운딩 박스 꼭짓점 인덱스 계산 및 확인
		const std::array<Vector, CornerCount>& corners = _box.GetCorners();
		for (const auto& corner : corners)
		{
			Vector max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };
			Vector index = (corner - start) / TileSize;

			// Cube 방향에 따라 인덱스 변환
			switch (currentCube->GetDir())
			{
			case Right:
				index = { index.y, max.x - 1 - index.x, index.z };
				break;
			case Back:
				index = { max.x - 1 - index.x, max.y - 1 - index.y, index.z };
				break;
			case Left:
				index = { max.y - 1 - index.y, index.x, index.z };
				break;
			}

			// 현재 있는 Cube의 Tilemap 안에 Index가 포함되지 않으면, 연결된 Cube들도 확인
			if (index < Vector{ 0, 0, 0 } || index >= max)
			{
				bool flag = true;
				std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
				for (const auto& cube : connectedCubes)
				{
					Vector otherCubePos = cube->GetPos();
					Vector otherCubeSize = cube->GetSize();
					Vector otherstart{ otherCubePos.x - otherCubeSize.x / 2, otherCubePos.y - otherCubeSize.y / 2, otherCubePos.z };
					switch (cube->GetCubeType())
					{
					case CubeType::GapRoom:	// 입구가 2층
					case CubeType::RailCatwalk:
					case CubeType::StorageRoom_Step:
					case CubeType::CabinetRoom:
					case CubeType::FactoryRoom:
						otherstart.z -= 600;
						break;
					}

					const std::vector<std::vector<std::vector<short>>> otherTilemap = g_dataManager->GetTilemap(cube->GetCubeType());
					Vector otherMax{ otherTilemap[0][0].size(), otherTilemap[0].size(), otherTilemap.size() };
					Vector otherIndex = (corner - otherstart) / TileSize;

					// Cube 방향에 따라 인덱스 변환
					switch (cube->GetDir())
					{
					case Right:
						otherIndex = { otherIndex.y, otherMax.x - 1 - otherIndex.x, otherIndex.z };
						break;
					case Back:
						otherIndex = { otherMax.x - 1 - otherIndex.x, otherMax.y - 1 - otherIndex.y, otherIndex.z };
						break;
					case Left:
						otherIndex = { otherMax.y - 1 - otherIndex.y, otherIndex.x, otherIndex.z };
						break;
					}

					if (otherIndex < Vector{ 0, 0, 0 } || otherIndex >= otherMax)
						continue;

					// 해당 위치가 갈 수 없는 타일이면 이전 좌표로 되돌리기
					if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 0)
					{
						SetPos(pos);
						return;
					}

					// 갈 수 있으면 flag 값 바꾸기
					if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 1)
						flag = false;
				}

				// 임시. 코드 반드시 최적화 할 것
				// 연결된 방들 중 포함된 방이 하나도 없으면 이전 좌표로 되돌리기
				if (flag)
				{
					SetPos(pos);
					return;
				}
			}
			else if (tilemap[index.z][index.y][index.x] == 0)
			{
				SetPos(pos);
				return;
			}
		}

		g_framework->SendMovePacket(shared_from_this(), true);
	}
}

std::vector<CubeRef> Monster::FindCubePath(Vector goal, const std::vector<CubeRef>& gameRooms)
{
	// 목적지 설정
	// 일단은 자신이 있는 큐브와 연결된 큐브의 좌표로 설정, 추후 수정
	CubeRef currentCube;
	for (const CubeRef gameRoom : gameRooms)
	{
		if (gameRoom->GetBoundingBox().CheckInclude(_pos))
		{
			currentCube = gameRoom;
			break;
		}
	}

	// 이동할 큐브 랜덤하게 선택
	std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
	std::uniform_int_distribution<int> selectCube(0, connectedCubes.size() - 1);
	int index = selectCube(gen);
	CubeRef goalCube = connectedCubes[index];

	// 목적지 큐브 찾기 (1차 탐색)
	auto cmp = [](CubeNode* a, CubeNode* b) { return a->f > b->f; };
	std::priority_queue<CubeNode*, std::vector<CubeNode*>, decltype(cmp)> openList(cmp);
	std::unordered_map<unsigned char, CubeNode*> openMap;
	std::unordered_set<unsigned char> closeList;

	// openList에 시작 노드 추가
	float startH = abs(currentCube->GetPos().x - goalCube->GetPos().x) + abs(currentCube->GetPos().y - goalCube->GetPos().y) + abs(currentCube->GetPos().z - goalCube->GetPos().z);
	CubeNode* startNode = new CubeNode{ currentCube, 0, startH, startH, nullptr };
	openList.push(startNode);
	openMap[currentCube->GetID()] = startNode;

	while (!openList.empty())
	{
		// openList에서 f값이 가장 작은 노드 가져오기
		CubeNode* currentNode = openList.top();
		openList.pop();
		openMap.erase(currentNode->cube->GetID());

		// 현재 노드와 연결된 모든 노드 확인
		std::vector<CubeRef>& currentConnectedCubes = currentNode->cube->GetConnectedCubes();
		for (const auto& cube : currentConnectedCubes)
		{
			// 목적지 노드라면 경로	반환
			if (cube->GetID() == goalCube->GetID())
			{
				std::vector<CubeRef> path;
				path.push_back(goalCube);
				CubeNode* node = currentNode;
				while (node)
				{
					path.push_back(node->cube);
					node = node->parent;
				}
				std::reverse(path.begin(), path.end());
				return path;
			}

			// 이미 closeList에 있으면 무시
			if (closeList.find(cube->GetID()) != closeList.end())
				continue;

			float g = currentNode->g + 1;
			float h = abs(cube->GetPos().x - goalCube->GetPos().x) + abs(cube->GetPos().y - goalCube->GetPos().y) + abs(cube->GetPos().z - goalCube->GetPos().z);
			float f = g + h;

			// 이미 openList에 있을때
			if (openMap.find(cube->GetID()) != openMap.end())
			{
				// 더 나은 경로가 발견되면 갱신
				if (openMap[cube->GetID()]->f > f)
				{
					CubeNode* newNode = new CubeNode{ cube, g, h, f, currentNode };
					openList.push(newNode);
					openMap[cube->GetID()] = newNode;
				}

				continue;
			}

			// 두 List에 모두 없으면 openList에 추가
			CubeNode* newNode = new CubeNode{ cube, g, h, f, currentNode };
			openList.push(newNode);
			openMap[cube->GetID()] = newNode;
		}

		// 확인한 노드는 closeList에 추가
		closeList.insert(currentNode->cube->GetID());
	}
}

void Monster::SetState(ObjectState state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case IDLE:
		_fsm->ChangeState(_idle);
		break;
	case ROAMING:
		_fsm->ChangeState(_roaming);
		break;
	case OPEN_DOOR:
		_fsm->ChangeState(_openDoor);
		break;
	case CHASE:
		_fsm->ChangeState(_chase);
		break;
	case ATTACK:
		_fsm->ChangeState(_attack);
		break;
	case HIT:
		_fsm->ChangeState(_hit);
		break;
	case DEAD:
		_fsm->ChangeState(_dead);
		break;
	}
}