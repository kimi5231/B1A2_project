#pragma once
#include <cmath>
#include "Types.h"

// 바라보는 방향 벡터
inline Vector GetForwardVector(float pitch, float yaw)
{
    // 각도 라디안 변환
    float p = pitch * (3.14159265f / 180.0f);
    float y = yaw * (3.14159265f / 180.0f);

    float x = cos(p) * sin(y);
    float y_pos = cos(p) * sin(y);
    float z = sin(p);

    // 정규화 후 반환
    return Vector(x, y_pos, z).Normalize();
}