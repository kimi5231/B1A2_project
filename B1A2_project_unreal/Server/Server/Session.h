#pragma once
class ExpOver;
class Room;

class Session
{
public:
	Session();
	~Session();

public:
	void Recv();
	void Send();

	SOCKET _clientSocket;
	int _id;
	bool _isConnected;
	ExpOver _recvOver;
	int _prevRecv;
	Room* _room;
	Player* _player;
};

