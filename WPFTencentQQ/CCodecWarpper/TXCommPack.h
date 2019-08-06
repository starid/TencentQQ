#pragma once
#include"../UtilLib/ByteBuffer.h"

#define BUFFER_SIZE	0x200
//#pragma pack(1)
class CTXCommPack
{
public:
	CTXCommPack(void);
	CTXCommPack(size_t);
	virtual ~CTXCommPack(void);
public:
	void AddByte(const char);
	void AddWord(const short);
	void AddDWord(const int);
	void AddByteBuffer(ByteBuffer&);
	void AddBuf(const char *,const int);
	void AddBufLenWord();		//增加前置2字节长度，不包含本身
	void AddLenDWord();		//增加前置4字节长度，包含本身
	void AddBufLenDWord();		//增加前置4字节长度，不包含本身
	void AddFieldCode(short);
	void GetBufferOut();
public:
	ByteBuffer buffer;
};
