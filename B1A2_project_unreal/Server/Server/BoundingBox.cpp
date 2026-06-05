#include "pch.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

bool BoundingBox::CheckCollision(const AABB& other)
{
	return  (_bounds.min.x < other.max.x && _bounds.max.x > other.min.x)
        && (_bounds.min.y < other.max.y && _bounds.max.y > other.min.y)
        && (_bounds.min.z < other.max.z && _bounds.max.z > other.min.z);
}

bool BoundingBox::CheckInclude(const AABB& other)
{
    return  (_bounds.min.x < other.min.x && other.max.x < _bounds.max.x)
        && (_bounds.min.y < other.min.y && other.max.y < _bounds.max.y)
        && (_bounds.min.z < other.min.z && other.max.z < _bounds.max.z);
}

bool BoundingBox::CheckInclude(const Vector pos)
{
    return  (_bounds.min.x <= pos.x && pos.x <= _bounds.max.x)
        && (_bounds.min.y <= pos.y && pos.y <= _bounds.max.y)
        && (_bounds.min.z <= pos.z && pos.z <= _bounds.max.z);
}

void BoundingBox::SetBounds(Vector pos, Vector size, Dir dir)
{
    _ownerSize = size;
    SetOwnerPos(pos, dir);
}

void BoundingBox::SetBounds(Vector pos, int size, Dir dir)
{
    _ownerSize = Vector(size, size, size);
    SetOwnerPos(pos, dir);
}

void BoundingBox::SetOwnerPos(Vector pos, Dir dir)
{
    _ownerPos = pos;

    switch (dir)
    {
    case Front:
    case Back:
        _bounds.min = { pos.x - _ownerSize.x / 2,  pos.y - _ownerSize.y / 2,  pos.z };
        _bounds.max = { pos.x + _ownerSize.x / 2,  pos.y + _ownerSize.y / 2, pos.z + _ownerSize.z };
        break;
    case Right:
    case Left:
        _bounds.min = { pos.x - _ownerSize.y / 2,  pos.y - _ownerSize.x / 2,  pos.z };
        _bounds.max = { pos.x + _ownerSize.y / 2,  pos.y + _ownerSize.x / 2, pos.z + _ownerSize.z };
        break;
    }
}

const std::unordered_map<Corner, Vector> BoundingBox::GetCorners()
{
    std::unordered_map<Corner, Vector> coners;

    coners[LeftFrontBottom] = _bounds.min;
    coners[LeftFrontTop] = { _bounds.min.x, _bounds.min.y, _bounds.max.z };
    coners[LeftBackBottom] = { _bounds.min.x, _bounds.max.y, _bounds.min.z };
    coners[LeftBackTop] = { _bounds.min.x, _bounds.max.y, _bounds.max.z };
    coners[RightFrontBottom] = { _bounds.max.x, _bounds.min.y, _bounds.min.z };
    coners[RightFrontTop] = { _bounds.max.x, _bounds.min.y, _bounds.max.z };
    coners[RightBackBottom] = { _bounds.max.x, _bounds.max.y, _bounds.min.z };
    coners[RightBackTop] = _bounds.max;
    
    return coners;
}

//const std::array<Vector, CornerCount> BoundingBox::GetCorners()
//{
//    std::array<Vector, CornerCount> coners;
//
//    coners[LeftFrontBottom] = _bounds.min;
//    coners[LeftFrontTop] = { _bounds.min.x, _bounds.min.y, _bounds.max.z };
//    coners[LeftBackBottom] = { _bounds.min.x, _bounds.max.y, _bounds.min.z };
//    coners[LeftBackTop] = { _bounds.min.x, _bounds.max.y, _bounds.max.z };
//    coners[RightFrontBottom] = { _bounds.max.x, _bounds.min.y, _bounds.min.z };
//    coners[RightFrontTop] = { _bounds.max.x, _bounds.min.y, _bounds.max.z };
//    coners[RightBackBottom] = { _bounds.max.x, _bounds.max.y, _bounds.min.z };
//    coners[RightBackTop] = _bounds.max;
//
//    return coners;
//}