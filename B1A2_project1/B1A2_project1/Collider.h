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

	// �浹 ���̾� ����, ��������
	void SetCollisionLayer(COLLISION_LAYER_TYPE layer) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer() { return _collisionLayer; }
	
	// �浹�ϰ� ���� ���̾� �߰�, ����
	void AddCollisionFlagLayer(COLLISION_LAYER_TYPE layer);		// �浹 ���̾� ����
	void RemoveCollisionFlagLayer(COLLISION_LAYER_TYPE layer);
	
	// ��Ʈ �÷��� ����, ��������, ����
	void SetCollisionFlag(uint32 flag) { _collisionFlag = flag; }
	uint32 GetCollisionFlag() { return _collisionFlag; }
	void ResetCollisionFlag() { _collisionFlag = 0; }		// �ƹ� ���̾�͵� �浹���� ���� ��

protected:
	ColliderType _colliderType;
	bool _showDebug = true;
	Vec2 _pos{};

public: 
	std::unordered_set<Collider*> _collisionMap;

protected:
	COLLISION_LAYER_TYPE _collisionLayer = {};	// ���� �����ΰ�?
	uint32 _collisionFlag = 0xFFFFFFFF;		// ������ �浹�� ���ΰ�? / 0 : �ƹ��� �浹���� ����, 0xFFF : ��ο� �浹
};

