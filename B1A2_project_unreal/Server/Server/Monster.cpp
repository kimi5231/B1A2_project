#include "pch.h"
#include "Monster.h"
#include "Global.h"
#include "Room.h"
#include "Cube.h"
#include "DataManager.h"
#include "FSM.h"
#include "Door.h"
#include "State.h"
#include "Player.h"

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

	_size = { 80, 80, 80 };
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

	//// 목적지 갱신
	//if (_targetPos == nullptr)
	//{
	//	// 목적지 설정
	//	CubeRef goalCube = SelectRandomConnectedCube(room);
	//	// 최종 목적지 기록
	//	_targetPos = new Vector( goalCube->GetPos().x, goalCube->GetPos().y, _pos.z );

	//	// 1차 길찾기
	//	_cubePath = FindCubePath(goalCube, currentCube, cubes);
	//}

	//// 경로 갱신
	//if (_path.empty())
	//{
	//	if (_cubePath.size() == 1)
	//	{
	//		_targetPos = nullptr;
	//		return;
	//	}

	//	// 넘어갈 큐브와 연결된 문 찾기
	//	DoorRef door;
	//	for (uint& doorID : _cubePath[0]->GetDoors())
	//	{
	//		if (doors[doorID - 1]->GetConnectedCubeID() == _cubePath[1]->GetID() ||
	//			doors[doorID - 1]->GetRoomID() == _cubePath[1]->GetID())
	//		{
	//			door = doors[doorID - 1];
	//			break;
	//		}
	//	}

	//	// 지나갈 문이 닫혀있으면 문 앞까지만 경로 찾기
	//	if (door->GetState() == ObjectState::CLOSE)
	//	{
	//		Vector goal;

	//		// 나중에 문이 있는 방에 따라 방향 바뀌는 거 고려할 것
	//		switch (door->GetDir())
	//		{
	//		case Front:
	//			goal = { door->GetPos().x, door->GetPos().y + _size.y / 2, _pos.z };
	//			break;
	//		case Right:
	//			goal = { door->GetPos().x - _size.x / 2, door->GetPos().y, _pos.z };
	//			break;
	//		case Back:
	//			goal = { door->GetPos().x, door->GetPos().y - _size.y / 2, _pos.z };
	//			break;
	//		case Left:
	//			goal = { door->GetPos().x + _size.x / 2, door->GetPos().y, _pos.z };
	//			break;
	//		}

	//		_path = FindPath(goal, _cubePath[0]);
	//		
	//		// 경로를 찾기 못하면 목적지 재설정
	//		if (_path.empty())
	//		{
	//			_targetPos = nullptr;
	//			return;
	//		}
	//	}

	//	// 지나갈 문이 열려 있으면 문의 좌표까지 경로 찾기
	//	if (door->GetState() == ObjectState::OPEN)
	//	{
	//		Vector goal{ _cubePath[1]->GetPos().x, _cubePath[1]->GetPos().y, _pos.z};

	//		_path = FindPath(goal, _cubePath[0]);

	//		// 경로를 찾기 못하면 목적지 재설정
	//		if (_path.empty())
	//		{
	//			_targetPos = nullptr;
	//			return;
	//		}

	//		// 지나온 큐브는 경로에서 제외
	//		_cubePath.pop_front();
	//	}
	//}

	//// 최종 목적지까지 도달했다면, 타겟 리셋
	//if (*_targetPos == _path[0])
	//	_targetPos = nullptr;

	//// 경로	따라 이동
	//SetPos(_path[0]);
	//_path.pop_front();
	//g_framework->SendMovePacket(shared_from_this(), true);
}

