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
	_targetPos = nullptr;

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

	// 목적지 갱신
	if (_targetPos == nullptr)
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
		// 최종 목적지 기록
		_targetPos = new VectorInt( goalCube->GetPos().x, goalCube->GetPos().y, _pos.z );

		// 1차 길찾기
		_cubePath = FindCubePath(goalCube, currentCube, cubes);
	}

	// 경로 갱신
	if (_path.empty())
	{
		if (_cubePath.size() == 1)
		{
			_targetPos = nullptr;
			return;
		}

		// 넘어갈 큐브와 연결된 문 찾기
		DoorRef door;
		for (uint& doorID : _cubePath[0]->GetDoors())
		{
			if (doors[doorID - 1]->GetConnectedCubeID() == _cubePath[1]->GetID() ||
				doors[doorID - 1]->GetRoomID() == _cubePath[1]->GetID())
			{
				door = doors[doorID - 1];
				break;
			}
		}

		// 지나갈 문이 닫혀있으면 문 앞까지만 경로 찾기
		if (door->GetState() == ObjectState::CLOSE)
		{
			Vector goal;

			// 나중에 문이 있는 방에 따라 방향 바뀌는 거 고려할 것
			switch (door->GetDir())
			{
			case Front:
				goal = { door->GetPos().x, door->GetPos().y + _size.y / 2, _pos.z };
				break;
			case Right:
				goal = { door->GetPos().x - _size.x / 2, door->GetPos().y, _pos.z };
				break;
			case Back:
				goal = { door->GetPos().x, door->GetPos().y - _size.y / 2, _pos.z };
				break;
			case Left:
				goal = { door->GetPos().x + _size.x / 2, door->GetPos().y, _pos.z };
				break;
			}

			_path = FindPath(goal, _cubePath[0]);
			
			// 경로를 찾기 못하면 목적지 재설정
			if (_path.empty())
			{
				_targetPos = nullptr;
				return;
			}
		}

		// 지나갈 문이 열려 있으면 문의 좌표까지 경로 찾기
		if (door->GetState() == ObjectState::OPEN)
		{
			Vector goal;

			// 나중에 문이 있는 방에 따라 방향 바뀌는 거 고려할 것
			switch (door->GetDir())
			{
			case Front:
				goal = { door->GetPos().x, door->GetPos().y - _size.y / 2, _pos.z };
				break;
			case Right:
				goal = { door->GetPos().x + _size.x / 2, door->GetPos().y, _pos.z };
				break;
			case Back:
				goal = { door->GetPos().x, door->GetPos().y + _size.y / 2, _pos.z };
				break;
			case Left:
				goal = { door->GetPos().x - _size.x / 2, door->GetPos().y, _pos.z };
				break;
			}

			_path = FindPath(goal, _cubePath[0]);

			// 경로를 찾기 못하면 목적지 재설정
			if (_path.empty())
			{
				_targetPos = nullptr;
				return;
			}

			// 지나온 큐브는 경로에서 제외
			_cubePath.pop_front();
		}
	}

	// 최종 목적지까지 도달했다면, 타겟 리셋
	if (*_targetPos == _path[0])
		_targetPos = nullptr;

	// 경로	따라 이동
	SetPos(_path[0]);
	_path.pop_front();
	g_framework->SendMovePacket(shared_from_this(), true);
}

// 나중에 잠긴 문도 고려하기
std::deque<CubeRef> Monster::FindCubePath(const CubeRef goalCube, const CubeRef currentCube, const std::vector<CubeRef>& gameRooms)
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
				std::deque<CubeRef> path;
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

	return {};
}

