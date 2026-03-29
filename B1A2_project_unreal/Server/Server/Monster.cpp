#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Room.h"
#include "Cube.h"
#include "DataManager.h"
#include "FSM.h"
#include "Door.h"

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

void Monster::Update(const std::vector<CubeRef>& cubes, const std::vector<DoorRef>& doors)
{
	_fsm->Update();

	// 경로 갱신
	if (_path.empty())
	{
		// 목적지 설정
		// 일단은 자신이 있는 큐브와 연결된 큐브의 좌표로 설정, 추후 수정
		CubeRef currentCube;
		for (const CubeRef cube : cubes)
		{
			if (cube->GetBoundingBox().CheckInclude(_pos))
			{
				currentCube = cube;
				break;
			}
		}

		// 이동할 큐브 랜덤하게 선택
		std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
		std::uniform_int_distribution<int> selectCube(0, connectedCubes.size() - 1);
		int index = selectCube(gen);
		CubeRef goalCube = connectedCubes[index];

		// 1차 길찾기
		std::vector<CubeRef> cubePath = FindCubePath(goalCube, currentCube, cubes);


		DoorRef door;
		for (uint& doorID : cubePath[0]->GetDoors())
		{

			if (doors[doorID - 1]->GetConnectedCubeID() == cubePath[1]->GetID())
			{
				door = doors[doorID - 1];
				break;
			}
		}

		Vector goal;
		switch (door->GetDir())
		{
		case Front:
			goal = { door->GetPos().x, door->GetPos().y + _size.y / 2, 100 };
			break;
		case Right:
			goal = { door->GetPos().x - _size.x / 2, door->GetPos().y, 100 };
			break;
		case Back:
			goal = { door->GetPos().x, door->GetPos().y - _size.y / 2, 100 };
			break;
		case Left:
			goal = { door->GetPos().x + _size.x / 2, door->GetPos().y, 100 };
			break;
		}

		_path = FindPath(goal, cubePath[0]);
	}

	SetPos(_path[0]);
	_path.pop_front();
	g_framework->SendMovePacket(shared_from_this(), true);
}