const CubeRef Monster::SelectRandomConnectedCube(Room* room)
{
	const std::vector<CubeRef>& cubes = room->GetCubes();
	const std::vector<Door*>& doors = room->GetDoors();
	const CubeRef currentCube = cubes[_currentCubeID];

	// 현재 위치한 방에 열린 문이 있는지 확인
	std::vector<int> openDoorCubeID;
	openDoorCubeID.reserve(currentCube->GetDoors().size());
	for (const int doorID : currentCube->GetDoors())
	{
		Door* door = doors[doorID];
		if (door->GetState() == ObjectState::OPEN)
		{
			if(door->GetConnectedCubeID() != _currentCubeID)
				openDoorCubeID.push_back(door->GetConnectedCubeID());
			else
				openDoorCubeID.push_back(door->GetRoomID());
		}
	}
	
	// 열린 문이 없으면 현재 위치한 큐브 반환
	if (openDoorCubeID.empty())
		return currentCube;

	// 열린 문이 있다면, 해당 문으로 연결된 방 중 랜덤하게 선택
	//std::vector<CubeRef>& connectedCubes = currentCube->GetConnectedCubes();
	std::uniform_int_distribution<int> selectCube(0, openDoorCubeID.size() - 1);
	return cubes[openDoorCubeID[selectCube(gen)]];
}

VectorInt Monster::SelectRandomPosInCube(const CubeRef currentCube)
{
	const std::vector<std::vector<std::vector<short>>>& tilemap = g_dataManager->GetTilemap(currentCube->GetCubeType());
	Vector cubePos = currentCube->GetPos();
	VectorInt max{ tilemap.size(), tilemap[0].size(), tilemap[0][0].size() };
	std::uniform_int_distribution<int> X(0, max.x - 1);
	std::uniform_int_distribution<int> Y(0, max.y - 1);

	VectorInt index{};
	while (!IsCanGo(index, currentCube))
	{
		int x = X(gen);
		int y = Y(gen);
		int z = _pos.z / TileSize;
		index = GetRotationIndex({ x, y, z }, max, currentCube->GetDir());
	}
	
	Vector pos = IndexToPos(index, currentCube);
	pos.z = _pos.z; // 높이는 현재 위치 유지
	return pos;
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

	// 시작 위치와 목적지의 인덱스 계산
	VectorInt startIndex = PosToIndex(_pos, currentCube);
	VectorInt goalIndex = PosToIndex(goal, currentCube);

	// openList에 시작 노드 추가
	// 맨해튼 거리로 휴리스틱 계산
	float startH = abs(startIndex.x - goalIndex.x) + abs(startIndex.y - goalIndex.y) + abs(startIndex.z - goalIndex.z);
	TileNode* startNode = new TileNode(startIndex, 0, startH, startH, nullptr);
	openList.push(startNode);
	openMap[startIndex] = startNode;

	while (!openList.empty())
	{
		// openList에서 f값이 가장 작은 노드 꺼내기
		TileNode* currentNode = openList.top();
		openList.pop();
		openMap.erase(currentNode->index);
		closeList.insert(currentNode->index);

		// 현재 노드와 연결된 모든 노드 확인
		// 상하좌우 대각선
		for (int x = -1; x <= 1; ++x)
		{
			for (int y = -1; y <= 1; ++y)
			{
				VectorInt connectedIndex{ currentNode->index.x +  x, currentNode->index.y + y, currentNode->index.z };

				// 현재 노드는 제외
				if (x == 0 && y == 0)
					continue;

				// 목적지 노드라면 경로	반환
				if (connectedIndex.x == goalIndex.x && connectedIndex.y == goalIndex.y)
				{
					std::deque<VectorInt> path;
					path.push_back(IndexToPos(goalIndex, currentCube));
					TileNode* node = currentNode;
					while (node)
					{
						path.push_back(IndexToPos(node->index, currentCube));
						node = node->parent;
					}
					std::reverse(path.begin(), path.end());
					_path = path;
					return _path;
				}

				// 이미 closeList에 있으면 무시
				if (closeList.contains(connectedIndex))
					continue;

				// 갈 수 있는 노드인지 확인
				CubeRef cube = FindCubeAtIndex(connectedIndex, currentCube);
				if (!cube)
					continue;

				VectorInt index = PosToIndex(IndexToPos(connectedIndex, currentCube), cube);
				if (!IsCanGo(index, cube) && !IsCanGo(connectedIndex, currentCube))
					continue;

				//float g = currentNode->g + ((x != 0 && y != 0) ? 1.414f : 1.0f);
				float g = currentNode->g + 1;
				float h = abs(connectedIndex.x - goalIndex.x) + abs(connectedIndex.y - goalIndex.y) + abs(connectedIndex.z - goalIndex.z);
				float f = g + h;
				
				// 이미 openList에 있지만 기존 경로가 더 낫다면 무시
				if (openMap.contains(connectedIndex) && openMap[connectedIndex]->f <= f)
					continue;
				
				// 두 List에 모두 없거나, 새로운 경로가 더 낫다면 openList에 추가
				TileNode* newNode = new TileNode{ connectedIndex, g, h, f, currentNode };
				openList.push(newNode);
				openMap[connectedIndex] = newNode;
				continue;
			}
		}
	}

	return {};
}

