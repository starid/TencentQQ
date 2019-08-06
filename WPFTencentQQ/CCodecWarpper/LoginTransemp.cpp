#include "StdAfx.h"
#include "LoginTransemp.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include<time.h>
#include"../CipherLib/Md5.h"
#include"ReportT1.h"
#include"../UtilLib/HelpFunc.h"
#include"../UtilLib/inflate.h"


unsigned short CLoginTransemp::wCmd=0x812;


CLoginTransemp::CLoginTransemp(void)
{
}


CLoginTransemp::~CLoginTransemp(void)
{
}

ByteBuffer CLoginTransemp::Encode()
{
	CTXCommPack p1;
	EncodeHead(p1);
	CTXCommPack p2;
	EncodeBody(p2);

	//对p2加密
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	unsigned int datalen=p2.buffer.size()+0x12;
	unsigned char *data=(unsigned char *)malloc(datalen);
	memset(data,0,datalen);
	mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->ecdh_key,data,&datalen);

	p2.GetBufferOut();
	p2.AddByte(0x2);//开始标志
	p2.AddWord(htons(datalen+0x4C));
	p2.AddWord(htons(CONST_wUnKnow2));
	p2.AddWord(htons(wCmd));
	p2.AddWord(htons(0x0001));
	p2.AddDWord(htonl(pConfig->qq_id));
	p2.AddByte(0x3);
	p2.AddByte(0x7);
	p2.AddByte(0x00);
	p2.AddDWord(htonl(0x00000002));
	p2.AddDWord(htonl(0x00000000));
	p2.AddDWord(htonl(0x00000000));
	p2.AddWord(htons(0x0101));
	p2.AddBuf((char*)KeyLogin,sizeof(KeyLogin));
	p2.AddWord(htons(0x0102));
	p2.AddWord(htons(0x0019));
	p2.AddBuf((char*)pConfig->stKey,sizeof(pConfig->stKey));
	//添加加密数据
	p2.AddBuf((char*)data,datalen);
	free(data);
	datalen=0;
	p2.AddByte(0x3);  //结束标志
	p2.AddLenDWord();

	mPack.AddByteBuffer(p1.buffer);
	p1.GetBufferOut();
	mPack.AddByteBuffer(p2.buffer);
	p2.GetBufferOut();

	return mPack.buffer;
}

void CLoginTransemp::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(sizeof(pConfig->tgt)+0x4));//添加tgt
	p.AddBuf((char*)pConfig->tgt,sizeof(pConfig->tgt));

	std::string str=STR_wtlogin_trans_emp;
	p.AddDWord(htonl(0x4+str.size()));
	p.AddBuf(str.c_str(),str.size());
	p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
	p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
	p.AddDWord(htonl(0x4+pConfig->mHardware.DEFAULT_DEVICE_ID.size()));
	p.AddBuf(pConfig->mHardware.DEFAULT_DEVICE_ID.c_str(),pConfig->mHardware.DEFAULT_DEVICE_ID.size());
	p.AddDWord(htonl(0x4));//空字符串
	CTXCommPack pack;
	pack.AddByte('|');
	pack.AddBuf(pConfig->mHardware.DEFAULT_IMSI.c_str(),pConfig->mHardware.DEFAULT_IMSI.size());
	pack.AddByte('|');
	str=CONST_QQ_VERSION;
	pack.AddBuf(str.c_str(),str.size());
	p.AddWord(htons(0x2+pack.buffer.size()));
	p.AddBuf((char*)pack.buffer.contents(),pack.buffer.size());
	pack.GetBufferOut();
	p.AddLenDWord();
}

void CLoginTransemp::EncodeBody(CTXCommPack &p)
{
	//先组装KEY_SHARE加密数据
	p.AddByte(0x1);

	//添加压缩json数据
	unsigned int dstlen=2*sizeof(pConfig->ksid);
	unsigned char *dst=(unsigned char*)malloc(dstlen);
	if(NULL==dst) return;
	HexToStr(pConfig->ksid,sizeof(pConfig->ksid),dst);
	std::string strKsid;
	strKsid.append((char*)dst,dstlen);
	free(dst);
	std::string strFixAppid;
	dst=(unsigned char*)malloc(20);
	ultoa(CONST_FIXAPPID,(char*)dst,10);
	strFixAppid=(char*)dst;
	free(dst);
	std::string strEmail;
	dst=(unsigned char*)malloc(20);
	ultoa(pConfig->qq_id,(char*)dst,10);
	strEmail=(char*)dst;
	free(dst);
	//再次生成ClientTime（覆盖）
	time_t t;
	t=time(0);
	pConfig->ClientTime=t;
	std::string strTime;
	dst=(unsigned char*)malloc(20);
	ultoa(pConfig->ClientTime,(char*)dst,10);
	strTime=(char*)dst;
	free(dst);
	std::string strOper;
	strOper.append(pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.c_str(),pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size());
	CReportT1 mReportT1(strKsid,strFixAppid,strEmail,strTime,strOper,pConfig);
	std::string strJson=mReportT1.toJasonObj();
	//压缩json
	Bytef odata[BUF_SIZE];
	uLong nodata = BUF_SIZE;
	zcompress((Bytef*)strJson.data(),strJson.size(),odata,&nodata);
	CTXCommPack pack1;
	pack1.AddDWord(htonl(pConfig->ServerTime));
	pack1.AddByte(0);
	pack1.AddByte(1);
	pack1.AddWord(htons(nodata));
	pack1.AddBuf((char*)odata,nodata);
	//st_key加密
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	unsigned int datalen=pack1.buffer.size()+0x12;
	unsigned char *data=(unsigned char *)malloc(datalen);
	memset(data,0,datalen);
	mTea.Tea_encrypt((unsigned char*)pack1.buffer.contents(),pack1.buffer.size(),pConfig->st_key,data,&datalen);
	pack1.GetBufferOut();

	p.AddWord(htons(datalen));
	p.AddDWord(htonl(0x00000010));
	p.AddDWord(htonl(0x00000055));
	p.AddWord(htons(sizeof(pConfig->st)));
	p.AddBuf((char*)pConfig->st,sizeof(pConfig->st));
	p.AddByte(0);
	p.AddBuf((char*)data,datalen);
	free(data);
	datalen=0;
}