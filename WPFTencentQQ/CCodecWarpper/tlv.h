#pragma once
#include"../UtilLib/ByteBuffer.h"

typedef struct
{
	unsigned short wLen;	//0x14（总长度）
	ByteBuffer sBuf;
}tlv_t104;

typedef struct
{
	unsigned short wLen;//总长度
	unsigned short wLen2;
	ByteBuffer   sBuf;	//未知数据
	unsigned short wLen3;
	ByteBuffer  sPicBuf;	//验证码图片数据
}tlv_t105;