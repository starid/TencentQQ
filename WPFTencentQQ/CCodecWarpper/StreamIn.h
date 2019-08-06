#pragma once
#include"../JceProtocol/JceInputStream.h"
class CStreamIn:public CJceInputStream
{
public:
	CStreamIn(void);
	CStreamIn(ByteBuffer paramByteBuffer):CJceInputStream(paramByteBuffer){};
	CStreamIn(JCE::JCEByteArray paramArrayOfByte):CJceInputStream(paramArrayOfByte){};
	CStreamIn(JCE::JCEByteArray paramArrayOfByte,int paramInt):CJceInputStream(paramArrayOfByte,paramInt){};
	virtual ~CStreamIn(void);
public:
	JCE::IObject *ObjectAlloc(unsigned int);
};

