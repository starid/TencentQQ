#pragma once
#include<Windows.h>
class CLock
{
public:
	void Lock()
	{
		EnterCriticalSection(s_cs);
	}

	void UnLock()
	{
		LeaveCriticalSection(s_cs);
	}
public:
	CLock(CRITICAL_SECTION *c)
	{ 
		s_cs = c;
		InitializeCriticalSection(s_cs);
	}
	~CLock() 
	{
		DeleteCriticalSection(s_cs);
	}
private:
	CLock(){};
private:
	CRITICAL_SECTION *s_cs;
};
