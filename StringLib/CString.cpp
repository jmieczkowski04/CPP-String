#include "CString.h"
#include <utility>
#include <cassert>
#include <string.h>

void CString::Init()
{
	size = 0;
	dataBufferSize = 1;
	data = new ANSICHAR[dataBufferSize];
}

void CString::ResizeDataBuffer(uint32 NewSize)
{
	ANSICHAR* NewBuffer = new ANSICHAR[NewSize];

	uint32 SizeToCopy = std::min(NewSize, dataBufferSize);
	assert(SizeToCopy > size);

	dataBufferSize = NewSize;
	memcpy(NewBuffer, data, SizeToCopy);
	delete data;
	data = NewBuffer;
}

CString::CString()
{
	Init();
}

CString::CString(const CString& Other)
{
	dataBufferSize = Other.dataBufferSize;
	size = Other.size;
	data = new ANSICHAR[dataBufferSize];
	memcpy(data, Other.data, dataBufferSize);
}

CString::CString(CString&& Other) noexcept : 
data(std::move(Other.data)), 
size(std::move(Other.size)), 
dataBufferSize(std::move(Other.dataBufferSize))
{
}

CString::~CString()
{
	delete data;
}

CString& CString::operator=(CString other) noexcept
{
	std::swap(size, other.size);
	std::swap(dataBufferSize, other.dataBufferSize);
	std::swap(data, other.data);
	return *this;
}

void CString::Assign(const char* str)
{
	delete data;
	size = strlen(str);
	dataBufferSize = size + 1;
	data = new ANSICHAR[dataBufferSize];
	strcpy_s(data, dataBufferSize, str);
}

void CString::AddString(const char* other)
{
	uint32 addedSize = strlen(other);
	ResizeDataBuffer(dataBufferSize + addedSize);
	strcpy_s(data + size, dataBufferSize - size, other);
	size += addedSize;
}

void CString::AddString(CString& other)
{
	uint32 addedSize = other.size;
	ResizeDataBuffer(dataBufferSize + addedSize);
	strcpy_s(data + size, dataBufferSize - size, other.data);
	size += addedSize;
}



CString::CString(const char* str)
{
	Init();
	Assign(str);
}

CString& CString::operator=(const char* str)
{
	Assign(str);
	return *this;
}

CString& CString::operator+(const char* str)
{
	AddString(str);

	return *this;
}

CString& CString::operator+=(const char* str)
{
	AddString(str);

	return *this;
}

CString& CString::operator+(CString& other)
{
	AddString(other);

	return *this;
}

CString& CString::operator+=(CString& other)
{
	AddString(other);

	return *this;
}



const ANSICHAR* CString::operator*() const
{
	return size ? data : "";
}

const ANSICHAR CString::operator[](uint32 index) const
{
	assert(index < size);
	return data[index];
}

uint32 CString::GetSize() const
{
	return size;
}
