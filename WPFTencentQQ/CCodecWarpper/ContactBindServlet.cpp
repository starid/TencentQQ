#include "StdAfx.h"
#include "ContactBindServlet.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamIn.h"
#include"StreamOut.h"
#include"UniPacket.h"
#include"RequestBindMobile.h"
#include"RequestHeader.h"
#include"RequestQueryQQBindingStat.h"
#include"RequestQueryQQMobileContactsV3.h"
#include"RequestUpdateAddressBook.h"
#include"RequestUploadAddressBookV2.h"
#include"RequestUploadAddressBook.h"


CContactBindServlet::CContactBindServlet(void)
{
}


CContactBindServlet::~CContactBindServlet(void)
{
}

ByteBuffer CContactBindServlet::Encode(unsigned int type)
{
	CTXCommPack p1;
	EncodeHead(p1,type);
	CTXCommPack p2;
	EncodeBody(p2,type);

	mPack.AddByteBuffer(p1.buffer);
	p1.GetBufferOut();
	mPack.AddByteBuffer(p2.buffer);
	p2.GetBufferOut();

	return mPack.buffer;
}

void CContactBindServlet::EncodeHead(CTXCommPack &p,unsigned int type)
{
	std::string strValue;
	switch(type)
	{
	case account_RequestBindMobile:
		{
			strValue=STR_account_RequestBindMobile;
		}break;
	case account_RequestCancelBindMobile:
		{
			strValue=STR_account_RequestCancelBindMobile;
		}break;
	case account_RequestQueryQQBindingStat:
		{
			strValue=STR_account_RequestQueryQQBindingStat;
		}break;
	case account_RequestQueryQQMobileContactsV3:
		{
			strValue=STR_account_RequestQueryQQMobileContactsV3;
		}break;
	case account_RequestUpdateAddressBook:
		{
			strValue=STR_account_RequestUpdateAddressBook;
		}break;
	case account_RequestUploadAddressBook:
		{
			strValue=STR_account_RequestUploadAddressBook;
		}break;
	case account_RequestUploadAddressBookV2:
		{
			strValue=STR_account_RequestUploadAddressBookV2;
		}break;
	case account_RequestVerifyBindingSmscode:
		{
			strValue=STR_account_RequestVerifyBindingSmscode;
		}break;
	}
	p.AddDWord(htonl(0x4+strValue.size()));
	p.AddBuf(strValue.c_str(),strValue.size());
	p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
	p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
	p.AddLenDWord();
}

