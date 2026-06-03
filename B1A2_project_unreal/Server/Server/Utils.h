#pragma once
// 바라보는 방향 벡터
Vector GetForwardVector(float pitch, float yaw);

Vector SelectRandomPosInCube(const CubeRef cube);

bool IsCanExist(VectorInt index, const CubeRef cube);

VectorInt PosToIndex(Vector pos, const CubeRef cube);

Vector IndexToPos(VectorInt index, const CubeRef cube);