std::vector<CubeRef> Monster::FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms)
{
	// 길찾기에 필요한 자료구조 정의
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

std::deque<VectorInt> Monster::FindPath(VectorInt goal, const CubeRef currentCube)
{
	// 현재 위치한 방의 타일맵 가져오기
	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetCubeType());

	// 타일맵의 시작점 계산(FrontLeftButtom)
	VectorInt cubePos = currentCube->GetPos();
	VectorInt cubeSize = currentCube->GetSize();
	VectorInt tilemapStart{ cubePos.x - cubeSize.x / 2, cubePos.y - cubeSize.y / 2, cubePos.z };
	// CubeType에 따라 보정
	switch (currentCube->GetCubeType())
	{
	case CubeType::GapRoom:	// 입구가 2층
	case CubeType::RailCatwalk:
	case CubeType::StorageRoom_Step:
	case CubeType::CabinetRoom:
	case CubeType::FactoryRoom:
		tilemapStart.z -= 600;
		break;
	}

	// 시작 위치와 목적지의 인덱스 계산
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };
	VectorInt startIndex = (_pos - tilemapStart) / TileSize;
	VectorInt goalIndex = (goal - tilemapStart) / TileSize;

	// Cube 방향에 따라 인덱스 변환
	switch (currentCube->GetDir())
	{
	case Right:
		startIndex = { startIndex.y, max.x - 1 - startIndex.x, startIndex.z };
		goalIndex = { goalIndex.y, max.x - 1 - goalIndex.x, goalIndex.z };
		break;
	case Back:
		startIndex = { max.x - 1 - startIndex.x, max.y - 1 - startIndex.y, startIndex.z };
		goalIndex = { max.x - 1 - goalIndex.x, max.y - 1 - goalIndex.y, goalIndex.z };
		break;
	case Left:
		startIndex = { max.y - 1 - startIndex.y, startIndex.x, startIndex.z };
		goalIndex = { max.y - 1 - goalIndex.y, goalIndex.x, goalIndex.z };
		break;
	}

	// 길찾기에 사용할 임시 BoundingBox
	BoundingBox box = _box;

	// 길찾기에 필요한 자료구조 정의
	auto cmp = [](TileNode* a, TileNode* b) { return a->f > b->f; };
	std::priority_queue<TileNode*, std::vector<TileNode*>, decltype(cmp)> openList(cmp);
	std::unordered_map<VectorInt, TileNode*, VectorIntHash> openMap;
	std::unordered_set<VectorInt, VectorIntHash> closeList;

	// openList에 시작 노드 추가
	// 유클리드 거리로 휴리스틱 계산
	float startH = sqrt((_pos.x - goal.x)* (_pos.x - goal.x) + (_pos.y - goal.y) * (_pos.y - goal.y) + (_pos.z - goal.z) * (_pos.z - goal.z));
	TileNode* startNode = new TileNode{ startIndex, 0, startH, startH, nullptr };
	openList.push(startNode);
	openMap[startIndex] = startNode;

	while (!openList.empty())
	{
		// openList에서 f값이 가장 작은 노드 꺼내기
		TileNode* currentNode = openList.top();
		openList.pop();
		openMap.erase(currentNode->index);

		// 현재 노드와 연결된 모든 노드 확인
		// 상하좌우 대각선
		for (int x = currentNode->index.x - 1; x <= currentNode->index.x + 1; ++x)
		{
			for (int y = currentNode->index.y - 1; y <= currentNode->index.y + 1; ++y)
			{
				VectorInt connectedIndex{ x, y, currentNode->index.z };

				// 현재 노드는 제외
				if (connectedIndex == currentNode->index)
					continue;

				// 갈 수 있는 노드인지 확인
				bool canGo = true;
				// 나중에 이동 방향에 따라 Dir 수정하기
				box.SetOwnerPos(tilemapStart + connectedIndex * TileSize, Front);
				const std::array<Vector, CornerCount>& corners = box.GetCorners();
				for (const auto& corner : corners)
				{
					VectorInt index = (corner - tilemapStart) / TileSize;

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
						std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
						for (const auto& cube : connectedCubes)
						{
							VectorInt otherCubePos = cube->GetPos();
							VectorInt otherCubeSize = cube->GetSize();
							VectorInt otherstart{ otherCubePos.x - otherCubeSize.x / 2, otherCubePos.y - otherCubeSize.y / 2, otherCubePos.z };
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

							// 다른 타일맵에서의 Index 계산
							const std::vector<std::vector<std::vector<short>>> otherTilemap = g_dataManager->GetTilemap(cube->GetCubeType());
							VectorInt otherMax{ otherTilemap[0][0].size(), otherTilemap[0].size(), otherTilemap.size() };
							VectorInt otherIndex = (corner - otherstart) / TileSize;

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

							// 연결된 큐브에 포함되지 않으면 일단 갈 수 없음으로 간주
							if (otherIndex < Vector{ 0, 0, 0 } || otherIndex >= otherMax)
							{
								canGo = false;
								continue;
							}

							// 하나의 모서리라도 갈 수 없는 곳에 위치하면 이동 불가능, 노드 제외
							if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 0)
							{
								canGo = false;
								break;
							}

							// 갈 수 있는 큐브 찾으면 flag 값 바꾸기
							if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 1)
								canGo = true;
						}
					
						if (!canGo)
							break;
					}
					else if (tilemap[index.z][index.y][index.x] == 0)
					{
						// 해당 위치가 갈 수 없는 곳이면 이동 불가능, 노드 제외
						canGo = false;
						break;
					}
				}

				// 갈 수 없는 노드면 제외
				if (!canGo)
					continue;

				// 목적지 노드라면 경로	반환
				if (connectedIndex.x == goalIndex.x && connectedIndex.y == goalIndex.y)
				{
					std::deque<VectorInt> path;
					path.push_back(tilemapStart + goalIndex * TileSize);
					TileNode* node = currentNode;
					while (node)
					{
						path.push_back(tilemapStart + node->index * TileSize);
						node = node->parent;
					}
					std::reverse(path.begin(), path.end());
					return path;
				}

				// 이미 closeList에 있으면 무시
				if (closeList.find(connectedIndex) != closeList.end())
					continue;

				float g = currentNode->g + 1;
				VectorInt connectedPos = tilemapStart + connectedIndex * TileSize;
				float h = sqrt((connectedPos.x - goal.x) * (connectedPos.x - goal.x) + (connectedPos.y - goal.y) * (connectedPos.y - goal.y) + (connectedPos.z - goal.z) * (connectedPos.z - goal.z));
				float f = g + h;

				// 이미 openList에 있을때
				if (openMap.find(connectedIndex) != openMap.end())
				{
					// 더 나은 경로가 발견되면 갱신
					if (openMap[connectedIndex]->f > f)
					{
						TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
						openList.push(newNode);
						openMap[connectedIndex] = newNode;
					}

					continue;
				}

				// 두 List에 모두 없으면 openList에 추가
				TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
				openList.push(newNode);
				openMap[connectedIndex] = newNode;
			}
		}
		
		// 확인한 노드는 closeList에 추가
		closeList.insert(currentNode->index);
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