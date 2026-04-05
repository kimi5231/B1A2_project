#pragma once
#include "BoundingBox.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

public:
	virtual void Update();

	bool CheckCollision(BoundingBox other) { return _box.CheckCollision(other.GetBounds()); };
	bool CheckInclude(Vector targetPos, float range, float angle);

public:
	void SetID(UINT id) { _id = id; }
	UINT GetID() { return _id; }
	void SetObjectType(ObjectType type) { _type = type; }
	ObjectType GetObjectType() { return _type; }
	void SetPos(Vector pos);
	Vector GetPos() { return _pos; }
	void SetRotation(Rotation rotation) { _rotation = rotation; }
	Rotation GetRotation() { return _rotation; }
	virtual void SetState(ObjectState state);
	ObjectState GetState() { return _state; }
	BoundingBox GetBoundingBox() { return _box; }
	void SetObjectPoolState(ObjectPoolState objectPoolState) { _objectPoolState = objectPoolState; }
	ObjectPoolState GetObjectPoolState() { return _objectPoolState; }

protected:
	uint _id{};
	ObjectType _type{};
	Vector _pos{};
	Vector _size{};
	Rotation _rotation{};
	ObjectState _state{};
	BoundingBox _box;
	ObjectPoolState _objectPoolState;
};

