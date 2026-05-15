#pragma once
class ExpOver
{
public:
	ExpOver()
	{
		ZeroMemory(&_over, sizeof(_over));
		_buffer.reserve(BufferSize);
		_wsaBuffer.buf = reinterpret_cast<char*>(_buffer.data());
		_wsaBuffer.len = BufferSize;
	}

	ExpOver(IOType ioType)
		: _ioType(ioType)
	{
		ZeroMemory(&_over, sizeof(_over));
		_buffer.reserve(BufferSize);
		_wsaBuffer.buf = reinterpret_cast<char*>(_buffer.data());
		_wsaBuffer.len = BufferSize;
	}

	WSAOVERLAPPED _over;
	IOType  _ioType;
	WSABUF	_wsaBuffer;
	std::vector<char> _buffer;
};