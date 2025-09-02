#include "Game.h"
#include "GameFramework.h"
#include "GameNet.h"

Game::Game()
{
	_gameFramework = std::make_shared<CGameFramework>();

	_gameNet = std::make_shared<GameNet>();
	_gameNet->Init();
}

void Game::Update()
{
	_gameFramework->FrameAdvance();
	_gameNet->Update();
}