void CContactBindServlet::EncodeBody(CTXCommPack &p,unsigned int type)
{
	JCE::JCEString strKey1;
	JCE::JCEString strKey2;
	std::string sServantName;
	std::string sFuncName;
	short sCmd=0;
	JCE::CJceStruct* pBody;

	CRequestQueryQQBindingStat mRequestQueryQQBindingStat;
	CRequestQueryQQMobileContactsV3 mRequestQueryQQMobileContactsV3;
	CRequestUpdateAddressBook mRequestUpdateAddressBook;
	CRequestUploadAddressBookV2 mRequestUploadAddressBookV2;
	CRequestUploadAddressBook mRequestUploadAddressBook;
	switch(type)
	{
	case account_RequestBindMobile:
		{
			strKey1.value("RequestBindMobile");
			strKey2.value("RequestHeader");
			pBody=&pConfig->mRequestBindMobile;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0xd;
		}break;
	case account_RequestCancelBindMobile:
		{
			strKey1.value("RequestCancelBindMobile");
			strKey2.value("RequestHeader");
			pBody=&pConfig->mRequestCancelBindMobile;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0x14;
		}break;
	case account_RequestQueryQQBindingStat:
		{
			strKey1.value("RequestQueryQQBindingStat");
			strKey2.value("RequestHeader");
			std::string strIMEI_UNIQUENO=pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO;
			mRequestQueryQQBindingStat.MobileUniqueNo.value(strIMEI_UNIQUENO);
			pBody=&mRequestQueryQQBindingStat;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0xc;
		}break;
	case account_RequestQueryQQMobileContactsV3:
		{
			strKey1.value("RequestQueryQQMobileContactsV3");
			strKey2.value("RequestHeader");
			mRequestQueryQQMobileContactsV3.queryFlag.value(1);
			mRequestQueryQQMobileContactsV3.Compressd.value(false);
			mRequestQueryQQMobileContactsV3.OmitOffline.value(true);
			std::string strIMEI_UNIQUENO=pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO;
			mRequestQueryQQMobileContactsV3.MobileUniqueNo.value(strIMEI_UNIQUENO);
			pBody=&mRequestQueryQQMobileContactsV3;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0x1E;
		}break;
	case account_RequestUpdateAddressBook:
		{
			strKey1.value("RequestUpdateAddressBook");
			strKey2.value("RequestHeader");
			mRequestUpdateAddressBook.nextFlag.value(0xFFFFFFFF);
			std::string strIMEI_UNIQUENO=pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO;
			mRequestUpdateAddressBook.MobileUniqueNo.value(strIMEI_UNIQUENO);
			for(int i=0;i<pConfig->mListCAddressBookItem.size();i++)
			{
				CAddressBookItem *p1=new CAddressBookItem();
				p1->mobileNo.value(pConfig->mListCAddressBookItem[i].mobileNo.value());
				p1->name.value(pConfig->mListCAddressBookItem[i].name.value());
				mRequestUpdateAddressBook.AddressBookAddList._value.push_back(p1);
			}
			pBody=&mRequestUpdateAddressBook;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0xf;
		}break;
	case account_RequestUploadAddressBook:
		{
			strKey1.value("RequestUploadAddressBook");
			strKey2.value("RequestHeader");
			mRequestUploadAddressBook.nextFlag.value(0xFFFFFFFF);
			std::string strIMEI_UNIQUENO=pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO;
			mRequestUploadAddressBook.MobileUniqueNo.value(strIMEI_UNIQUENO);

			for(int i=0;i<pConfig->mListCAddressBookItem.size();i++)
			{
				CAddressBookItem *p1=new CAddressBookItem();
				p1->mobileNo.value(pConfig->mListCAddressBookItem[i].mobileNo.value());
				p1->name.value(pConfig->mListCAddressBookItem[i].name.value());
				mRequestUploadAddressBook.AddressBookList._value.push_back(p1);
			}
			pBody=&mRequestUploadAddressBook;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0xe;
		}break;
	case account_RequestUploadAddressBookV2:
		{
			strKey1.value("RequestUploadAddressBookV2");
			strKey2.value("RequestHeader");
			mRequestUploadAddressBookV2.nextFlag.value(0xFFFFFFFF);
			std::string strIMEI_UNIQUENO=pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO;
			mRequestUploadAddressBookV2.MobileUniqueNo.value(strIMEI_UNIQUENO);

			for(int i=0;i<pConfig->mListCAddressBookItem.size();i++)
			{
				CAddressBookItem *p1=new CAddressBookItem();
				p1->mobileNo.value(pConfig->mListCAddressBookItem[i].mobileNo.value());
				p1->name.value(pConfig->mListCAddressBookItem[i].name.value());
				mRequestUploadAddressBookV2.AddressBookList._value.push_back(p1);
			}
			pBody=&mRequestUploadAddressBook;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0x1f;
		}break;
	case account_RequestVerifyBindingSmscode:
		{
			strKey1.value("RequestVerifySmscode");
			strKey2.value("RequestHeader");
			pBody=&pConfig->mRequestVerifyBindingSmscode;
			sServantName="AccountServer";
			sFuncName="AccountServerFunc";
			sCmd=0x10;
		}break;
	}

	//Ìí¼ÓUniPacket
	CStreamOut mStream1;
	//·â×°Body
	mStream1.write(pBody,0);
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	JCE::JCEMap	Map1;
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&strKey1,p2));
	mStream1.clearbs();
	//·â×°RequestHeader
	CRequestHeader mRequestHeader(100,sCmd,0,0,"",0,"","","",0,0);
	mStream1.write(&mRequestHeader,0);
	p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&strKey2,p2));
	mStream1.clearbs();
	mStream1.write(&Map1,0);

	std::map<std::string,std::string> a;			//¿Õmap
	UniPacket mUniPacket(3,0,0,0,sServantName,sFuncName,mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}

void CContactBindServlet::DecodeBody(const ByteBuffer &bt,unsigned int type,JCE::CJceStruct* pRetPack)
{
	JCE::JCEString *mKey=new JCE::JCEString();
	switch(type)
	{
	case account_RequestBindMobile:
		{
			mKey->value("ResponeBindMobile");
		}break;
	case account_RequestCancelBindMobile:
		{
			return;
		}break;
	case account_RequestQueryQQBindingStat:
		{
			mKey->value("RespondQueryQQBindingStat");
		}break;
	case account_RequestQueryQQMobileContactsV3:
		{
			mKey->value("ResponeQueryQQMobileContactsV3");
		}break;
	case account_RequestUpdateAddressBook:
		{
			mKey->value("ResponeUpdateAddressBook");
		}break;
	case account_RequestUploadAddressBook:
		{
			mKey->value("ResponeUploadAddressBook");
		}break;
	case account_RequestUploadAddressBookV2:
		{
			mKey->value("ResponeUploadAddressBookV2");
		}break;
	case account_RequestVerifyBindingSmscode:
		{
			mKey->value("ResponeVerifySmscode");
		}break;
	}
	UniPacket mUniPacket;
	mUniPacket.decode((char*)bt.contents(),bt.size());
	if(mUniPacket._package.sBuffer.value().size()!=0)
	{
		JCE::JCEMap mMap;
		CStreamIn mStreamIn;
		mStreamIn.wrap((unsigned char*)mUniPacket._package.sBuffer.value().contents(),
			mUniPacket._package.sBuffer.value().size());
		mStreamIn.read(&mMap,0,true);
		JCE::JCEByteArray *pList=static_cast<JCE::JCEByteArray *>(mMap._value[mKey]);
		if(pList==NULL)
		{
			return;
		}
		mStreamIn.clearbs();
		mStreamIn.wrap((unsigned char*)pList->value().contents(),pList->value().size());
		mStreamIn.read(pRetPack,0,true);
	}
	delete mKey;
}
