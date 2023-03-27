#pragma once

#include "GenericTypes.h"

class CString
{
private:
	ANSICHAR* data;
	uint32 size;
	uint32 dataBufferSize;

	void Init();
	void ResizeDataBuffer(uint32 NewSize);
	void Assign(const char* str);
	void AddString(const char* other);
	void AddString(CString& other);

public:
	CString();
	CString(const CString& Other);
	CString(CString&& Other) noexcept;
	~CString();
	CString& operator=(CString other) noexcept;

	CString(const char* str);
	CString& operator=(const char* str);
	CString& operator+(const char* str);
	CString& operator+=(const char* str);
	CString& operator+(CString& other);
	CString& operator+=(CString& other);

	const ANSICHAR* operator*() const;
	const ANSICHAR operator[](uint32 index) const;


	uint32 GetSize() const;
};