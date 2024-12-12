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

	// ��� �浹�� ��ȸ
	for (int32 i = 0; i < colliders.size(); i++)
	{
		Collider* src = colliders[i];
		Vec2 pos = src->GetPos();

		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		Vec2Int winSize = GET_SINGLE(ValueManager)->GetWinSize();

		// ī�޶� ���� ���ϱ�
		int32 leftX = (int32)cameraPos.x - winSize.x / 2;
		int32 leftY = (int32)cameraPos.y - winSize.y / 2;
		int32 rightX = (int32)cameraPos.x + winSize.x / 2;
		int32 rightY = (int32)cameraPos.y + winSize.y / 2;

		RECT rect = { leftX, leftY, rightX, rightY };

		// ī�޶� ������ ������ �ǳʶٱ�
		if (!::PtInRect(&rect, { (int32)pos.x, (int32)pos.y }))
			continue;
		
		// ������ �� �ڿ� �ִ� �͵��� ��ȸ
		for (int32 j = i + 1; j < colliders.size(); j++)
		{
			Collider* dest = colliders[j];

			// �浹�Ѵٸ�
			if (src->CheckCollision(dest))
			{
				if (src->_collisionMap.contains(dest) == false)
				{
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
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
