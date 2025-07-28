#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize)
{
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();
	if (dataSize == 0)
	{
		// read, write 커서가 만나면 초기화
		_readPos = _writePos = 0;
	}
	else
	{
		// 남은 공간이 별로 없으면 데어터를 복사하여 buffer 앞으로 이동
		if (FreeSize() < _bufferSize)
		{
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
		}
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	// 남은 데이터의 크기가 한 번에 읽는 데이터의 크기보다 적으면 리턴
	if (numOfBytes > DataSize())
		return false;

	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	// 남은 공간이 한 번에 쓰는 데이터의 크기보다 적으면 리턴
	if (numOfBytes > FreeSize())
		return false;

	_writePos += numOfBytes;
	return true;
}