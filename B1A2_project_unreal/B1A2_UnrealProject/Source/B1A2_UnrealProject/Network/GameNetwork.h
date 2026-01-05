#pragma once
#include "Includes.h"

class GameNetwork
{
public:
	GameNetwork();
	~GameNetwork();

public:
	void Update();
	void ProcessRecv();

public:
	std::vector<RecvEventType>& GetRecvEvents() { return _recvEvents; }

private:
	fd_set _readSet{};
	fd_set _writeSet{};

	SOCKET _clientSocket{};

	std::vector<RecvEventType> _recvEvents;
};