float Monster::GetDistance(VectorInt a, VectorInt b)
{
	return (float)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

std::deque<VectorInt> Monster::FindPath(VectorInt goal, const CubeRef currentCube)
{
	// 길찾기에 필요한 자료구조 선언
	auto cmp = [](TileNode* a, TileNode* b) { return a->f > b->f; };
	std::priority_queue<TileNode*, std::vector<TileNode*>, decltype(cmp)> openList(cmp);
	std::unordered_map<VectorInt, TileNode*, VectorIntHash> allNodes;

	VectorInt startWP = { _pos.x, _pos.y, _pos.z };
	VectorInt goalWP = { goal.x, goal.y, goal.z };

	// 2. 시작 노드 설정 (현재 방 기준)
	VectorInt startIdx = WorldToLocalIndex(startWP, currentCube);
	float startH = GetDistance(startWP, goalWP) / TileSize;
	TileNode* startNode = new TileNode{ startWP, startIdx, 0, startH, startH, nullptr };

	openList.push(startNode);
	allNodes[startWP] = startNode;

	int loopCount = 0;
	while (!openList.empty()) {
		TileNode* currentNode = openList.top();
		openList.pop();

		loopCount++;
		if (loopCount > 3000) break; // 무한 루프 방지 안전장치

		// 목적지 도착 확인 (TileSize 오차 범위 내)
		if (abs(currentNode->pos.x - goalWP.x) < TileSize && abs(currentNode->pos.y - goalWP.y) < TileSize) {
			std::deque<VectorInt> path = ReconstructPath(currentNode);
			for (auto& pair : allNodes) delete pair.second; // 메모리 해제
			return path;
		}

		// 3. 8방향 탐색 시작
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;

				// 차기 탐색 지점 (월드 좌표)
				VectorInt nextWP = {
					currentNode->pos.x + dx * TileSize,
					currentNode->pos.y + dy * TileSize,
					currentNode->pos.z
				};

				// [핵심] 4. 현재 좌표가 어느 방에 속하는지 실시간 탐색 (옆방 확장)
				CubeRef targetCube = FindCubeAtWorldPos(nextWP, currentCube);

				// 어느 방에도 속하지 않으면 (진짜 맵 밖이면) 스킵
				if (targetCube == nullptr) continue;

				// 5. 해당 방의 타일맵 데이터 확인 (회전 변환 포함)
				VectorInt localIdx = WorldToLocalIndex(nextWP, targetCube);
				if (!IsWalkable(targetCube, localIdx)) continue;

				// 6. A* 노드 갱신 로직
				float moveCost = (dx != 0 && dy != 0) ? 1.414f : 1.0f;
				float g = currentNode->g + moveCost;

				if (allNodes.count(nextWP) && allNodes[nextWP]->g <= g) continue;

				float h = GetDistance(nextWP, goalWP) / TileSize;
				float f = g + h;

				if (allNodes.count(nextWP)) {
					allNodes[nextWP]->g = g;
					allNodes[nextWP]->f = f;
					allNodes[nextWP]->parent = currentNode;
				}
				else {
					TileNode* newNode = new TileNode{ nextWP, localIdx, g, h, f, currentNode };
					allNodes[nextWP] = newNode;
					openList.push(newNode);
				}
			}
		}
	}

	// 실패 시 메모리 해제 및 빈 경로 반환
	for (auto& pair : allNodes) delete pair.second;
	return {};
}

