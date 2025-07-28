#pragma once
class BufferReader
{
public:
	BufferReader();
	BufferReader(BYTE* buffer, uint32 dataSize, uint32 pos = 0);
	~BufferReader();

	BYTE* Buffer() { return _buffer; }
	uint32 DataSize() { return _dataSize; }
	uint32 ReadSize() { return _pos; }
	uint32 ReadableSize() { return _dataSize - _pos; }

	// 데이터의 복사본을 만들어 미리보기
	template<typename T>
	bool Peek(T* dest) { return Peek(dest, sizeof(T)); }
	bool Peek(void* dest, uint32 len);

	// 데이터를 읽고 커서 옮기기
	template<typename T>
	bool Read(T* dest) { return Read(dest, sizeof(T)); }
	bool Read(void* dest, uint32 len);

	// 데이터를 읽기 위한 연산자 오버로딩
	template<typename T>
	BufferReader& operator>>(OUT T& dest);

private:
	BYTE* _buffer = nullptr;
	uint32 _dataSize = 0;
	uint32 _pos = 0;
};

template<typename T>
inline BufferReader& BufferReader::operator>>(OUT T& dest)
{
	dest = *reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += sizeof(T);
	return *this;
}