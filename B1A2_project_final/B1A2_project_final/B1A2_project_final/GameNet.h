#pragma once
#include <array>

enum
{
	EnterRoom = 1,
	AddPlayer = 3,
	AddObject = 4,
	Move = 5,
};

class GameNet
{
public:
	GameNet();
	virtual	~GameNet();

	void Init();
	void Update();

public:
	// ¼Û½Å
	bool SendEnterRoomPacket();
	bool SendMovePacket();

private:
	bool _isServerConnected = false;

	SOCKET _clientSocket{};
	WSAPOLLFD _pollfd{};
	std::vector<char> _recvBuffer;
	std::array<uint32_t, 2> _header{};
};