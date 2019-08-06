// MobileNo.cpp : 实现文件
//

#include "stdafx.h"
#include "MobileNo.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../NetLib/NetLib.h"
#include"UserMsg.h"
#include"../CCodecWarpper/ResponeUploadAddressBookV2.h"
#include"../CCodecWarpper/RespondQueryQQBindingStat.h"
#include"../CCodecWarpper/ResponeVerifySmscode.h"
#include"../CCodecWarpper/ResponeQueryQQMobileContactsV3.h"
#include"../CCodecWarpper/AddressBookItem.h"
#include"../CCodecWarpper/MobileContactsFriendInfo.h"
#include"../CCodecWarpper/MobileContactsNotFriendInfo.h"
#include"../UtilLib/HelpFunc.h"
#include"../CCodecWarpper/ResponeBindMobile.h"
#include"../CCodecWarpper/SummaryCardRespSearch.h"
#include"../CCodecWarpper/addcontacts/search.pb.h"
#include"../CCodecWarpper/profilecard/comm.pb.h"
#include"../CCodecWarpper/ClassFactory.h"
#include<cstdlib>
#include"../UtilLib/deelx.h"


// CMobileNo 对话框

IMPLEMENT_DYNAMIC(CMobileNo, CDialogEx)

CMobileNo::CMobileNo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMobileNo::IDD, pParent)
{

}

CMobileNo::~CMobileNo()
{
}

void CMobileNo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, ctrPhoneNos);
	DDX_Control(pDX, IDC_EDIT8, mOutPutEdit);
	DDX_Control(pDX, IDC_EDIT1, mStartEdt);
	DDX_Control(pDX, IDC_EDIT2, mEndEdt);
}


BEGIN_MESSAGE_MAP(CMobileNo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMobileNo::OnBnClickedButton1)
	ON_MESSAGE(WM_RECEIVED_MSG, &CMobileNo::OnReceivedMsg)
	ON_BN_CLICKED(IDC_RADIO1, &CMobileNo::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMobileNo::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CMobileNo::OnBnClickedRadio4)
	ON_COMMAND(ID_32795, &CMobileNo::On32795)
	ON_COMMAND(ID_32796, &CMobileNo::On32796)
	ON_BN_CLICKED(IDC_BUTTON5, &CMobileNo::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMobileNo::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMobileNo 消息处理程序

BOOL CMobileNo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//精确查询
	m_Radio=1;		//默认为精确查询
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//选上
	mStartEdt.SetLimitText(11);
	mEndEdt.SetLimitText(11);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CMobileNo::OnBnClickedButton1()
{
	//首先取输入内容
	mBindMobile.dwCurSel=0;
	mBindMobile.mBindInfos.clear();
	std::string strmobileNo;
	std::string strnationCode;
	switch(m_Radio)
	{
	case 1:
		{
			//从文件读取
		}break;
	case 2:
		{
			//文本框输入查询
			int nLineCount=ctrPhoneNos.GetLineCount();
			CString strText, strLine;
			for (int i=0; i < nLineCount; i++)
			{
				// length of line i:
				int len = ctrPhoneNos.LineLength(ctrPhoneNos.LineIndex(i));
				if(len==0) break;
				ctrPhoneNos.GetLine(i, strText.GetBuffer(len), len);
				strText.ReleaseBuffer(len);
				BindInfo m;
				m.strMobileNo="+86";
				m.strNationCode=strText;
				mBindMobile.mBindInfos.push_back(m);
			}
			if(mBindMobile.mBindInfos.size()>0)
			{
				mBindMobile.dwCurSel=0;
				strmobileNo=mBindMobile.mBindInfos[mBindMobile.dwCurSel].strMobileNo;
				strnationCode=mBindMobile.mBindInfos[mBindMobile.dwCurSel].strNationCode;
				CPackReq mPack;
				mPack.SetPacketType(account_RequestBindMobile);
				mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::CMobileNo_RequestBindMobile));
				//取第一个数据
				pConfig->mRequestBindMobile.mobileNo.value(strmobileNo);
				pConfig->mRequestBindMobile.nationCode.value(strnationCode);
				mPack.pConfig=pConfig;
				mPack.PackData();
				SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
			}else
			{
				AfxMessageBox("文本框输入为空");
				return;
			}
		}break;
	case 4:
		{
			//输入范围查询
			CString strStart;
			mStartEdt.GetWindowTextA(strStart);
			CString strEnd;
			mEndEdt.GetWindowTextA(strEnd);

			CRegexpT <char> regexp("^((13[0-9])|(15[^4,\\D])|(18[0,5-9]))\\d{8}$");  
			MatchResult result = regexp.MatchExact(strStart);
			if(result.IsMatched())
			{
				unsigned __int64 value1=_atoi64(strStart);
				unsigned __int64 value2=_atoi64(strEnd);
				for(;value1<=value2;value1++)
				{
					char buf[12]={0};
					_i64toa_s(value1,buf,sizeof(buf),10);
					BindInfo m;
					m.strMobileNo="+86";
					m.strNationCode=buf;
					mBindMobile.mBindInfos.push_back(m);
				}
				if(mBindMobile.mBindInfos.size()>0)
				{
					mBindMobile.dwCurSel=0;
					strmobileNo=mBindMobile.mBindInfos[mBindMobile.dwCurSel].strMobileNo;
					strnationCode=mBindMobile.mBindInfos[mBindMobile.dwCurSel].strNationCode;
					CPackReq mPack;
					mPack.SetPacketType(account_RequestBindMobile);
					mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::CMobileNo_RequestBindMobile));
					//取第一个数据
					pConfig->mRequestBindMobile.mobileNo.value(strmobileNo);
					pConfig->mRequestBindMobile.nationCode.value(strnationCode);
					mPack.pConfig=pConfig;
					mPack.PackData();
					SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
				}else
				{
					AfxMessageBox("文本框输入为空");
					return;
				}
			}else
			{
				AfxMessageBox("输入有误");
				return;
			}
		}break;
	}
}

