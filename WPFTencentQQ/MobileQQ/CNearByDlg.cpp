// CNearByDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CNearByDlg.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/ClassFactory.h"
#include<NetLib.h>
#include"../CCodecWarpper/ReqGetEncounterV2.h"
#include"SeqSerial.h"


// CCNearByDlg 对话框

IMPLEMENT_DYNAMIC(CCNearByDlg, CDialogEx)

CCNearByDlg::CCNearByDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCNearByDlg::IDD, pParent)
{

}

CCNearByDlg::~CCNearByDlg()
{
}

void CCNearByDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, mList1);
}


BEGIN_MESSAGE_MAP(CCNearByDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCNearByDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCNearByDlg 消息处理程序


BOOL CCNearByDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	char  _column[][20]={"序号","QQ","用户名","其他"};
	mList1.Clear();
	mList1.SetHeaders(_column,sizeof(_column)/sizeof(*_column));
	return TRUE;
}

//查询功能
void CCNearByDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CPackReq mPack;
	mPack.SetPacketType(EncounterSvc_ReqGetEncounter);
	CReqGetEncounterV2 mReqGetEncounterV2;
	CClassFactory mClassFactory;
	mClassFactory.SetCReqGetEncounterV2(mReqGetEncounterV2);
	CSeqSerial	mSeqSerial;
	mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::default_func));
	mPack.pConfig=pConfig;
	mPack.PackData(&mReqGetEncounterV2);
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}
