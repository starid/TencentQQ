#include "StdAfx.h"
#include "StatSvcRegister.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamIn.h"
#include"StreamOut.h"
#include"SvcReqRegister.h"
#include"UniPacket.h"
#include<time.h>
#include"../CipherLib/Md5.h"


CStatSvcRegister::CStatSvcRegister(void)
{
}


CStatSvcRegister::~CStatSvcRegister(void)
{
}


ByteBuffer CStatSvcRegister::Encode()
{
	CTXCommPack p1;
	EncodeHead(p1);
	CTXCommPack p2;
	EncodeBody(p2);

	mPack.AddByteBuffer(p1.buffer);
	p1.GetBufferOut();
	mPack.AddByteBuffer(p2.buffer);
	p2.GetBufferOut();

	return mPack.buffer;
}

void CStatSvcRegister::EncodeHead(CTXCommPack &p)
{
	switch(pConfig->mRegisterCmd)
	{
	case CmdOnLine:
	case CmdOffLine:
		{
			std::string str=STR_StatSvc_register;
			p.AddDWord(htonl(0x4+str.size()));
			p.AddBuf(str.c_str(),str.size());
			p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
			p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
			p.AddLenDWord();
		}break;
	case CmdHeartBeat:
		{
			p.AddDWord(htonl(mSeq));//Seq
			p.AddDWord(htonl(CONST_FIXAPPID));
			p.AddDWord(htonl(CONST_FIXAPPID));
			p.AddByte(0x67);
			char buf[0xB]={0};
			p.AddBuf(buf,sizeof(buf));
			p.AddDWord(htonl(sizeof(pConfig->tgt)+0x4));//添加tgt
			p.AddBuf((char*)pConfig->tgt,sizeof(pConfig->tgt));
			std::string str=STR_friendlist_GetTroopListReqV2;
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
	}
}

void CStatSvcRegister::EncodeBody(CTXCommPack &p)
{
	//添加UniPacket
	CStreamOut mStream1;
	//封装SvcReqRegister
	CSvcReqRegister mSvcReq;
	mSvcReq.lUin.value(pConfig->qq_id);
	switch(pConfig->mRegisterCmd)
	{
	case CmdOnLine:
		{
			mSvcReq.lBid.value(0x7);
			mSvcReq.iStatus.value(0xb);
			mSvcReq.bIsOnline.value(0x1);
			//mSvcReq.bKikPC.value(0x1);
			mSvcReq.bOnlinePush.value(0x1);
			mSvcReq.bIsShowOnline.value(0x1);
			time_t t;
			t=time(0);
			mSvcReq.iLargeSeq.value(t);//当前时间
		}break;
	case CmdOffLine:
		{
			mSvcReq.iStatus.value(0x15);
			mSvcReq.timeStamp.value(pConfig->mSvcRespRegister.timeStamp.value());//上线时返回
		}break;
	case CmdHeartBeat:
		{
			mSvcReq.lBid.value(0x7);
			mSvcReq.iStatus.value(0xb);
			mSvcReq.timeStamp.value(pConfig->mSvcRespRegister.timeStamp.value());//上线时返回
			time_t t;
			t=time(0);
			mSvcReq.iLargeSeq.value(t);//当前时间
		}break;
	}
	mSvcReq.iOSVersion.value(pConfig->mHardware.DEFAULT_OS_INT_VERSION);
	mSvcReq.cNetType.value(pConfig->mHardware.DEFALUT_NETWORK_INT_TYPE);//此处为，数据包中为1
	ByteBuffer bt;
	std::string strImeiMac;
	strImeiMac.append(pConfig->mHardware.DEFAULT_DEVICE_ID);
	strImeiMac.append(pConfig->mHardware.DEFAULT_WIFI_MAC);
	unsigned char md5[0x10]={0};
	CMd5 mMd5;
	mMd5.GetMd5(md5,sizeof(md5),(unsigned char*)strImeiMac.c_str(),strImeiMac.size());
	bt.append(md5,sizeof(md5));
	mSvcReq.vecGuid.value(bt);
	mSvcReq.iLocaleID.value(CONST_LCID);
	mSvcReq.strDevName.value(pConfig->mHardware.DEFAULT_BRAND);
	mSvcReq.strDevType.value(pConfig->mHardware.DEFAULT_BRAND);
	mSvcReq.strOSVer.value(pConfig->mHardware.DEFAULT_OS_VERSION);
	mSvcReq.bOpenPush.value(0x1);

	mStream1.write(&mSvcReq,0);

	JCE::JCEString key1;
	key1.value("SvcReqRegister");
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	JCE::JCEMap	Map1;
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&key1,p2));
	mStream1.clearbs();
	mStream1.write(&Map1,0);

	std::map<std::string,std::string> a;			//空map
	UniPacket mUniPacket(3,0,0,0,"PushService","SvcReqRegister",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}

void CStatSvcRegister::DecodeBody(const ByteBuffer &bt,CSvcRespRegister& mRetPack)
{
	UniPacket mUniPacket;
	mUniPacket.decode((char*)bt.contents(),bt.size());

	if(mUniPacket._package.sBuffer.value().size()!=0)
	{
		JCE::JCEMap mMap;
		CStreamIn mStreamIn;
		mStreamIn.wrap((unsigned char*)mUniPacket._package.sBuffer.value().contents(),
			mUniPacket._package.sBuffer.value().size());
		mStreamIn.read(&mMap,0,true);
		JCE::JCEString *mKey=new JCE::JCEString();
		mKey->value("SvcRespRegister");
		JCE::JCEMap *pMap=static_cast<JCE::JCEMap*>(mMap._value[mKey]);
		mKey->value("QQService.SvcRespRegister");
		JCE::JCEByteArray *pList=static_cast<JCE::JCEByteArray *>(pMap->_value[mKey]);
		delete mKey;
		mStreamIn.clearbs();
		mStreamIn.wrap((unsigned char*)pList->value().contents(),pList->value().size());
		mRetPack.readFrom(mStreamIn);
	}
}