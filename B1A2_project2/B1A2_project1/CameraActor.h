#pragma once
#include "Actor.h"

// ī�޶� �̵��� ���� ��ü
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

