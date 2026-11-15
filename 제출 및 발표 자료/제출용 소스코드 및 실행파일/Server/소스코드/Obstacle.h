#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
	Obstacle();
	virtual ~Obstacle() {};

	virtual void Update() override {};

public:
	ObstacleType GetObstacleType() const { return _obstacleType; }
	void SetObstacleType(ObstacleType obstacleType) { _obstacleType = obstacleType; }

protected:
	ObstacleType _obstacleType;
};