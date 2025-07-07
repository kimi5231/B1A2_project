#pragma once
#include "Actor.h"

// 카메라 이동을 위한 객체
class CameraActor : public Actor
{
	using Super = Actor;
public:
	CameraActor();
	virtual ~CameraActor() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
};

