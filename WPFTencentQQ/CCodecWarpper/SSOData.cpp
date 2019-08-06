#include "StdAfx.h"
#include "SSOData.h"
#include "../CipherLib/TeaCrypt.h"
#include "../MobileQQ/protocol_type.h"


CSSOData::CSSOData(void)
{
}


CSSOData::~CSSOData(void)
{
}

void CSSOData::init(int,char const *,char,int,int,int,char const *,char const *,char const *,char const *,std::string&,
		char const *,char const *,int,char const *,int,int,int)
{
}

void CSSOData::serialize(std::string& mStr)
{
	mSSOReqHead.serialize(mStr);

	//加密

	mSSOHead.serialize(mStr,0);
}

void CSSOData::deSerialize(ByteBuffer &mBuffer,bool b)
{
	if(mBuffer.size()-mBuffer.rpos()<3)
		return;
	int retLen=0;
	mSSOHead.deSerialize(mBuffer,retLen);
	//解密数据
	CTeaCrypt mTeaCrypt;
	mTeaCrypt.InitTeaOne();
	unsigned char *dst=NULL;
	unsigned int bytes=0;
	mTeaCrypt.Tea_decrypt((unsigned char*)mBuffer.contents(),mBuffer.size()-mBuffer.rpos(),Key0,&dst,&bytes);

	mBuffer.clear();
	mBuffer.append(dst,bytes);		//重新安装数据
	free(dst);dst=NULL;bytes=0;

	mSSOReqHead.deSerialize(mBuffer,retLen);

}