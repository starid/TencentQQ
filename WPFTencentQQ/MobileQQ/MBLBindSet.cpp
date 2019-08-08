// MBLBindSet.cpp : 实现文件
//

#include "stdafx.h"
#include "MBLBindSet.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/ResponeVerifySmscode.h"
#include"../CCodecWarpper/ResponeBindMobile.h"
#include"UserMsg.h"


// CMBLBindSet 对话框

IMPLEMENT_DYNAMIC(CMBLBindSet, CDialogEx)

CMBLBindSet::CMBLBindSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMBLBindSet::IDD, pParent)
{

}

CMBLBindSet::~CMBLBindSet()
{
}

void CMBLBindSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEditPhoneNo);
	DDX_Control(pDX, IDC_EDIT2, mEditCheckNo);
}


BEGIN_MESSAGE_MAP(CMBLBindSet, CDialogEx)
	ON_MESSAGE(WM_RECEIVED_MSG, &CMBLBindSet::OnReceivedMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CMBLBindSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &CMBLBindSet::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &CMBLBindSet::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMBLBindSet 消息处理程序

afx_msg LRESULT CMBLBindSet::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			CResponeBindMobile *pResponeBindMobile=static_cast<CResponeBindMobile*>((void*)lParam);

			if(pResponeBindMobile->alreadyBindedUin.value().size()==0)
			{
				if(pResponeBindMobile->sessionSid.value().size()==0)
				{
					//登陆QQ号码已绑定手机号码，请先解除绑定或者切换登陆未绑定QQ号码
					CString strFormat;
					strFormat.Format("未查询到结果");
					AfxMessageBox(strFormat);
				}else
				{
					//登陆QQ号码未绑定，且目标手机号码未绑定任何QQ号码
					std::string strMobileNo;
					strMobileNo.append((char*)pResponeBindMobile->sessionSid.value().contents(),pResponeBindMobile->sessionSid.value().size());
					strsessionSid=strMobileNo;
					CString strFormat;
					strFormat.Format("目标手机号码%s未绑定任何QQ",strMobileNo.c_str());
					AfxMessageBox(strFormat);
				}
			}else
			{
				//登陆QQ号码未绑定，且目标手机号码已绑定QQ号码
				CString strFormat;
				strFormat.Format("已绑定账号:%s",pResponeBindMobile->alreadyBindedUin.value().c_str());
				AfxMessageBox(strFormat);
			}
			delete pResponeBindMobile;
			pResponeBindMobile=NULL;
		}break;
	case 1:
		{
			CResponeVerifySmscode *pResponeVerifySmscode=
				static_cast<CResponeVerifySmscode*>((void*)lParam);
			if(pResponeVerifySmscode->sessionSid.value().size()==0)
			{
				CString strFormat;
				strFormat.Format("绑定失败");
				AfxMessageBox(strFormat);
			}else
			{
				CString strFormat;
				strFormat.Format("绑定成功");
				AfxMessageBox(strFormat);
			}
			delete pResponeVerifySmscode;
			pResponeVerifySmscode=NULL;
		}break;
	case 2:
		{
			AfxMessageBox("解除绑定成功");
		}break;
	default:
		{
			return 0;
		}break;
	}
	return 0;
}

//绑定设置
void CMBLBindSet::OnBnClickedButton1()
{
	CString str;
	this->mEditCheckNo.GetWindowTextA(str);
	if(str.GetLength()==0)
	{
		AfxMessageBox("验证码为空");
		return;
	}
	if(strsessionSid.size()==0)
	{
		AfxMessageBox("请先查询目标手机号码是否绑定");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestVerifyBindingSmscode);
	pConfig->mRequestVerifyBindingSmscode.smsCode.value(str.GetBuffer());
	ByteBuffer bt;
	bt.append(strsessionSid.c_str(),strsessionSid.size());
	pConfig->mRequestVerifyBindingSmscode.sessionSid.value(bt);
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

//解除绑定
void CMBLBindSet::OnBnClickedButton8()
{
	if(pConfig->mRequestCancelBindMobile.mobileNo.value().size()==0||
		pConfig->mRequestCancelBindMobile.nationCode.value().size()==0)
	{
		AfxMessageBox("请先查询登陆号码绑定状态");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestCancelBindMobile);
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

//验证
void CMBLBindSet::OnBnClickedButton2()
{
	CString str1;
	mEditPhoneNo.GetWindowTextA(str1);
	if(str1.GetLength()==0)
	{
		AfxMessageBox("输入号码为空");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestBindMobile);
	mPack.pConfig=pConfig;
	mPack.pConfig->mRequestBindMobile.mobileNo.value("+86");
	mPack.pConfig->mRequestBindMobile.nationCode.value(str1.GetBuffer(0));
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(),mPack.pack.size());
	CString strFormat;
	strFormat.Format("查询号码:%s%s","+86",str1);
	//OutputEdit(strFormat);
}


BOOL CMBLBindSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始查询
	//CPackReq mPack;
	//mPack.SetPacketType(account_RequestQueryQQBindingStat);
	//pConfig->isNeedCode=false;
	//mPack.pConfig=pConfig;
	//mPack.PackData();
	//SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
