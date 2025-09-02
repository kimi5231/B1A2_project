#pragma once
class GameNet
{
public:
	GameNet();
	virtual	~GameNet();

	void Init();
	void Update();

private:
	bool SendAddPlayerPacket();

private:
	SOCKET _clientSocket{};
	WSAPOLLFD _pollfd{};
};