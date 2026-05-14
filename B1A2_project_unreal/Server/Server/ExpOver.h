#pragma once
class ExpOver
{
public:
	ExpOver()
	{
		ZeroMemory(&_over, sizeof(_over));
		_wsaBuffer.buf = _buffer;
		_wsaBuffer.len = BufferSize;
	}

	ExpOver(IOType ioType)
		: _ioType(ioType)
	{
		ZeroMemory(&_over, sizeof(_over));
		_wsaBuffer.buf = _buffer;
		_wsaBuffer.len = BufferSize;
	}

	WSAOVERLAPPED _over;
	IOType  _ioType;
	WSABUF	_wsaBuffer;
	char  _buffer[BufferSize];
};