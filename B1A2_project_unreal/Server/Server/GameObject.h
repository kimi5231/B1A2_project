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
	bool CheckCollision(BoundingBox my, BoundingBox other){ return my.CheckCollision(other.GetBounds()); };
	bool CheckInclude(Vector targetPos, float range, float angle, float height);

public:
	void SetID(int id) { _id = id; }
	int GetID() { return _id; }
	void SetObjectType(ObjectType type) { _type = type; }
	ObjectType GetObjectType() { return _type; }
	virtual void SetPos(Vector pos);
	Vector GetPos() { return _pos; }
	void SetSize(Vector size);
	Vector GetSize() { return _size; }
	void SetRotation(Rotation rotation) { _rotation = rotation; }
	Rotation GetRotation() { return _rotation; }
	virtual bool SetState(ObjectState state, bool isSend = true);
	ObjectState GetState() { return _state; }
	BoundingBox GetBoundingBox() { return _box; }
	void SetObjectPoolState(ObjectPoolState objectPoolState);
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

