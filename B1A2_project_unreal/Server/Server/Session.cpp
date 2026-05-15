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
	_recvOver._ioType = IOType::Recv;
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
	DWORD bytesReceived = 0;
	memset(&_recvOver._over, 0, sizeof(_recvOver._over));
	_recvOver._wsaBuffer.buf = _recvOver._buffer.data();
	_recvOver._wsaBuffer.len = _recvOver._buffer.size();
	int result = WSARecv(_clientSocket, &_recvOver._wsaBuffer, 1, &bytesReceived, &recvFlag, &_recvOver._over, nullptr);

	if (result == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING)
		{
			// 여기서 에러가 찍힌다면 예약 자체가 실패한 것임!
			printf("WSARecv Failed: %d\n", err);
		}
		else
		{
			// 997이 찍힌다면 예약은 성공, 클라가 안 보낸 것임
			// printf("WSARecv Pending...\n");
		}
	}
}

void Session::Send(const std::vector<char>& packet)
{
	ExpOver* over = new ExpOver(IOType::Send);
	memcpy(over->_buffer.data(), packet.data(), packet.size());
	over->_wsaBuffer.buf = (char*)over->_buffer.data();
	over->_wsaBuffer.len = packet.size();
	WSASend(_clientSocket, &over->_wsaBuffer, 1, 0, 0, &over->_over, nullptr);
}