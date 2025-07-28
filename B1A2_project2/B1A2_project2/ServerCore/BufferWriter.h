#pragma once
class BufferWriter
{
public:
	BufferWriter();
	BufferWriter(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferWriter();

	BYTE* Buffer() { return _buffer; }
	uint32 Size() { return _size; }
	uint32 WriteSize() { return _pos; }
	uint32 FreeSize() { return _size - _pos; }

	// 데이터를 버퍼에 기록하고 커서 이동
	template<typename T>
	bool Write(T* src) { return Write(src, sizeof(T)); }
	bool Write(void* src, uint32 len);

	// 공간 확보
	template<typename T>
	T* Reserve();

	// 데이터를 쓰기 위한 연산자 오버로딩
	template<typename T>
	BufferWriter& operator<<(T&& src);

private:
	BYTE* _buffer = nullptr;
	uint32 _size = 0;
	uint32 _pos = 0;
};

template<typename T>
T* BufferWriter::Reserve()
{
	// 남은 공간이 확보해야되는 공간보다 작으면 리턴
	if (FreeSize() < sizeof(T))
		return nullptr;

	// 공간 확보
	T* ret = reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += sizeof(T);
	return ret;
}

template<typename T>
BufferWriter& BufferWriter::operator<<(T&& src)
{
	using DataType = std::remove_reference_t<T>;
	*reinterpret_cast<DataType*>(&_buffer[_pos]) = std::forward<DataType>(src);
	_pos += sizeof(T);
	return *this;
}