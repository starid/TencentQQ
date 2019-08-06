#pragma once
#include "ipackdata.h"
#include"CallArgus.pb.h"


class CCommReq :
	public CIPackData
{
public:
	CCommReq(void);
	~CCommReq(void);
private:
	unsigned int PackHead(CTXCommPack*);
	unsigned int PackBody(CTXCommPack*);
public:
	unsigned int PackData();
public:
	const TransmitParameters::ToPackArgu *ptoPackArgus;
};

