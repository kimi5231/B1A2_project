#include "pch.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"
#include "ValueManager.h"

void Game::Init(const WindowInfo& info)
{
	_hwnd = info.hwnd;
	_hdc = ::GetDC(info.hwnd);

	GEngine->Init(info);

	GET_SINGLE(ValueManager)->Init(info.hwnd);
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::TestScene);

}

void Game::Update()
{
	GEngine->Update();
}