afx_msg LRESULT CMobileNo::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			CRespondQueryQQBindingStat *pRespondQueryQQBindingStat=
				static_cast<CRespondQueryQQBindingStat*>((void*)lParam);
			if(pRespondQueryQQBindingStat->type.value()==1&&pRespondQueryQQBindingStat->mobileNo.value().size()!=0&&
				pRespondQueryQQBindingStat->nationCode.value().size()!=0)
			{
				CString strFormat;
				strFormat.Format("本号码已绑定%s%s %s",pRespondQueryQQBindingStat->nationCode.value().c_str(),
					pRespondQueryQQBindingStat->mobileNo.value().c_str(),pRespondQueryQQBindingStat->MobileUniqueNo.value().c_str());
				pConfig->mRequestCancelBindMobile.mobileNo.value(pRespondQueryQQBindingStat->mobileNo.value());
				pConfig->mRequestCancelBindMobile.nationCode.value(pRespondQueryQQBindingStat->nationCode.value());
				AfxMessageBox(strFormat);
			}else
			{
				CString strFormat;
				strFormat.Format("本号码未绑定任何手机号码");
				AfxMessageBox(strFormat);
			}
			delete pRespondQueryQQBindingStat;
			pRespondQueryQQBindingStat=NULL;
		}break;
	case 1:
		{
			CResponeQueryQQMobileContactsV3 *pResponeQueryQQMobileContactsV3=
				static_cast<CResponeQueryQQMobileContactsV3*>((void*)lParam);
			if(pResponeQueryQQMobileContactsV3->BindFriendContacts._value.size()==0&&
				pResponeQueryQQMobileContactsV3->BindNotFriendContacts._value.size()==0)
			{
				CString strFormat;
				strFormat.Format("查询结果为空");
				OutputEdit(strFormat);
			}else
			{
				if(pResponeQueryQQMobileContactsV3->BindFriendContacts._value.size()!=0)
				{
					std::list<JCE::IObject*>::iterator iter;
					for(iter=pResponeQueryQQMobileContactsV3->BindFriendContacts._value.begin();
						iter!=pResponeQueryQQMobileContactsV3->BindFriendContacts._value.end();iter++)
					{
						CString strFormat;
						strFormat.Format("%s",static_cast<CMobileContactsFriendInfo*>(*iter)->QQ.value().c_str());
						OutputEdit(strFormat);
					}
				}
				if(pResponeQueryQQMobileContactsV3->BindNotFriendContacts._value.size()!=0)
				{
					std::list<JCE::IObject*>::iterator iter;
					for(iter=pResponeQueryQQMobileContactsV3->BindNotFriendContacts._value.begin();
						iter!=pResponeQueryQQMobileContactsV3->BindNotFriendContacts._value.end();iter++)
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
						OutputEdit(strFormat);
					}
				}
			}
			delete pResponeQueryQQMobileContactsV3;
			pResponeQueryQQMobileContactsV3=NULL;
		}break;
	case 2:
		{
			CResponeBindMobile *pResponeBindMobile=static_cast<CResponeBindMobile*>((void*)lParam);
			if(pResponeBindMobile->alreadyBindedUin.value().size()==0)
			{
				if(pResponeBindMobile->sessionSid.value().size()==0)
				{
					//登陆QQ号码已绑定手机号码，请先解除绑定或者切换登陆未绑定QQ号码
					CString strFormat;
					strFormat.Format("%s%s",mBindMobile.mBindInfos[mBindMobile.dwCurSel].strMobileNo.c_str(),
					mBindMobile.mBindInfos[mBindMobile.dwCurSel].strNationCode.c_str());
					OutputEdit(strFormat);
				}else
				{
					//登陆QQ号码未绑定，且目标手机号码未绑定任何QQ号码
					CString strFormat;
					strFormat.Format("%s%s",mBindMobile.mBindInfos[mBindMobile.dwCurSel].strMobileNo.c_str(),
					mBindMobile.mBindInfos[mBindMobile.dwCurSel].strNationCode.c_str());
					strFormat.AppendFormat("|null");
					OutputEdit(strFormat);
				}
			}else
			{
				//登陆QQ号码未绑定，且目标手机号码已绑定QQ号码
				CString strFormat;
				strFormat.Format("%s%s",mBindMobile.mBindInfos[mBindMobile.dwCurSel].strMobileNo.c_str(),
					mBindMobile.mBindInfos[mBindMobile.dwCurSel].strNationCode.c_str());
				strFormat.AppendFormat("|%s",pResponeBindMobile->alreadyBindedUin.value().c_str());
				OutputEdit(strFormat);
			}
			delete pResponeBindMobile;
			pResponeBindMobile=NULL;
		}break;
	default:
		{
			return 0;
		}break;
	}
	return 0;
}

