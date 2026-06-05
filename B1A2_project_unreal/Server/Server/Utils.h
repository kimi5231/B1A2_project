#pragma once
class BoundingBox;
class GameObject;

// 바라보는 방향 벡터
Vector GetForwardVector(float pitch, float yaw);

Vector SelectRandomPosInCube(VectorInt size, const CubeRef cube);

Vector SelectRandomPosInCube(const CubeRef cube);

bool IsCanExist(VectorInt index, const CubeRef cube);

bool IsCanExist(VectorInt index, VectorInt size, const CubeRef cube);

VectorInt PosToIndex(Vector pos, const CubeRef cube);

Vector IndexToPos(VectorInt index, const CubeRef cube);