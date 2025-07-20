#include "pch.h"
#include "CameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::LateUpdate()
{
	if (!_player)
		return;

	Vec3 playerPos = _player->GetTransform()->GetLocalPosition();
	Vec3 cameraPos = playerPos + Vec3(0.f, 3.f, -5.f);

	Vec3 cameraRotation = _player->GetTransform()->GetLocalRotation();

	GetTransform()->SetLocalPosition(cameraPos);
	GetTransform()->SetLocalRotation(cameraRotation);
}