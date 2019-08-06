#pragma once
#include"../JceProtocol/JceOutputStream.h"
class CStreamOut:public CJceOutputStream
{
public:
	CStreamOut(void);
	virtual ~CStreamOut(void);
};

