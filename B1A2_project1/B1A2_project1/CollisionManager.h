#pragma once

class Collider;

// ������ ������������ ����Ʈ �����ͷ� ����ؾ� ��
class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

	// ��� _colliders ����
	void ClearColliders();

private:
	std::vector<Collider*> _colliders;
};

