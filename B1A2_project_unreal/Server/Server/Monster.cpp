#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Cube.h"
#include "DataManager.h"
#include "FSM.h"
#include "Door.h"
#include "State.h"
#include "Player.h"
#include "Room.h"

Monster::Monster(MonsterType monsterType, Room* ownerRoom)
	: _monsterType(monsterType)
{
	// FSM 생성
	_fsm = new FSM();
	_targetPos = std::nullopt;
	_returnPos = _pos;
	_target = nullptr;
	_sumTime = 0.f;
	_ownerRoom = ownerRoom;
	_isNeedDoorOpen = false;

	_rotation = { 0, 0, 0 };
	_type = ObjectType::Monster;
	// 나중에 방향 조절하기
	_box.SetBounds(_pos, _size, Front);
} 

Monster::~Monster()
{
}

void Monster::Update(Room* room)
{
	_fsm->Update(this);
}

void Monster::UpdatePath(Vector currentGoal, CubeRef goalCube)
{
	// 최종 목적지 갱신
	if (!_targetPos)
	{
		const std::vector<CubeRef>& cubes = _ownerRoom->GetCubes();
		const CubeRef currentCube = cubes[_currentCubeID];
		// 같은 큐브에 있다면 target의 위치로 바로 경로 갱신
		if (goalCube == currentCube)
		{
			FindPath(currentGoal, currentCube);
			SetTargetPos(currentGoal);
		}
		else // 목적 큐브까지 1차 경로 찾기
			FindCubePath(goalCube, currentCube, cubes);
	}

	// 2차 경로 갱신
	if (GetPath().empty())
	{
		std::deque<CubeRef>& cubePath = GetCubePath();
		// 최종 목적지까지 더 이동할 큐브가 없다면 목적지 재설정
		if (cubePath.size() <= 1)
		{
			SetTargetPos(std::nullopt);
			return;
		}

		// 넘어갈 큐브와 연결된 문 찾기
		const std::vector<Door*>& doors = _ownerRoom->GetDoors();
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

		// 문을 찾지 못했다면 목적지 재설정
		if (!door)
		{
			SetTargetPos(std::nullopt);
			return;
		}

		// 지나갈 문이 닫혀있으면 문 앞까지만 경로 찾기
		if (door->GetState() == ObjectState::CLOSE || door->GetState() == ObjectState::LOCK)
		{
			Vector doorPos = door->GetPos();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
			case Back:
				if (doorPos.y < _pos.y)
					goal = { doorPos.x, doorPos.y + _size.y / 2, doorPos.z + TileSize };
				else
					goal = { doorPos.x, doorPos.y - _size.y / 2, doorPos.z + TileSize };
				break;
			case Right:
			case Left:
				if (doorPos.x < _pos.x)
					goal = { doorPos.x + _size.x / 2, doorPos.y, doorPos.z + TileSize };
				else
					goal = { doorPos.x - _size.x / 2, doorPos.y, doorPos.z + TileSize };
				break;
			}

			if ((goal - _pos).Length() > TileSize * 2)
			{
				// 경로를 찾기 못하면 목적지 재설정
				if (FindPath(goal, cubePath[0]).empty())
				{
					SetTargetPos(std::nullopt);
					return;
				}
				SetTargetPos(goal);
			}

			// Hatch는 제외
			if (door->GetDoorType() == DoorType::Hatch)
				return;

			SetTargetDoor(door);
			SetIsNeedDoorOpen(true);
		}

		// 지나갈 문이 열려 있으면 문 너머 좌표까지 경로 찾기
		if (door->GetState() == ObjectState::OPEN)
		{
			Vector doorPos = door->GetPos();
			Vector goal;

			switch (door->GetDir())
			{
			case Front:
			case Back:
				if (doorPos.y < _pos.y)
					goal = { doorPos.x, doorPos.y - _size.y, doorPos.z + TileSize };
				else
					goal = { doorPos.x, doorPos.y + _size.y, doorPos.z + TileSize };
				break;
			case Right:
			case Left:
				if (doorPos.x < _pos.x)
					goal = { doorPos.x - _size.x, doorPos.y, doorPos.z + TileSize };
				else
					goal = { doorPos.x + _size.x, doorPos.y, doorPos.z + TileSize };
				break;
			}

			// 경로를 찾기 못하면 목적지 재설정
			if (FindPath(goal, cubePath[0]).empty())
			{
				SetTargetPos(std::nullopt);
				return;
			}

			// 지나온 큐브는 경로에서 제외
			cubePath.pop_front();
		}
	}
}

