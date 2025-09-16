#pragma once
#include <array>

enum
{
	EnterRoom = 1,
	AddPlayer = 3,
	AddObject = 4,
};

class GameNet
{
public:
	GameNet();
	virtual	~GameNet();

	void Init();
	void Update();

public:
	// 
	bool SendEnterRoomPacket();

	// 


private:
	bool _isServerConnected = false;

	SOCKET _clientSocket{};
	WSAPOLLFD _pollfd{};
	std::vector<char> _recvBuffer;
	std::array<uint32_t, 2> _header{};
};