//std::deque<VectorInt> Monster::FindPath(VectorInt goal, const CubeRef currentCube)
//{
//	// 현재 위치한 방의 타일맵 가져오기
//	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetCubeType());
//
//	// 타일맵의 시작점 계산(FrontLeftButtom)
//	VectorInt cubePos = currentCube->GetPos();
//	VectorInt cubeSize = currentCube->GetSize();
//	VectorInt tilemapStart{ cubePos.x - cubeSize.x / 2, cubePos.y - cubeSize.y / 2, cubePos.z };
//	// CubeType에 따라 보정
//	switch (currentCube->GetCubeType())
//	{
//	case CubeType::GapRoom:	// 입구가 2층
//	case CubeType::RailCatwalk:
//	case CubeType::StorageRoom_Step:
//	case CubeType::CabinetRoom:
//	case CubeType::FactoryRoom:
//		tilemapStart.z -= 600;
//		break;
//	}
//
//	// 시작 위치와 목적지의 인덱스 계산
//	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };
//	VectorInt startIndex = (_pos - tilemapStart) / TileSize;
//	VectorInt goalIndex = (goal - tilemapStart) / TileSize; 
//
//	// Cube 방향에 따라 인덱스 변환
//	switch (currentCube->GetDir())
//	{
//	case Right:
//		startIndex = { startIndex.y, max.x - 1 - startIndex.x, startIndex.z };
//		goalIndex = { goalIndex.y, max.x - 1 - goalIndex.x, goalIndex.z };
//		break;
//	case Back:
//		startIndex = { max.x - 1 - startIndex.x, max.y - 1 - startIndex.y, startIndex.z };
//		goalIndex = { max.x - 1 - goalIndex.x, max.y - 1 - goalIndex.y, goalIndex.z };
//		break;
//	case Left:
//		startIndex = { max.y - 1 - startIndex.y, startIndex.x, startIndex.z };
//		goalIndex = { max.y - 1 - goalIndex.y, goalIndex.x, goalIndex.z };
//		break;
//	}
//
//	// 길찾기에 사용할 임시 BoundingBox
//	BoundingBox box = _box;
//
//	// 길찾기에 필요한 자료구조 정의
//	auto cmp = [](TileNode* a, TileNode* b) { return a->f > b->f; };
//	std::priority_queue<TileNode*, std::vector<TileNode*>, decltype(cmp)> openList(cmp);
//	std::unordered_map<VectorInt, TileNode*, VectorIntHash> openMap;
//	std::unordered_set<VectorInt, VectorIntHash> closeList;
//
//	// openList에 시작 노드 추가
//	// 유클리드 거리로 휴리스틱 계산
//	float startH = sqrt((_pos.x - goal.x)* (_pos.x - goal.x) + (_pos.y - goal.y) * (_pos.y - goal.y) + (_pos.z - goal.z) * (_pos.z - goal.z));
//	TileNode* startNode = new TileNode{ startIndex, 0, startH, startH, nullptr };
//	openList.push(startNode);
//	openMap[startIndex] = startNode;
//
//	while (!openList.empty())
//	{
//		// openList에서 f값이 가장 작은 노드 꺼내기
//		TileNode* currentNode = openList.top();
//		openList.pop();
//		openMap.erase(currentNode->index);
//
//		// 현재 노드와 연결된 모든 노드 확인
//		// 상하좌우 대각선
//		for (int x = currentNode->index.x - 1; x <= currentNode->index.x + 1; ++x)
//		{
//			for (int y = currentNode->index.y - 1; y <= currentNode->index.y + 1; ++y)
//			{
//				VectorInt connectedIndex{ x, y, currentNode->index.z };
//
//				// 현재 노드는 제외
//				if (connectedIndex == currentNode->index)
//					continue;
//
//				// 목적지 노드라면 경로	반환
//				if (connectedIndex.x == goalIndex.x && connectedIndex.y == goalIndex.y)
//				{
//					std::deque<VectorInt> path;
//					path.push_back(tilemapStart + goalIndex * TileSize);
//					TileNode* node = currentNode;
//					while (node)
//					{
//						path.push_back(tilemapStart + node->index * TileSize);
//						node = node->parent;
//					}
//					std::reverse(path.begin(), path.end());
//					return path;
//				}
//
//				// 갈 수 있는 노드인지 확인
//				bool canGo = true;
//				// 나중에 이동 방향에 따라 Dir 수정하기
//				box.SetOwnerPos(tilemapStart + connectedIndex * TileSize, Front);
//				const std::array<Vector, CornerCount>& corners = box.GetCorners();
//				for (const auto& corner : corners)
//				{
//					VectorInt index = (corner - tilemapStart) / TileSize;
//
//					// Cube 방향에 따라 인덱스 변환
//					switch (currentCube->GetDir())
//					{
//					case Right:
//						index = { index.y, max.x - 1 - index.x, index.z };
//						break;
//					case Back:
//						index = { max.x - 1 - index.x, max.y - 1 - index.y, index.z };
//						break;
//					case Left:
//						index = { max.y - 1 - index.y, index.x, index.z };
//						break;
//					}
//
//					// 현재 있는 Cube의 Tilemap 안에 Index가 포함되지 않으면, 연결된 Cube들도 확인
//					if (index < Vector{ 0, 0, 0 } || index >= max)
//					{
//						std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
//						for (const auto& cube : connectedCubes)
//						{
//							VectorInt otherCubePos = cube->GetPos();
//							VectorInt otherCubeSize = cube->GetSize();
//							VectorInt otherstart{ otherCubePos.x - otherCubeSize.x / 2, otherCubePos.y - otherCubeSize.y / 2, otherCubePos.z };
//							switch (cube->GetCubeType())
//							{
//							case CubeType::GapRoom:	// 입구가 2층
//							case CubeType::RailCatwalk:
//							case CubeType::StorageRoom_Step:
//							case CubeType::CabinetRoom:
//							case CubeType::FactoryRoom:
//								otherstart.z -= 600;
//								break;
//							}
//
//							// 다른 타일맵에서의 Index 계산
//							const std::vector<std::vector<std::vector<short>>> otherTilemap = g_dataManager->GetTilemap(cube->GetCubeType());
//							VectorInt otherMax{ otherTilemap[0][0].size(), otherTilemap[0].size(), otherTilemap.size() };
//							VectorInt otherIndex = (corner - otherstart) / TileSize;
//
//							// Cube 방향에 따라 인덱스 변환
//							switch (cube->GetDir())
//							{
//							case Right:
//								otherIndex = { otherIndex.y, otherMax.x - 1 - otherIndex.x, otherIndex.z };
//								break;
//							case Back:
//								otherIndex = { otherMax.x - 1 - otherIndex.x, otherMax.y - 1 - otherIndex.y, otherIndex.z };
//								break;
//							case Left:
//								otherIndex = { otherMax.y - 1 - otherIndex.y, otherIndex.x, otherIndex.z };
//								break;
//							}
//
//							// 연결된 큐브에 포함되지 않으면 일단 갈 수 없음으로 간주
//							if (otherIndex < Vector{ 0, 0, 0 } || otherIndex >= otherMax)
//							{
//								canGo = false;
//								continue;
//							}
//
//							// 하나의 모서리라도 갈 수 없는 곳에 위치하면 이동 불가능, 노드 제외
//							if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 0)
//							{
//								canGo = false;
//								break;
//							}
//
//							// 갈 수 있는 큐브 찾으면 flag 값 바꾸기
//							if (otherTilemap[otherIndex.z][otherIndex.y][otherIndex.x] == 1)
//								canGo = true;
//						}
//					
//						if (!canGo)
//							break;
//					}
//					else if (tilemap[index.z][index.y][index.x] == 0)
//					{
//						// 해당 위치가 갈 수 없는 곳이면 이동 불가능, 노드 제외
//						canGo = false;
//						break;
//					}
//				}
//
//				// 갈 수 없는 노드면 제외
//				if (!canGo)
//					continue;
//
//				// 이미 closeList에 있으면 무시
//				if (closeList.find(connectedIndex) != closeList.end())
//					continue;
//
//				float g = currentNode->g + 1;
//				VectorInt connectedPos = tilemapStart + connectedIndex * TileSize;
//				float h = sqrt((connectedPos.x - goal.x) * (connectedPos.x - goal.x) + (connectedPos.y - goal.y) * (connectedPos.y - goal.y) + (connectedPos.z - goal.z) * (connectedPos.z - goal.z));
//				float f = g + h;
//
//				// 이미 openList에 있을때
//				if (openMap.find(connectedIndex) != openMap.end())
//				{
//					// 더 나은 경로가 발견되면 갱신
//					if (openMap[connectedIndex]->f > f)
//					{
//						TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
//						openList.push(newNode);
//						openMap[connectedIndex] = newNode;
//					}
//
//					continue;
//				}
//
//				// 두 List에 모두 없으면 openList에 추가
//				TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
//				openList.push(newNode);
//				openMap[connectedIndex] = newNode;
//			}
//		}
//		
//		// 확인한 노드는 closeList에 추가
//		closeList.insert(currentNode->index);
//	}
//
//	return {};
//}

