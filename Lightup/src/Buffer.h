#pragma once
class Buffer
{
public:
	Buffer();
	Buffer(SIZE_T length);
	~Buffer();

public:
	Buffer(const Buffer& src);
	Buffer& operator=(const Buffer& src);

public:
	SIZE_T	Length() const;
	char*	Adress() const;

private:
	char* p = NULL;
	SIZE_T len = 0;

public:
	static char* Alloc(SIZE_T length);
	static char* AllocCopy(char* src, SIZE_T length);
	static void Free(char** p);
};

