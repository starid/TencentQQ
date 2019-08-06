#pragma once
#include<random>
class CSeqSerial
{
public:

	CSeqSerial(void)
	{
	}
	virtual ~CSeqSerial(void)
	{
	}
public:
	unsigned short GetSeqSerial(unsigned short wCmd=0x0000)
	{
		if (wCmd == 0)
		{
			unsigned short seq = rand();
			return seq;
		}
		else if (wCmd == 0x0058)
			return SeqSerial0058++;
		else if (wCmd == 0x001D)
			return SeqSerial001D++;
		else
		{
			unsigned short seq = rand();
			return seq;
		}

	}
private:
	//common
	static short SeqSerial0058;
	static short SeqSerial001D;
};