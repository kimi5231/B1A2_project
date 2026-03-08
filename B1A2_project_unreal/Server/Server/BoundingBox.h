#pragma once
class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

public:
	bool CheckCollision(const AABB& other);
	bool CheckInclude(const AABB& other);
	bool CheckInclude(const Vector pos);

public:
	void SetBounds(Vector pos, Vector size, Dir dir);
	const AABB& GetBounds() { return _bounds; }
	void SetOwnerPos(Vector pos, Dir dir);
	const std::array<Vector, CornerCount> GetCorners();

private:
	Vector _ownerPos;
	Vector _ownerSize;
	AABB _bounds;
};

