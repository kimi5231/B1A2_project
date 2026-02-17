#pragma once
class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

public:
	bool CheckCollision(const std::pair<Vector, Vector>& other);

public:
	void SetRanges(Vector min, Vector max) { _ranges = {min, max}; }
	const std::pair<Vector, Vector>& GetRanges() { return _ranges; }

private:
	// min - max
	std::pair<Vector, Vector> _ranges;
};

