// SearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../NetLib/NetLib.h"
#include"UserMsg.h"
#include"../CCodecWarpper/ClassFactory.h"
#include"../UtilLib/HelpFunc.h"
#include"../CCodecWarpper/SummaryCardRespSearch.h"
#include<iostream>
#include<sstream>


// CSearchDlg 对话框

IMPLEMENT_DYNAMIC(CSearchDlg, CDialogEx)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchDlg::IDD, pParent)
{

}

CSearchDlg::~CSearchDlg()
{
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSearchDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RECEIVED_MSG, &CSearchDlg::OnReceivedMsg)
END_MESSAGE_MAP()


// CSearchDlg 消息处理程序


void CSearchDlg::OnBnClickedButton1()
{
	//SummaryCard.ReqSearch消息
	CPackReq mPack;
	mPack.SetPacketType(SummaryCard_ReqSearch);
	CClassFactory mClassFactory;
	CString strValue;
	strValue="Surreal";
	std::string strKeyWord=strValue;
	unsigned char *dst=NULL;
	unsigned int len=MultiByteToUtf8(strKeyWord.c_str(),strKeyWord.size(),&dst);
	strKeyWord.clear();
	strKeyWord.append((char*)dst,len);
	delete dst;
	dst=NULL;
	CSummaryCardReqSearch mSummaryCardReqSearch;
	mClassFactory.SetCSummaryCardReqSearch(mSummaryCardReqSearch,strKeyWord.c_str(),"+86");//其他信息暂时不进行输入
	mPack.pConfig=pConfig;
	mPack.PackData(&mSummaryCardReqSearch);
	SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
}


afx_msg LRESULT CSearchDlg::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			CSummaryCardRespSearch *pSummaryCardRespSearch=
				static_cast<CSummaryCardRespSearch*>((void*)lParam);
			if(pSummaryCardRespSearch->vvRespServices._value.size()==0)
			{
				CString strFormat;
				strFormat.Format("结果为空");
				//OutputEdit(strFormat);
			}else
			{
				//可以解析结果
				std::string strResult;
				strResult.append((char*)pSummaryCardRespSearch->vSecureSig.value().contents(),
					pSummaryCardRespSearch->vSecureSig.value().size());
				std::stringstream str(strResult);
				std::string sub_str;
				while(std::getline(str,sub_str,','))
				{
					//OutputEdit(sub_str.c_str());
				}
			}
			delete pSummaryCardRespSearch;
			pSummaryCardRespSearch=NULL;
		}break;
	default:
		{
			return 0;
		}break;
	}
	return 0;
}