VectorInt Monster::WorldToLocalIndex(VectorInt wp, CubeRef cube)
{
	VectorInt cubePos = cube->GetPos();
	VectorInt cubeSize = cube->GetSize();

	// 1. 월드 시작점 계산
	int minX = cubePos.x - (cubeSize.x / 2);
	int minY = cubePos.y - (cubeSize.y / 2);
	int minZ = cubePos.z;

	auto type = cube->GetCubeType();
	if (type == CubeType::GapRoom || type == CubeType::RailCatwalk ||
		type == CubeType::StorageRoom_Step || type == CubeType::CabinetRoom ||
		type == CubeType::FactoryRoom)
	{
		minZ -= 600;
	}

	// 2. 타일맵 데이터 크기 확인
	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	int maxZ = (int)tilemap.size();
	int maxY = (int)tilemap[0].size();
	int maxX = (int)tilemap[0][0].size();

	// 3. 인덱스 계산 (소수점 버림)
	int tx = (wp.x - minX) / TileSize;
	int ty = (wp.y - minY) / TileSize;
	int tz = (wp.z - minZ) / TileSize;

	// 5. 회전 방향에 따른 축 변환 (수정된 로직)
	VectorInt result;
	switch (cube->GetDir()) {
	case Right: result = { ty, maxX - 1 - tx, tz }; break;
	case Back:  result = { maxX - 1 - tx, maxY - 1 - ty, tz }; break;
	case Left:  result = { maxY - 1 - ty, tx, tz }; break;
	default:    result = { tx, ty, tz }; break; // Front
	}

	result.x = std::clamp(result.x, 0, maxX - 1);
	result.y = std::clamp(result.y, 0, maxY - 1);
	result.z = std::clamp(result.z, 0, maxZ - 1);

	return result;
}

