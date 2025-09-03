#pragma once
#include <array>

enum
{
	TEST = 1,
	EnterRoom = 2,
	AddPlayer = 3,
};

class GameNet
{
public:
	GameNet();
	virtual	~GameNet();

	void Init();
	void Update();

public:
	bool SendEnterRoomPacket();

private:
	SOCKET _clientSocket{};
	WSAPOLLFD _pollfd{};
	std::vector<char> _recvBuffer;
	std::array<uint32_t, 2> _header{};
};