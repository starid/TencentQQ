#include "StdAfx.h"
#include <WinSock.h>
#include "LoginPack.h"
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include<time.h>
#include"../CipherLib/Md5.h"


unsigned short CLoginPack::wCmd=0x810;

CLoginPack::CLoginPack(void)
{
}

CLoginPack::~CLoginPack(void)
{
}

ByteBuffer CLoginPack::Encode()
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

void CLoginPack::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(0x4));//空字符串
	std::string str=STR_wtlogin_login;
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

void CLoginPack::EncodeBody(CTXCommPack &p)
{
	if(pConfig->mCodePngData.isNeedCode)
	{
		//添加验证码
		p.AddWord(htons(0x0002));
		p.AddWord(htons(0x0004));//0x4个字段
		
		CTXCommPack pack1;
		//添加tlv_t2
		pack1.AddWord(htons(0x0002));
		pack1.AddWord(htons(0x000E));
		pack1.AddDWord(htonl(0x00000004));
		pack1.AddBuf(pConfig->mCodePngData.sIndetifyCode.c_str(),0x4);
		pack1.AddWord(htons(0x0004));
		pack1.AddByteBuffer(pConfig->mCodePngData.sBuf_TLV105);
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//添加tlv_t8
		pack1.AddWord(htons(0x0008));
		pack1.AddWord(htons(0x0008));
		pack1.AddWord(htons(0x0000));
		pack1.AddDWord(htonl(CONST_LCID));
		pack1.AddWord(htons(0x0000));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//添加tlv_t104
		pack1.AddWord(htons(0x0104));
		pack1.AddWord(htons(0x0014));
		pack1.AddByteBuffer(pConfig->mCodePngData.sBuf_TLV104);
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//添加tlv_t116
		pack1.AddWord(htons(0x0116));
		pack1.AddWord(htons(0x000a));
		pack1.AddByte(0);
		pack1.AddDWord(htonl(CONST_mMiscBitmap));
		pack1.AddDWord(htonl(CONST_mSubSigMap));
		pack1.AddByte(0);
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
	}else
	{
		p.AddWord(htons(0x0009));
		p.AddWord(htons(0x0014));//0x14个字段

		CTXCommPack pack1;
		//添加tlv_t18
		pack1.AddWord(htons(0x0018));
		pack1.AddWord(htons(0x0016));
		pack1.AddWord(htons(0x0001));
		pack1.AddDWord(htonl(0x00000600));
		pack1.AddDWord(htonl(CONST_dwUnKnow1));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddDWord(htonl(pConfig->qq_id));
		pack1.AddDWord(htonl(0x00000000));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//添加tlv_t1
		pack1.AddWord(htons(0x0001));
		pack1.AddWord(htons(0x0014));
		pack1.AddWord(htons(0x0001));
		pack1.AddDWord(htonl(0x5f2198ed));//随机
		pack1.AddDWord(htonl(pConfig->qq_id));
		time_t t;
		t=time(0);
		pConfig->ClientTime=t;
		pack1.AddDWord(htonl(pConfig->ClientTime));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddWord(htons(0x0000));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//添加tlv_t106
		pack1.AddWord(htons(0x0003));
		pack1.AddDWord(htonl(0x7e0ffe3f));//随机
		pack1.AddDWord(htonl(0x00000005));
		pack1.AddDWord(htonl(0x00000010));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddDWord(htonl(pConfig->qq_id));
		pack1.AddDWord(htonl(pConfig->ServerTime));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddByte(0x1);
		unsigned char buf[0x10]={0};
		CMd5 md5;
		md5.GetMd5(buf,sizeof(buf),pConfig->qq_pwd,strlen((const char *)pConfig->qq_pwd));
		pack1.AddBuf((char*)buf,sizeof(buf));
		pack1.AddBuf((char*)TGTGT_KEY,sizeof(TGTGT_KEY));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddByte(0x1);

		std::string strImeiMac;
		strImeiMac.append(pConfig->mHardware.DEFAULT_DEVICE_ID);
		strImeiMac.append(pConfig->mHardware.DEFAULT_WIFI_MAC);
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)strImeiMac.c_str(),strImeiMac.size());

		pack1.AddBuf((char*)buf,sizeof(buf));
		pack1.AddDWord(htonl(CONST_FIXAPPID));
		pack1.AddDWord(htonl(0x00000001));
		pack1.AddWord(htons(0x0000));
		//使用KeyAuth加密
		unsigned int bytes=0;
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),pConfig->qq_pwd,strlen((const char *)pConfig->qq_pwd));
		ByteBuffer b;
		b.append(buf,sizeof(buf));
		b.append(htonl(0));
		b.append(htonl(pConfig->qq_id));
		md5.GetMd5(pConfig->KeyAuth,sizeof(pConfig->KeyAuth),(unsigned char *)b.contents(),b.size());
		CTeaCrypt mTea;
		mTea.InitTeaOne();
		unsigned int datalen=pack1.buffer.size()+0x12;
		unsigned char *data=(unsigned char *)malloc(datalen);
		memset(data,0,datalen);
		mTea.Tea_encrypt((unsigned char*)pack1.buffer.contents(),pack1.buffer.size(),pConfig->KeyAuth,data,&datalen);
		pack1.GetBufferOut();
		pack1.AddWord(htons(0x0106));
		pack1.AddWord(htons(0x0070));
		pack1.AddBuf((char*)data,datalen);
		free(data);
		datalen=0;
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t116
		pack1.AddWord(htons(0x0116));
		pack1.AddWord(htons(0x000a));
		pack1.AddByte(0);
		pack1.AddDWord(htonl(CONST_mMiscBitmap));
		pack1.AddDWord(htonl(CONST_mSubSigMap));
		pack1.AddByte(0);
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t100
		pack1.AddWord(htons(0x0100));
		pack1.AddWord(htons(0x0016));
		pack1.AddWord(htons(0x0001));
		pack1.AddDWord(htonl(0x00000005));
		pack1.AddDWord(htonl(0x00000010));
		pack1.AddDWord(htonl(CONST_FIXAPPID));
		pack1.AddDWord(htonl(0x00000000));
		pack1.AddDWord(htonl(CONST_mMainSigMap));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t107
		pack1.AddWord(htons(0x0107));
		pack1.AddWord(htons(0x0006));
		pack1.AddWord(htons(0x0000));
		pack1.AddByte(0x00);
		pack1.AddWord(htons(0x0000));
		pack1.AddByte(0x01);
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t144
		pack1.AddWord(htons(0x0004));		//字段个数
		pack1.AddWord(htons(0x0109));	//tlv_t109
		pack1.AddWord(htons(0x0010));
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)pConfig->mHardware.DEFAULT_DEVICE_ID.c_str(),pConfig->mHardware.DEFAULT_DEVICE_ID.size());
		pack1.AddBuf((char*)buf,sizeof(buf));
		pack1.AddWord(htons(0x0124));	//tlv_t124
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_OS_TYPE.size()+0x2+pConfig->mHardware.DEFAULT_OS_VERSION.size()+0x2+sizeof(pConfig->mHardware.DEFALUT_NETWORK_INT_TYPE)
			+pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size()+0x2+0x2+pConfig->mHardware.DEFAULT_APN.size()+0x2));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_OS_TYPE.size()));
		pack1.AddBuf(pConfig->mHardware.DEFAULT_OS_TYPE.c_str(),pConfig->mHardware.DEFAULT_OS_TYPE.size());
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_OS_VERSION.size()));
		pack1.AddBuf(pConfig->mHardware.DEFAULT_OS_VERSION.c_str(),pConfig->mHardware.DEFAULT_OS_VERSION.size());
		pack1.AddWord(htons(pConfig->mHardware.DEFALUT_NETWORK_INT_TYPE));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.c_str(),pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size());
		pack1.AddWord(htons(0x0000));//空字符串
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_APN.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_APN.c_str(),pConfig->mHardware.DEFAULT_APN.size());
		pack1.AddWord(htons(0x0128));	//tlv_t128
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_BRAND.size()*2+0x1F));
		pack1.AddWord(htons(0x0000));
		pack1.AddByte(0x1);
		pack1.AddByte(0x1);
		pack1.AddByte(0x0);
		pack1.AddDWord(htonl(0x11000000));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_BRAND.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_BRAND.c_str(),pConfig->mHardware.DEFAULT_BRAND.size());
		pack1.AddWord(htons(0x0010));

		strImeiMac.clear();
		strImeiMac.append(pConfig->mHardware.DEFAULT_DEVICE_ID);
		strImeiMac.append(pConfig->mHardware.DEFAULT_WIFI_MAC);
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)strImeiMac.c_str(),strImeiMac.size());

		pack1.AddBuf((char*)buf,sizeof(buf));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_BRAND.size()));
		pack1.AddBuf(pConfig->mHardware.DEFAULT_BRAND.c_str(),pConfig->mHardware.DEFAULT_BRAND.size());
		pack1.AddWord(htons(0x016e));	//tlv_t16e
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_BRAND.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_BRAND.c_str(),pConfig->mHardware.DEFAULT_BRAND.size());
		//使用TGTGT_KEY加密
		datalen=pack1.buffer.size()+0x12;
		data=(unsigned char *)malloc(datalen);
		memset(data,0,datalen);
		mTea.InitTeaOne();
		mTea.Tea_encrypt((unsigned char*)pack1.buffer.contents(),pack1.buffer.size(),TGTGT_KEY,data,&datalen);
		pack1.GetBufferOut();
		pack1.AddWord(htons(0x0144));		
		pack1.AddWord(htons(0x0088));
		pack1.AddBuf((char*)data,datalen);
		free(data);
		datalen=0;
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t142
		pack1.AddWord(htons(0x0142));
		pack1.AddWord(htons(strlen(CONST_APP_N)+0x4));
		pack1.AddWord(htons(0x0000));
		pack1.AddWord(htons(strlen(CONST_APP_N)));
		pack1.AddBuf(CONST_APP_N,strlen(CONST_APP_N));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t145
		pack1.AddWord(htons(0x0145));
		pack1.AddWord(htons(0x0010));

		strImeiMac.clear();
		strImeiMac.append(pConfig->mHardware.DEFAULT_DEVICE_ID);
		strImeiMac.append(pConfig->mHardware.DEFAULT_WIFI_MAC);
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)strImeiMac.c_str(),strImeiMac.size());

		pack1.AddBuf((char*)buf,sizeof(buf));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t154
		pack1.AddWord(htons(0x0154));
		pack1.AddWord(htons(0x0004));
		pack1.AddDWord(htonl(mSeq));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t141
		pack1.AddWord(htons(0x0141));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size()+pConfig->mHardware.DEFAULT_APN.size()+0x8));
		pack1.AddWord(htons(0x0001));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.c_str(),pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME.size());
		pack1.AddWord(htons(pConfig->mHardware.DEFALUT_NETWORK_INT_TYPE));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_APN.size()));
		pack1.AddBuf(pConfig->mHardware.DEFAULT_APN.c_str(),pConfig->mHardware.DEFAULT_APN.size());
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t8
		pack1.AddWord(htons(0x0008));
		pack1.AddWord(htons(0x0008));
		pack1.AddWord(htons(0x0000));
		pack1.AddDWord(htonl(CONST_LCID));
		pack1.AddWord(htons(0x0000));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t16b
		pack1.AddWord(htons(0x016B));
		pack1.AddWord(htons(strlen(CONST_GAME_URL)+strlen(CONST_MAIL_URL)+0x6));
		pack1.AddWord(htons(0x0002));		//URL个数
		pack1.AddWord(htons(strlen(CONST_GAME_URL)));
		pack1.AddBuf(CONST_GAME_URL,strlen(CONST_GAME_URL));
		pack1.AddWord(htons(strlen(CONST_MAIL_URL)));
		pack1.AddBuf(CONST_MAIL_URL,strlen(CONST_MAIL_URL));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t147
		pack1.AddWord(htons(0x0147));
		pack1.AddWord(htons(strlen(CONST_APK_V)+0x18));
		pack1.AddDWord(htonl(CONST_dwUnKnow1));
		pack1.AddWord(htons(strlen(CONST_APK_V)));
		pack1.AddBuf((char*)CONST_APK_V,strlen(CONST_APK_V));
		pack1.AddWord(htons(0x0010));
		pack1.AddBuf((char*)CONST_PkgSig,sizeof(CONST_PkgSig));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t177
		pack1.AddWord(htons(0x0177));
		pack1.AddWord(htons(strlen(CONST_V)+0x7));
		pack1.AddByte(0x1);
		pack1.AddDWord(htonl(CONST_TIME));
		pack1.AddWord(htons(strlen(CONST_V)));
		pack1.AddBuf(CONST_V,strlen(CONST_V));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t187
		pack1.AddWord(htons(0x0187));
		pack1.AddWord(htons(0x0010));
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)pConfig->mHardware.DEFAULT_WIFI_MAC.c_str(),pConfig->mHardware.DEFAULT_WIFI_MAC.size());
		pack1.AddBuf((char*)buf,sizeof(buf));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t188
		pack1.AddWord(htons(0x0188));
		pack1.AddWord(htons(0x0010));
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)pConfig->mHardware.DEFAULT_ANDROID_ID.c_str(),pConfig->mHardware.DEFAULT_ANDROID_ID.size());
		pack1.AddBuf((char*)buf,sizeof(buf));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t191
		pack1.AddWord(htons(0x0191));
		pack1.AddWord(htons(0x0001));
		pack1.AddByte(0x01);
		//tlv_t194
		pack1.AddWord(htons(0x0194));
		pack1.AddWord(htons(0x0010));
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)pConfig->mHardware.DEFAULT_IMSI.c_str(),pConfig->mHardware.DEFAULT_IMSI.size());
		pack1.AddBuf((char*)buf,sizeof(buf));
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
		//tlv_t202
		pack1.AddWord(htons(0x0202));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_SSID.size()+0x14));
		pack1.AddWord(htons(0x0010));
		memset(buf,0,sizeof(buf));
		md5.GetMd5(buf,sizeof(buf),(unsigned char*)pConfig->mHardware.DEFAULT_BSSID.c_str(),pConfig->mHardware.DEFAULT_BSSID.size());
		pack1.AddBuf((char*)buf,sizeof(buf));
		pack1.AddWord(htons(pConfig->mHardware.DEFAULT_SSID.size()));
		pack1.AddBuf((char*)pConfig->mHardware.DEFAULT_SSID.c_str(),pConfig->mHardware.DEFAULT_SSID.size());
		p.AddByteBuffer(pack1.buffer);
		pack1.GetBufferOut();
	}
}