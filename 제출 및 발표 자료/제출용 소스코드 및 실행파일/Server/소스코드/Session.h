#pragma once
#include "ExpOver.h"

class Room;

class Session
{
public:
	Session();
	~Session();

public:
	void Recv();
	void Send(const std::vector<char>& packetData);

	SOCKET _clientSocket;
	int _id;
	bool _isConnected;
	ExpOver _recvOver;
	int _prevRecv;
	std::vector<char> _name;
	Room* _room;
	Player* _player;
};