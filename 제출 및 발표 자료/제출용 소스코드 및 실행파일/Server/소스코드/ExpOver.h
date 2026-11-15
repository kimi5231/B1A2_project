#pragma once
#include "Packets.h"

class ExpOver
{
public:
	ExpOver()
	{
		ZeroMemory(&_over, sizeof(_over));
		ZeroMemory(&_udpAddr, sizeof(_udpAddr));
		_udpAddrLen = sizeof(_udpAddr);
		_buffer.resize(BufSize);
		_wsaBuffer.buf = reinterpret_cast<char*>(_buffer.data());
		_wsaBuffer.len = BufSize;
	}

	ExpOver(IOType ioType)
		: _ioType(ioType)
	{
		ZeroMemory(&_over, sizeof(_over));
		ZeroMemory(&_udpAddr, sizeof(_udpAddr));
		_udpAddrLen = sizeof(_udpAddr);
		_buffer.resize(BufSize);
		_wsaBuffer.buf = reinterpret_cast<char*>(_buffer.data());
		_wsaBuffer.len = BufSize;
	}

	WSAOVERLAPPED _over;
	IOType  _ioType;
	DBType _dbType;
	bool _dbResult;
	SOCKADDR_IN _udpAddr;
	int _udpAddrLen;
	WSABUF	_wsaBuffer;
	std::vector<char> _buffer;
};