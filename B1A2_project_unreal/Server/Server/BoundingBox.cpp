#include "pch.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::CheckCollision(const std::pair<Vector, Vector>& other)
{
	return  (_ranges.first.x < other.second.x && _ranges.second.x > other.first.x)
        && (_ranges.first.y < other.second.y && _ranges.second.y > other.first.y)
        && (_ranges.first.z < other.second.z && _ranges.second.z > other.first.z);
}