#include "pch.h"
#include "BufferReader.h"

BufferReader::BufferReader()
{
}

BufferReader::BufferReader(BYTE* buffer, uint32 dataSize, uint32 pos)
	: _buffer(buffer), _dataSize(dataSize), _pos(pos)
{

}

BufferReader::~BufferReader()
{

}

bool BufferReader::Peek(void* dest, uint32 len)
{
	// 읽을 수 있는 데이터의 크기보다 크면 리턴
	if (ReadableSize() < len)
		return false;

	// 데이터 복사
	::memcpy(dest, &_buffer[_pos], len);
	return true;
}

bool BufferReader::Read(void* dest, uint32 len)
{
	// 커서를 옮길 수 있는지 미리 체크
	if (Peek(dest, len) == false)
		return false;

	// 커서 옮기기
	_pos += len;
	return true;
}