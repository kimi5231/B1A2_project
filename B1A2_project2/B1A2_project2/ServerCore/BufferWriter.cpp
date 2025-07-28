#include "pch.h"
#include "BufferWriter.h"

BufferWriter::BufferWriter()
{

}

BufferWriter::BufferWriter(BYTE* buffer, uint32 size, uint32 pos)
	: _buffer(buffer), _size(size), _pos(pos)
{

}

BufferWriter::~BufferWriter()
{

}

bool BufferWriter::Write(void* src, uint32 len)
{
	// 남은 공간이 데이터의 크기보다 작으면 리턴
	if (FreeSize() < len)
		return false;

	// 데이터를 버퍼에 복사
	::memcpy(&_buffer[_pos], src, len);
	// 커서 이동
	_pos += len;
	return true;
}