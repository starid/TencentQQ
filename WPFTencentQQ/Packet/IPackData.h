#pragma once
#include"../UtilLib/ByteBuffer.h"
#include"Packet.h"
#include"TXCommPack.h"
#include"..\Packet\ConfigData.h"

class CIPackData
{
public:
	CIPackData(void)
	{
	};
	virtual ~CIPackData(void)
	{
	};
private:
	//用于封装数据包头
	virtual unsigned int PackHead(CTXCommPack *)=0;
	//用于封装数据体
	virtual unsigned int PackBody(CTXCommPack *)=0;
	//用于对数据加密前的填充
	virtual void GarbagePadding(const ByteBuffer&){};
public:
	//用于封装整个数据包
	virtual unsigned int PackData()=0;
	//用于设置数据包类型
	void SetPacketType(unsigned short type){_packet_type=type;};
	unsigned short GetPackType(){return _packet_type;};
public:
	ByteBuffer pack;
	CConfigData *pConfig;     //数据包配置
private:
	unsigned short _packet_type;
};

