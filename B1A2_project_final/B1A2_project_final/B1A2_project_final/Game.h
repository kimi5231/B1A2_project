#pragma once
#include <memory>

class CGameFramework;
class GameNet;

class Game
{
public:
	Game();
	virtual ~Game() {};

	void Update();

public:
	std::shared_ptr<CGameFramework> GetGameFramework() { return _gameFramework; }

private:
	std::shared_ptr<CGameFramework> _gameFramework;
	std::shared_ptr<GameNet> _gameNet;
};