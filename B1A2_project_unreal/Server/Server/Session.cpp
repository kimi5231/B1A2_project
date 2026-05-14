#include "pch.h"
#include "Session.h"
#include "ExpOver.h"
#include "Room.h"
#include "Player.h"

Session::Session()
{
	_clientSocket = INVALID_SOCKET;
	_isConnected = false;
	_id = -1;
	_recvOver._ioType = IOType::Accept;
	_prevRecv = 0;
	_room = nullptr;
	_player = nullptr;
}

Session::~Session()
{
	if (_isConnected)
		closesocket(_clientSocket);
}

void Session::Recv()
{
	DWORD recvFlag = 0;
	memset(&_recvOver._over, 0, sizeof(_recvOver._over));
	WSARecv(_clientSocket, &_recvOver._wsaBuffer, 1, 0, &recvFlag, &_recvOver._over, nullptr);
}

void Session::Send(const std::vector<char>& packetData)
{
	ExpOver* o = new ExpOver(IOType::Send);
	o->m_wsa.len = num_bytes;
	memcpy(o->m_buff, packetData, num_bytes);
	WSASend(_clientSocket, &o->m_wsa, 1, 0, 0, &o->m_over, nullptr);
}