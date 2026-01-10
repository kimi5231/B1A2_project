#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	virtual void Update();

public:
	void SetID(UINT id) { _id = id; }
	UINT GetID() { return _id; }
	void SetObjectType(ObjectType type) { _type = type; }
	ObjectType GetObjectType() { return _type; }
	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }
	void SetRotation(Rotation rotation) { _rotation = rotation; }
	Rotation GetRotation() { return _rotation; }
	void SetState(MoveState state) { _state = state; }
	MoveState GetState() { return _state; }

protected:
	UINT _id{};
	ObjectType _type{};
	Vector _pos{};
	Rotation _rotation{};
	MoveState _state{};
};

