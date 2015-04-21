#pragma once
#include <Lightup.h>

class Global
{
public:
	Global();
	~Global();

	// ���ü���
	// ����ƽ�� WSPStartup() �� WSPCleanup() ����
public:
	int GetRefCount();
	void IncRefCount();
	void DecRefCount();
private:
	int refCount;

	// ȫ���ٽ���
public:
	void Enter();
	void Leave();
private:
	CriticalSection cs;

	// �ϵ����̱�
public:
	WSPUPCALLTABLE GetUpcallTable();
	void SetUpcallTable(WSPUPCALLTABLE v);
private:
	WSPUPCALLTABLE upcallTable;
};

extern Global g;