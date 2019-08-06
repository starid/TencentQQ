#pragma once
#include"../JceProtocol/JceStruct.h"

class CEntranceContent:public JCE::CJceStruct
{
public:
	CEntranceContent(void);
	virtual ~CEntranceContent(void);
public:
	JCE::JCEInt type;
	JCE::JCEByteArray content_buff;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