VectorInt Monster::GetRotationIndex(VectorInt index, VectorInt max, Dir dir)
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

VectorInt Monster::PosToIndex(Vector pos, CubeRef cube)
{
	Vector cubePos = cube->GetPos();
	Vector cubeSize = cube->GetSize();

	Vector startPos;
	switch (cube->GetDir())
	{
	case Front:
	case Back:
		startPos = { cubePos.x - (cubeSize.x / 2), cubePos.y - (cubeSize.y / 2), cubePos.z };
		break;
	case Right:
	case Left:
		startPos = { cubePos.x - (cubeSize.y / 2), cubePos.y - (cubeSize.x / 2), cubePos.z };
		break;
	}

	switch (cube->GetCubeType())
	{
	case CubeType::GapRoom:
	case CubeType::RailCatwalk:
	case CubeType::StorageRoom_Step:
	case CubeType::CabinetRoom:
	case CubeType::FactoryRoom:
		startPos.z -= 600;
		break;
	}

	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	VectorInt index = (pos - startPos)/TileSize;

	VectorInt result = index;
	switch (cube->GetDir())
	{
	case Right:
		result.x = index.y;
		result.y = (max.y - 1 - index.x);
		break;
	case Back:
		result.x = (max.x - 1 - index.x);
		result.y = (max.y - 1 - index.y);
		break;
	case Left:
		result.x = (max.x - 1 - index.y);
		result.y = index.x;
		break;
	}

	return result;
}

Vector Monster::IndexToPos(VectorInt index, const CubeRef cube)
{
	Vector cubePos = cube->GetPos();
	Vector cubeSize = cube->GetSize();

	Vector startPos;
	switch (cube->GetDir())
	{
	case Front:
	case Back:
		startPos = { cubePos.x - (cubeSize.x / 2), cubePos.y - (cubeSize.y / 2), cubePos.z };
		break;
	case Right:
	case Left:
		startPos = { cubePos.x - (cubeSize.y / 2), cubePos.y - (cubeSize.x / 2), cubePos.z };
		break;
	}

	switch (cube->GetCubeType())
	{
	case CubeType::GapRoom:
	case CubeType::RailCatwalk:
	case CubeType::StorageRoom_Step:
	case CubeType::CabinetRoom:
	case CubeType::FactoryRoom:
		startPos.z -= 600;
		break;
	}

	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	Vector pos = index;

	// Cube 방향에 따라 보정
	switch (cube->GetDir())
	{
	case Right:
		pos.x = (float)(max.y - 1 - index.y);
		pos.y = (float)index.x;
		break;
	case Back:
		pos.x = (float)(max.x - 1 - index.x);
		pos.y = (float)(max.y - 1 - index.y);
		break;
	case Left:
		pos.x = (float)index.y;
		pos.y = (float)(max.x - 1 - index.x);
		break;
	}

	pos *= TileSize;

	return startPos + pos;
}

bool Monster::IsCanGo(VectorInt index, const CubeRef cube)
{
	const auto& tilemap = g_dataManager->GetTilemap(cube->GetCubeType());
	VectorInt max{ tilemap[0][0].size(), tilemap[0].size(), tilemap.size() };

	// 인덱스가 실제 배열 크기를 벗어나는지 최종 체크
	if (index < Vector{ 0, 0, 0 } || index >= max)
		return false;

	return tilemap[index.z][index.y][index.x] == 1;
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

void Monster::UpdateNextAttackTime()
{
	auto delay = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
		std::chrono::duration<float>(_attackDelay)
	);

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
	/*case OPEN_DOOR:
		_fsm->ChangeState(_openDoor, this);
		break;*/
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