void Monster::Move(float speed, ObjectState state)
{
	std::deque<VectorInt>& path = GetPath();
	if (!path.empty())
	{
		// 방향, 거리 계산
		Vector dir = path[0] - _pos;
		float distance = dir.Length();

		// 이동 속도 적용
		float moveDist = speed * _ownerRoom->GetUpdateMonsterTime();

		// 남은 거리가 이동할 거리보다 목적지 위치로 바로 이동
		if (distance <= moveDist)
		{
			SetPos(path[0]);
			path.pop_front();

			// Chase일 때만 실시간 경로 갱신
			if (state == ObjectState::CHASE)
				SetTargetPos(std::nullopt);
		}
		else
		{
			// 이동 방향 계산
			dir.Normalize();
			float angle = std::atan2(dir.y, dir.x) * (180.0f / 3.14159265f);

			float currentAngle = _rotation.yaw;

			// 각도가 -180도 ~ 180도 사이에서 튈 수 있으므로 최단 거리 회전 보정
			float angleDiff = angle - currentAngle;
			while (angleDiff < -180.0f) angleDiff += 360.0f;
			while (angleDiff > 180.0f)  angleDiff -= 360.0f;

			// 회전 속도 설정 (숫자가 클수록 빠르게 회전, 5.0f~10.0f 정도가 적당해)
			float rotationSpeed = 8.0f;
			float nextAngle = currentAngle + angleDiff * rotationSpeed * _ownerRoom->GetUpdateMonsterTime();

			// 3. 보정된 회전값 적용
			Rotation rotation = { 0.f, nextAngle, 0.f };

			_rotation = rotation;
			SetPos(_pos + (dir * moveDist));
		}

		// 몬스터 이동 알리기
		for (auto& p : _ownerRoom->GetPlayers())
		{
			if (!p->GetClient())
				continue;

			g_network->SendMovePacket(this, p->GetClient());
		}
	}

	// 최종 목적지까지 도달했다면, 목적지 재설정
	if (path.empty())
	{
		SetTargetPos(std::nullopt);
		if (GetIsNeedDoorOpen())
		{
			GetTargetDoor()->SetState(ObjectState::OPEN);

			for (auto& p : GetOwnerRoom()->GetPlayers())
			{
				if (!p->GetClient())
					continue;

				g_network->SendUpdateObjectStatePacket(GetTargetDoor(), p->GetClient());
			}

			SetTargetDoor(nullptr);
			SetIsNeedDoorOpen(false);
		}
	}
}

const CubeRef Monster::SelectRandomConnectedCube()
{
	//const std::vector<CubeRef>& cubes = _ownerRoom->GetCubes();
	//const std::vector<Door*>& doors = _ownerRoom->GetDoors();
	//const CubeRef currentCube = cubes[_currentCubeID];

	//// 연결된 Cube 중 열린 문이 있는 CubeID만 저장
	//std::vector<int> openDoorCubeID;
	//openDoorCubeID.reserve(currentCube->GetDoors().size());
	//for (const int doorID : currentCube->GetDoors())
	//{
	//	Door* door = doors[doorID];
	//	if (door->GetState() == ObjectState::OPEN)
	//	{
	//		if (door->GetConnectedCubeID() != _currentCubeID)
	//			openDoorCubeID.push_back(door->GetConnectedCubeID());
	//		else
	//			openDoorCubeID.push_back(door->GetOwnerCubeID());
	//	}
	//}

	//// 열린 문이 없다면 현재 Cube 반환
	//if (openDoorCubeID.empty())
	//	return currentCube;

	//// 열린 문이 있다면 랜덤으로 선택
	//std::uniform_int_distribution<int> selectCube(0, openDoorCubeID.size() - 1);
	//return cubes[openDoorCubeID[selectCube(gen)]];

	const std::vector<CubeRef>& cubes = _ownerRoom->GetCubes();
	const CubeRef currentCube = cubes[_currentCubeID];
	const std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();

	// 열린 문이 있다면 랜덤으로 선택
	std::uniform_int_distribution<int> selectCube(0, connectedCubes.size() - 1);
	return connectedCubes[selectCube(gen)];
}

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
				_cubePath = path;
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

