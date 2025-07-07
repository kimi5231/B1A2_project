#include "pch.h"
#include "CollisionManager.h"
#include "ValueManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init()
{
}

void CollisionManager::Update()
{
	std::vector<Collider*>& colliders = _colliders;

	// 모든 충돌을 순회
	for (int32 i = 0; i < colliders.size(); i++)
	{
		Collider* src = colliders[i];

		if (src->GetCollisionLayer() == CLT_GROUND || src->GetCollisionLayer() == CLT_WALL)
		{
			Vec2 pos = src->GetPos();

			Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
			Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

			// 카메라 영역 구하기
			int32 leftX = (int32)cameraPos.x - winSize.x / 2;
			int32 leftY = (int32)cameraPos.y - winSize.y / 2;
			int32 rightX = (int32)cameraPos.x + winSize.x / 2;
			int32 rightY = (int32)cameraPos.y + winSize.y / 2;

			RECT rect = { leftX, leftY, rightX, rightY };

			// 카메라에 보이지 않으면 건너뛰기
			if (!::PtInRect(&rect, { (int32)pos.x, (int32)pos.y }))
				continue;
		}
			
		// 나보다 더 뒤에 있는 것들을 순회
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* dest = colliders[j];

			// 충돌한다면
			if (src->CheckCollision(dest))
			{
				// 충돌 진행중
				if (src->_collisionMap.contains(dest))
				{
					src->GetOwner()->OnComponentOverlapping(src, dest);
					dest->GetOwner()->OnComponentOverlapping(dest, src);
				}

				// 최초 충돌
				if (src->_collisionMap.contains(dest) == false)
				{
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
				}
			}
			else
			{
				if (src->_collisionMap.contains(dest))
				{
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}

void CollisionManager::ClearColliders()
{
	_colliders.clear();
}
