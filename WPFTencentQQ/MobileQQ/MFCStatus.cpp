// MFCStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCStatus.h"
#include"resource.h"


// MFCStatus

IMPLEMENT_DYNAMIC(MFCStatus, CStatusBarCtrl)

MFCStatus::MFCStatus()
{

}

MFCStatus::~MFCStatus()
{
}
BEGIN_MESSAGE_MAP(MFCStatus, CStatusBarCtrl)
END_MESSAGE_MAP()

void MFCStatus::SetUI()
{
	this->EnableAutomation();
	CRect rect;
	this->GetWindowRect(&rect);
	
	const int nParts = 4;
	int widths[nParts] = { 100,400,300,-1 };
	this->SetParts(nParts, widths);
	
	this->GetClientRect(&rect);
	rect.left=600;
	rect.left+=2;
	rect.top+=2;
	rect.bottom-=2;
	rect.right-=2;
	this->m_progres.Create(WS_CHILD | WS_VISIBLE,rect,this,IDC_PROGRESS);
	this->m_progres.SetRange32(0,100);
	this->m_progres.SetPos(0);

	Updata(0,0,0);
}

//更新数据窗口
void MFCStatus::Updata(int send,int recv,int abandon)
{
	this->SetText("状态:Ready",0,0);
	CString strStatue;
	strStatue.Format("发送:%d   接收:%d   丢弃:%d",send,recv,abandon);
	this->SetText(strStatue,1,0);
}
//更新用户状态信息
void MFCStatus::UpdataUinStatus(UINT id,CString strName,CString mStatus)
{
	CString strStatue;
	strStatue.Format("%s(%lu): %s",strName,id,mStatus);
	this->SetText(strStatue,3,0);
}

