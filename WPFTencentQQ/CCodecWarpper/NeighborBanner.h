#pragma once
#include"../JceProtocol/JceStruct.h"

class CNeighborBanner:public JCE::CJceStruct
{
public:
	CNeighborBanner(void);
	virtual ~CNeighborBanner(void);
public:
	JCE::JCEByteArray description;
	JCE::JCEByteArray pic_url;
	JCE::JCEByteArray skip_url;
	JCE::JCEInt postion;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

