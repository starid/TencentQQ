#include"Packet.h"
#include"ICHeadData.h"

struct CCommHeadReq_Type
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
};

struct CCommHeadResp_Type
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
};


class CCommHeadReq :
	public ICHeadData
{
public:
	CCommHeadReq(void)
	{
	};
	virtual ~CCommHeadReq(void)
	{
	};
public:
	CCommHeadReq_Type Hda;
};

class CCommHeadResp :
	public ICHeadData
{
public:
	CCommHeadResp(void)
	{
	};
	virtual ~CCommHeadResp(void)
	{
	};
public:
	CCommHeadResp_Type Hda;
public:                               //数据头部和数据体部分数据偏移以及长度
	unsigned int _head_offset;           //数据包头部偏移
	unsigned int _head_len;              //数据包头部大小
	unsigned int _body_offset;           //数据包数据体偏移
	unsigned int _body_len;              //数据包数据体大小
};