bool Monster::IsWalkable(CubeRef cube, VectorInt localIdx)
{
	// 1. 타일맵 데이터 가져오기
	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());

	// 2. 실제 데이터의 크기 확인 (이게 핵심)
	int maxZ = (int)tilemap.size();
	if (maxZ == 0) return false;

	int maxY = (int)tilemap[0].size();
	if (maxY == 0) return false;

	int maxX = (int)tilemap[0][0].size();

	// 3. 인덱스가 실제 배열 크기를 벗어나는지 최종 체크
	if (localIdx.z < 0 || localIdx.z >= maxZ ||
		localIdx.y < 0 || localIdx.y >= maxY ||
		localIdx.x < 0 || localIdx.x >= maxX)
	{
		//// 여기서 터지기 직전 상황임. 로그 출력.
		//printf("[Error] Index Out of Range! Cube: %d, Idx: (%d, %d, %d), MapSize: (%d, %d, %d)\n",
		//	(int)cube->GetCubeType(), localIdx.x, localIdx.y, localIdx.z, maxX, maxY, maxZ);
		return false; // 터지는 대신 그냥 못 가는 길로 판정
	}

	// 4. 안전함이 확인된 후 데이터 참조
	return tilemap[localIdx.z][localIdx.y][localIdx.x] == 1;
}

CubeRef Monster::FindCubeAtWorldPos(VectorInt wp, CubeRef currentCube)
{
	if (IsPointInCube(wp, currentCube)) return currentCube;

	// 현재 방 밖이라면 연결된 방들 전수 조사
	for (auto& adj : currentCube->GetConnectedCubes()) {
		if (IsPointInCube(wp, adj)) 
			return adj;
	}
	return nullptr;
}

bool Monster::IsPointInCube(VectorInt wp, CubeRef cube)
{
	VectorInt pos = cube->GetPos();
	VectorInt size = cube->GetSize();
	// 단순 AABB 체크
	return (wp.x >= pos.x - size.x / 2 && wp.x <= pos.x + size.x / 2 &&
		wp.y >= pos.y - size.y / 2 && wp.y <= pos.y + size.y / 2);
}

std::deque<VectorInt> Monster::ReconstructPath(TileNode* goalNode)
{
	std::deque<VectorInt> path;
	TileNode* curr = goalNode;

	// 1. 부모 노드를 따라가며 좌표를 수집 (목적지 -> 시작점 순서)
	while (curr != nullptr)
	{
		// VectorInt 형태로 월드 좌표 저장
		path.push_back({ curr->pos.x, curr->pos.y, curr->pos.z });
		curr = curr->parent;
	}

	// 2. 수집된 경로는 목적지부터 시작점까지 역순이므로, 다시 뒤집어줌
	std::reverse(path.begin(), path.end());

	// 3. (선택 사항) 시작 위치는 이미 몬스터가 서 있는 곳이므로 제거하기도 함
	// if (!path.empty()) path.pop_front();

	return path;
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