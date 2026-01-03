#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#undef min
#undef max

class GameNetwork
{
public:
	GameNetwork();
	~GameNetwork();

public:
	void Update() {};

private:
	SOCKET _clientSocket;
};