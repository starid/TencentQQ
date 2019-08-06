#pragma once
#include"ICHeadData.h"
#include"Packet.h"


struct CLoginHeadReq_Type0825
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
	unsigned int unknown3;
	unsigned char key[0x10];
};

struct CLoginHeadReq_Type0836
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
	unsigned int unknown3;
};

struct CLoginHeadReq_Type0104
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
	unsigned int unknown3;
	unsigned char key[0x10];
};

struct CLoginHeadReq_Type00BA
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
	unsigned int unknown3;
	unsigned char key[0x10];
};

struct COnlineHeadReq_Type0828
{
	unsigned short version;       //未知，可能为应用软件版本
	unsigned short code;          //CODE_0825,CODE_0836,CODE_0828等数值
	unsigned short serial;          //包序号
	unsigned int   qq_id;          //QQ号码
	unsigned char fix[3];          //3字节填充数据
	unsigned int unknown1;
	unsigned int unknown2;
};

class CLoginPingHeadReq :
	public ICHeadData
{
public:
	CLoginPingHeadReq(void)
	{
	};
	virtual ~CLoginPingHeadReq(void)
	{
	};
public:
	CLoginHeadReq_Type0825 Hda;
};

class CLoginVerifyHeadReq :
	public ICHeadData
{
public:
	CLoginVerifyHeadReq(void)
	{
	};
	virtual ~CLoginVerifyHeadReq(void)
	{
	};
public:
	CLoginHeadReq_Type0836 Hda;
};

class CLoginTipHeadReq:
	public ICHeadData
{
public:
	CLoginTipHeadReq(void)
	{
	};
	virtual ~CLoginTipHeadReq(void)
	{
	};
public:
	CLoginHeadReq_Type0104 Hda;
};

class CLoginCodeHeadReq:
	public ICHeadData
{
public:
	CLoginCodeHeadReq(void)
	{
	};
	virtual ~CLoginCodeHeadReq(void)
	{
	};
public:
	CLoginHeadReq_Type00BA Hda;
};

class COnlineHeadReq :
	public ICHeadData
{
public:
	COnlineHeadReq(void)
	{
	};
	virtual ~COnlineHeadReq(void)
	{
	};
public:
	COnlineHeadReq_Type0828 Hda;
};
