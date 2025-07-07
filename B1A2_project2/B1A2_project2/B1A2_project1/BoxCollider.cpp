#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "SceneManager.h"
#include "ValueManager.h"
#include "Actor.h"
#include "TilemapActor.h"
#include "Monster.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Player.h"
#include "ZipLine.h"
#include "FootHold.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::BeginPlay()
{
	Super::BeginPlay();

	if (!dynamic_cast<TilemapActor*>(GetOwner()))
		_pos = GetOwner()->GetPos();
	
	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());
		Vec2Int playerDetection = owner->GetPlayerDetection();

		if(owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + playerDetection.x / 2;
		else
			_pos.x = owner->GetPos().x - playerDetection.x / 2;
	}
	else if (GetCollisionLayer() == CLT_MONSTER_ATTACK && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + 30;
		else
			_pos.x = owner->GetPos().x - 30;
	}
	else if (GetCollisionLayer() == CLT_FINAL_BOSS_SLASH && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());

		_pos = GetOwner()->GetPos();
	}
	
	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Player*>(GetOwner()))
	{
		Player* owner = dynamic_cast<Player*>(GetOwner());
		int32 monsterDetection = owner->GetAtkRange();

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + monsterDetection;
		else
			_pos.x = owner->GetPos().x - monsterDetection;
	}

	if (GetCollisionLayer() == CLT_PLAYER_ATTACK && dynamic_cast<Player*>(GetOwner()))
	{
		Player* owner = dynamic_cast<Player*>(GetOwner());

		_pos.y -= 20;

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + 20;
		else
			_pos.x = owner->GetPos().x - 20;
	}

	if (GetCollisionLayer() == CLT_STRUCTURE_DETECT && dynamic_cast<ZipLine*>(GetOwner()))
	{
		ZipLine* owner = dynamic_cast<ZipLine*>(GetOwner());
		Player* player = dynamic_cast<Player*>(owner->GetPlayer());

		if (player->GetState() == HANG)	// Player를 따라감
		{
			owner->GetPlayerDetectCollider()->SetPos({ player->GetPos() });
		}
		else if (player->GetState() == RELEASE)
		{
			_pos = owner->GetMidPos();
		}
		else
		{
			if (owner->GetMidPos().x == 0 && owner->GetMidPos().y == 0)		// 초기 위치
				_pos = owner->GetBeginPos();
			else  // 중간 하차 후 위치 유지
				_pos = owner->GetMidPos();
		}
	}

	if (_isManual && GetCollisionLayer() == CLT_GROUND)		// Foothold의 Collider 중 아래 발판
	{
		FootHold* footHold = dynamic_cast<FootHold*>(GetOwner());

		_pos.y = footHold->GetPos().y + 40;
	}
}

void BoxCollider::TickComponent()
{
	Super::TickComponent();

	if (!dynamic_cast<TilemapActor*>(GetOwner()))
		_pos = GetOwner()->GetPos();

	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());
		Vec2Int playerDetection = owner->GetPlayerDetection();
		
		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + playerDetection.x / 2;
		else
			_pos.x = owner->GetPos().x - playerDetection.x / 2;
	}
	else if (GetCollisionLayer() == CLT_MONSTER_ATTACK && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + 30;
		else
			_pos.x = owner->GetPos().x - 30;
	}
	else if (GetCollisionLayer() == CLT_FINAL_BOSS_SLASH && dynamic_cast<Monster*>(GetOwner()))
	{
		Monster* owner = dynamic_cast<Monster*>(GetOwner());

		_pos = GetOwner()->GetPos();
	}

	if (GetCollisionLayer() == CLT_DETECT && dynamic_cast<Player*>(GetOwner()))
	{
		Player* owner = dynamic_cast<Player*>(GetOwner());
		int32 monsterDetection = owner->GetAtkRange();

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + monsterDetection;
		else
			_pos.x = owner->GetPos().x - monsterDetection;
	}

	if (GetCollisionLayer() == CLT_PLAYER_ATTACK && dynamic_cast<Player*>(GetOwner()))
	{
		Player* owner = dynamic_cast<Player*>(GetOwner());

		_pos.y -= 20;

		if (owner->GetDir() == DIR_RIGHT)
			_pos.x = owner->GetPos().x + 20;
		else
			_pos.x = owner->GetPos().x - 20;
	}

	if (GetCollisionLayer() == CLT_STRUCTURE_DETECT && dynamic_cast<ZipLine*>(GetOwner()))
	{
		ZipLine* owner = dynamic_cast<ZipLine*>(GetOwner());
		Player* player = dynamic_cast<Player*>(owner->GetPlayer());

		if (owner == nullptr || player == nullptr)
			return;

		if (player->GetState() == HANG)	// Player를 따라감
		{
			owner->GetPlayerDetectCollider()->SetPos({ player->GetPos() });
		}
		else if (player->GetState() == RELEASE)
		{
			_pos = owner->GetMidPos();
		}
		else
		{
			if (owner->GetMidPos().x == 0 && owner->GetMidPos().y == 0)		// 초기 위치
				_pos = owner->GetBeginPos();
			else  // 중간 하차 후 위치 유지
				_pos = owner->GetMidPos();		
		}
	}
	
	if (_isManual && GetCollisionLayer() == CLT_GROUND)		// Foothold의 Collider 중 아래 발판
	{
		FootHold* footHold = dynamic_cast<FootHold*>(GetOwner());

		_pos.y = footHold->GetPos().y + 40;
	}
}

void BoxCollider::Render(HDC hdc)
{
	Super::Render(hdc);

	Vec2 cameraPosAdjustment = GET_SINGLE(ValueManager)->GetCameraPosAdjustment();
	Vec2 winSizeAdjustment = GET_SINGLE(ValueManager)->GetWinSizeAdjustment();

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
	Utils::DrawRect(hdc, 
		{ _pos.x * winSizeAdjustment.x - cameraPosAdjustment.x,
		_pos.y * winSizeAdjustment.y - cameraPosAdjustment.y },
		_size.x * winSizeAdjustment.x,
		_size.y* winSizeAdjustment.y);
	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);
}

bool BoxCollider::CheckCollision(Collider* other)
{
	if (Super::CheckCollision(other) == false)		// 애초에 충돌을 원하지 않으면 바로 skip
		return false;

	switch (other->GetColliderType())
	{
	case ColliderType::Box:
		return CheckCollisionBox2Box(this, static_cast<BoxCollider*>(other));
	case ColliderType::Sphere:
		return CheckCollisionSphere2Box(static_cast<SphereCollider*>(other), this);
	}

	return false;
}

RECT BoxCollider::GetRect()
{
	RECT rect =
	{
		(int32)(_pos.x - (_size.x / 2)),
		(int32)(_pos.y - (_size.y / 2)),
		(int32)(_pos.x + (_size.x / 2)),
		(int32)(_pos.y + (_size.y / 2))
	};

	return rect;
}
