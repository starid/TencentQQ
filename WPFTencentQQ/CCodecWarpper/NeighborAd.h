#pragma once
#include"../JceProtocol/JceStruct.h"

class CNeighborAd:public JCE::CJceStruct
{
public:
	CNeighborAd(void);
	virtual ~CNeighborAd(void);
public:
	JCE::JCEString ad_item;
	JCE::JCEInt ad_postion;
	JCE::JCEInt ad_source;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

