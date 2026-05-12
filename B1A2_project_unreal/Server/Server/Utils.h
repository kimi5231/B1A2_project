#pragma once
#include <cmath>
#include "Types.h"
#include "BoundingBox.h"

// 바라보는 방향 벡터
inline Vector GetForwardVector(float pitch, float yaw)
{
    float p = pitch * (3.14159265f / 180.0f);
    float y = yaw * (3.14159265f / 180.0f);

    float x = cos(p) * cos(y);
    float y_pos = cos(p) * sin(y);
    float z = sin(p);

    Vector v{ x, y_pos, x };
    v.Normalize();

    return v;
}