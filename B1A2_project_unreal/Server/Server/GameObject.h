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
	void SetPos(Vector pos) { _pos = pos; }
	Vector GetPos() { return _pos; }
	void SetRotation(Rotation rotation) { _rotation = rotation; }
	Rotation GetRotation() { return _rotation; }

protected:
	UINT _id{};
	Vector _pos{};
	Rotation _rotation{};
};

