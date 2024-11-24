#pragma once

enum class ObjectType
{
	None,
	Player,
	Projectile,
	Monster
};

enum class MoveDir
{
	Left,
	Right,
};

class Object
{
public:
	Object(ObjectType type);	// � Ÿ������ �޾Ƽ� �����ϱ�
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

public:
	ObjectType GetObjectType() { return _type; }

protected:
	ObjectType _type = ObjectType::None;
	MoveDir _dir = MoveDir::Right;
	PlayerStat _stat = {};
	Vec2 _pos = {};
	float _radius = 0.f;
};

