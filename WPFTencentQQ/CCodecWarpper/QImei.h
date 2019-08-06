#pragma once
#include"../JceProtocol/JceInputStream.h"
#include"../JceProtocol/JceOutputStream.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JceStruct.h"

//原型com.tencent.beacon.c.a.c
class QImei:public JCE::CJceStruct
{
public:
	QImei(void);
	virtual ~QImei(void);
private:
	JCE::JCEChar	a;
	JCE::JCEInt		b;
	JCE::JCEByteArray	c;		//处理Lcom/tencent/beacon/b/a;->b([BIILjava/lang/String;)[B
	JCE::JCEString		d;
	JCE::JCEChar		e;		//-1表示无加密，1代表DES加密，3代表AES加密
	JCE::JCEChar		f;		//-1代表无压缩，1 zip压缩，2代表gzip压缩
	JCE::JCELong		g;
	JCE::JCEString		h;
	JCE::JCEString		i;		//DES或者AES密钥，当为AES密钥时，其后填充字符“0”（0x30）至16字节
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	JCE::JCEString	Geti(){return i;};
	JCE::JCEByteArray	Getc(){return c;};
};

