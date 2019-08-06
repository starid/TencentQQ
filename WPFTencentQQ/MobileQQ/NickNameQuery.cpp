// NickNameQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "NickNameQuery.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../NetLib/NetLib.h"
#include"UserMsg.h"
#include"../UtilLib/HelpFunc.h"
#include"../CCodecWarpper/ResponeUploadAddressBookV2.h"
#include"../CCodecWarpper/MobileContactsFriendInfo.h"
#include"../CCodecWarpper/MobileContactsNotFriendInfo.h"


// CNickNameQuery 对话框

IMPLEMENT_DYNAMIC(CNickNameQuery, CDialogEx)

CNickNameQuery::CNickNameQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNickNameQuery::IDD, pParent)
{

}

CNickNameQuery::~CNickNameQuery()
{
}

void CNickNameQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, mEditPhoneNos);
}


BEGIN_MESSAGE_MAP(CNickNameQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNickNameQuery::OnBnClickedButton1)
END_MESSAGE_MAP()


// CNickNameQuery 消息处理程序


void CNickNameQuery::OnBnClickedButton1()
{

	int nLineCount=mEditPhoneNos.GetLineCount();
	CString strText, strLine;
	for (int i=0; i < nLineCount; i++)
	{
		// length of line i:
		int len = mEditPhoneNos.LineLength(mEditPhoneNos.LineIndex(i));
		if(len==0) break;
		mEditPhoneNos.GetLine(i, strText.GetBuffer(len), len);
		strText.ReleaseBuffer(len);
		CAddressBookItem m1;
		m1.mobileNo.value(strText.GetBuffer(0));
		m1.name.value("chenjinglan");
		pConfig->mListCAddressBookItem.push_back(m1);
	}

	if(pConfig->mListCAddressBookItem.size()==0)
	{
		AfxMessageBox("输入为空");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestUploadAddressBookV2);//account_RequestUploadAddressBookV2,account_RequestUpdateAddressBook
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
}

afx_msg LRESULT CNickNameQuery::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			CResponeUploadAddressBookV2 *pResponeUploadAddressBookV2=
				static_cast<CResponeUploadAddressBookV2*>((void*)lParam);
			if(pResponeUploadAddressBookV2->BindFriendContacts._value.size()==0&&
				pResponeUploadAddressBookV2->BindNotFriendContacts._value.size()==0)
			{
				CString strFormat;
				strFormat.Format("查询结果为空");
				//OutputEdit(strFormat);
			}else
			{
				if(pResponeUploadAddressBookV2->BindFriendContacts._value.size()!=0)
				{
					std::list<JCE::IObject*>::iterator iter;
					for(iter=pResponeUploadAddressBookV2->BindFriendContacts._value.begin();
						iter!=pResponeUploadAddressBookV2->BindFriendContacts._value.end();iter++)
					{
						CString strFormat;
						strFormat.Format("%s",static_cast<CMobileContactsFriendInfo*>(*iter)->QQ.value().c_str());
						//OutputEdit(strFormat);
					}
				}
				if(pResponeUploadAddressBookV2->BindNotFriendContacts._value.size()!=0)
				{
					std::list<JCE::IObject*>::iterator iter;
					for(iter=pResponeUploadAddressBookV2->BindNotFriendContacts._value.begin();
						iter!=pResponeUploadAddressBookV2->BindNotFriendContacts._value.end();iter++)
					{
						CString strFormat;
						std::string strNickName=static_cast<CMobileContactsNotFriendInfo*>(*iter)->nickname.value();
						unsigned char *dst=NULL;
						unsigned int len=Utf8ToMultiByte(strNickName.c_str(),strNickName.size(),&dst);
						strNickName.clear();
						strNickName.append((char*)dst,len);
						delete dst;
						dst=NULL;
						strFormat.Format("%s",strNickName.c_str());
						//OutputEdit(strFormat);
					}
				}
			}
			delete pResponeUploadAddressBookV2;
			pResponeUploadAddressBookV2=NULL;
		}break;
	default:
		{
			return 0;
		}break;
	}
	return 0;
}