std::deque<VectorInt> Monster::FindPath(Vector goal, const CubeRef currentCube)
{
	// 길찾기에 필요한 자료구조 정의
	auto cmp = [](TileNode* a, TileNode* b) { return a->f > b->f; };
	std::priority_queue<TileNode*, std::vector<TileNode*>, decltype(cmp)> openList(cmp);
	std::unordered_map<VectorInt, TileNode*, VectorIntHash> openMap;
	std::unordered_set<VectorInt, VectorIntHash> closeList;

	std::vector<TileNode*> allocatedNodes;

	// 시작 위치와 목적지의 인덱스 계산
	VectorInt startIndex = PosToIndex(_pos, currentCube);
	VectorInt goalIndex = PosToIndex(goal, currentCube);

	// openList에 시작 노드 추가
	// 맨해튼 거리로 휴리스틱 계산
	float startH = abs(startIndex.x - goalIndex.x) + abs(startIndex.y - goalIndex.y) + abs(startIndex.z - goalIndex.z);
	TileNode* startNode = new TileNode(startIndex, 0, startH, startH, nullptr);
	openList.push(startNode);
	openMap[startIndex] = startNode;
	allocatedNodes.push_back(startNode);

	// 평면 4방향 오프셋 (우, 좌, 상, 하)
	const int dx[4] = { 1, -1, 0, 0 };
	const int dy[4] = { 0, 0, 1, -1 };

	// 오르내릴 수 있는 Z축 3개 층 오프셋 (현재층, 윗층, 아랫층)
	const int dz[5] = { 0, 1, 2, -1, -2 };

	while (!openList.empty())
	{
		// openList에서 f값이 가장 작은 노드 꺼내기
		TileNode* currentNode = openList.top();
		openList.pop();
		openMap.erase(currentNode->index);
		closeList.insert(currentNode->index);

		// 현재 노드와 연결된 노드 확인
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				int nextX = currentNode->index.x + dx[i];
				int nextY = currentNode->index.y + dy[i];
				int nextZ = currentNode->index.z + dz[j];

				VectorInt connectedIndex{ nextX, nextY, nextZ };

				// 이미 closeList에 있으면 무시
				if (closeList.contains(connectedIndex))
					continue;

				// 목적지 노드인지 먼저 확인 (Z축 높이까지 일치하는지 체크)
				if (connectedIndex.x == goalIndex.x && connectedIndex.y == goalIndex.y && connectedIndex.z == goalIndex.z)
				{
					std::deque<VectorInt> path;
					TileNode* node = currentNode;
					while (node != startNode)
					{
						Vector worldPos = IndexToPos(node->index, currentCube);
						path.push_back(worldPos);
						node = node->parent;
					}
					std::reverse(path.begin(), path.end());
					_path = path;

					// 메모리 해제 후 경로 반환
					for (TileNode* allocated : allocatedNodes)
						delete allocated;
					
					return _path;
				}

				// Index가 소속된 Cube 찾기
				CubeRef cube = FindCubeAtIndex(connectedIndex, currentCube);
				if (!cube)
					continue;

				VectorInt index = PosToIndex(IndexToPos(connectedIndex, currentCube), cube);
				if (!IsCanGo(index, cube) && !IsCanGo(connectedIndex, currentCube))
					continue;

				// 이동 비용 계산
				float moveCost = (dz[j] != 0) ? 1.414f : 1.0f;
				float g = currentNode->g + moveCost;
				float h = abs(connectedIndex.x - goalIndex.x) + abs(connectedIndex.y - goalIndex.y) + abs(connectedIndex.z - goalIndex.z);
				float f = g + h;

				// 이미 openList에 있지만 기존 경로가 더 낫다면 무시
				if (openMap.contains(connectedIndex) && openMap[connectedIndex]->f <= f)
					continue;

				// 두 List에 모두 없거나, 새로운 경로가 더 낫다면 openList에 추가
				TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
				openList.push(newNode);
				openMap[connectedIndex] = newNode;
				allocatedNodes.push_back(newNode);
			}
		}
	}
	
	for (TileNode* allocated : allocatedNodes)
		delete allocated;

	return {};
}

VectorInt Monster::RotateIndexByDir(VectorInt index, VectorInt max, Dir dir)
{
	switch (dir)
	{
	case Right:
		index.x = (max.x - 1 - index.y);
		index.y = index.x;
		break;
	case Back:
		index.x = (max.x - 1 - index.x);
		index.y = (max.y - 1 - index.y);
		break;
	case Left:
		index.x = index.y;
		index.y = (max.y - 1 - index.x);
		break;
	}

	return index;
}

bool Monster::IsCanGo(VectorInt index, const CubeRef cube)
{
	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	// 인덱스가 실제 배열 크기를 벗어나는지 최종 체크
	if (index < Vector{ 0, 0, 0 } || index >= max)
		return false;

	return tilemap[index.z][index.y][index.x] == 1 && (tilemap[index.z - 1][index.y][index.x] == 0 || tilemap[index.z - 1][index.y][index.x] == 2);
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

CubeRef Monster::FindCubeAtIndex(VectorInt index, CubeRef currentCube)
{
	Vector pos = IndexToPos(index, currentCube);

	// currentCube에 속해있지 않다면 연결된 Cube 확인
	for (const CubeRef cube : currentCube->GetConnectedCubes())
	{
		if (cube->GetBoundingBox().CheckInclude(pos))
			return cube;
	}

	if (currentCube->GetBoundingBox().CheckInclude(pos))
		return currentCube;

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

void Monster::AddDeltaTime()
{
	_sumTime += _ownerRoom->GetUpdateMonsterTime();
}

void Monster::UpdateNextAttackTime()
{
	auto delay = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<float>(_attackDelay));

	_nextAttackTime = std::chrono::steady_clock::now() + delay;
}

bool Monster::SetState(ObjectState state, bool isSend)
{
	if(!Creature::SetState(state, isSend))
		return false;

	switch (state)
	{
	case IDLE:
		_fsm->ChangeState(g_idleState, this);
		break;
	case ROAMING:
		_fsm->ChangeState(g_roamingState, this);
		break;
	case CHASE:
		_fsm->ChangeState(g_chaseState, this);
		break;
	case ATTACK:
		_fsm->ChangeState(g_attackState, this);
		break;
	case HIT:
		_fsm->ChangeState(g_hitState, this);
		break;
	case DEAD:
		_fsm->ChangeState(g_deadState, this);
		break;
	}

	return true;
}