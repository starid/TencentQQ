#pragma once
#include"Packet.h"
#include"../UtilLib/ByteBuffer.h"

class CIUnPackData
{
public:

	CIUnPackData(void)
	{
		pack.clear();
		_packet_type=TYPE_UnDefine;
		mSeq=0;
	}

	virtual ~CIUnPackData(void)
	{
	}
private:
	//用于解封数据包头
	virtual unsigned int UnPackHead()=0;
	//用于解封数据体
	virtual unsigned int UnPackBody()=0;
public:
	//用于包裹代码
	void Wrapping(const ByteBuffer& b){pack=b;pack.rpos(0);};
	//用于检查接收的数据包(解密前检查)
	virtual	unsigned int _check_packet()=0;
	//用于解封数据包
	virtual unsigned int UnPackData()=0;
	//用于分析接受的数据包（解密后的分析）
	virtual unsigned int Analysis()=0;
	//用于设置数据包类型
	virtual void SetPacketType(const unsigned short type){_packet_type=type;};
	unsigned short GetPackType(){return _packet_type;};
	void SetSeq(unsigned int seq){mSeq=seq;};
	unsigned int GetSeq(){return mSeq;};
public:
	ByteBuffer pack;
private:
	unsigned short _packet_type;
	unsigned int mSeq;
};

