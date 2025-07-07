#pragma once
#include "Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);
	
	ColliderType GetColliderType() { return _colliderType; }
	void SetShowDebug(bool show) { _showDebug = show; }

public:
	static bool CheckCollisionBox2Box(BoxCollider* b1, BoxCollider* b2);
	static bool CheckCollisionSphere2Box(SphereCollider* s1, BoxCollider* b2);
	static bool CheckCollisionSphere2Sphere(SphereCollider* s1, SphereCollider* s2);
	
	Vec2 GetPos() { return _pos; }
	void SetPos(Vec2 pos) { _pos = pos; }

	// 충돌 레이어 설정, 가져오기
	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer() { return _collisionLayer; }
	
	// 충돌하고 싶은 레이어 추가, 제거
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);		// 충돌 레이어 설정
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	
	// 비트 플래그 설정, 가져오기, 삭제
	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }
	void ResetCollisionFlag() { _collisionFlag = 0; }		// 아무 레이어와도 충돌하지 않을 것

protected:
	ColliderType _colliderType;
	bool _showDebug = true;
	Vec2 _pos{};

public: 
	std::unordered_set<Collider*> _collisionMap;

protected:
	COLLISION_LAYER_TYPE _collisionLayer = {};	// 나는 누구인가?
	uint32 _collisionFlag = 0xFFFFFFFF;		// 누구랑 충돌할 것인가? / 0 : 아무와 충돌하지 않음, 0xFFF : 모두와 충돌
};