void CMobileNo::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=1;
}


void CMobileNo::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=2;
}


void CMobileNo::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Radio=4;
}

//绑定状态查询
void CMobileNo::On32795()
{
	CPackReq mPack;
	mPack.SetPacketType(account_RequestQueryQQBindingStat);
	mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::CMobileNo_RequestQueryQQBindingStat));
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
}

//绑定号码查询
void CMobileNo::On32796()
{
	CPackReq mPack;
	mPack.SetPacketType(account_RequestQueryQQMobileContactsV3);
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
}

//清空列表
void CMobileNo::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	mOutPutEdit.SetWindowTextA("");
}

//导出列表内容
void CMobileNo::OnBnClickedButton6()
{
	//保存文件对话框
	CString strFile;        //文件完整路径
	CFileDialog fileDlg(FALSE);              //构造一个文件另存为对话框
	fileDlg.m_ofn.lpstrTitle="另存为";
	fileDlg.m_ofn.lpstrFilter="Text Files(*.txt)\0*.txt\0ALL Files(*.*)\0*.*\0\0";
	fileDlg.m_ofn.lpstrDefExt="txt";    //定义缺省文件扩展名
	if(IDOK==fileDlg.DoModal())              //打开文件另存为对话框
	{
		strFile = fileDlg.GetPathName();//返回选定文件的完整路径
		
		CString strComment;
		mOutPutEdit.GetWindowTextA(strComment);
		CFile mFile(strFile,CFile::modeCreate|CFile::modeReadWrite);
		mFile.SeekToBegin();
		mFile.Write(strComment.GetBuffer(0),strComment.GetLength());
		mFile.Close();
		AfxMessageBox("保存完毕");
	}
	//判断是否有重名文件
	//if (PathFileExists(strFile))
	//{
	//	//存在
	//	if (IDYES ==AfxMessageBox("文件已经存在是否要替换它?",MB_YESNO|MB_ICONQUESTION))
	//	{
	//		//存在相同文件名，替换
	//	}else
	//	{
	//		//存在相同文件名，不替换
	//	}
	//}else
	//{
	//	//不存在
	//}
}

void CMobileNo::OutputEdit(CString str)
{
	str.Append("\r\n");
	int nCount    = 0;
    int nLastLine = 0;
    nCount         =  mOutPutEdit.GetLineCount();              //获取行数，包括回车行
    nLastLine      =  mOutPutEdit.LineIndex( nCount - 1 );   //获取字符数，许可多行
    mOutPutEdit.SetSel( nLastLine + 1, nLastLine + 2 );      //设定光标选中的区域
    mOutPutEdit.ReplaceSel(str);                 //
}