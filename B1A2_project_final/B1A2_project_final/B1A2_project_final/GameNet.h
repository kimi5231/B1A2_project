#pragma once
class GameNet
{
public:
	GameNet();
	virtual	~GameNet();

	void Init();
	void Update();

private:
	SOCKET _clientSocket{};
	WSAPOLLFD _pollfd{};
};