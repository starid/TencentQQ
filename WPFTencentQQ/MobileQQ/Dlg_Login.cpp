// Dlg_Login.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "Dlg_Login.h"
#include "IdentifyCodeDlg.h"
#include "afxdialogex.h"
#include "GlobeVar.h"
#include "../UtilLib/err_code.h"
#include"QQDlg.h"
#include"UserMsg.h"
#include"protocol_type.h"
#include"MyLog.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/CommonUnPack.h"
#include"../CipherLib/Md5.h"


//#define TEST_ECDH


// Dlg_Login 对话框

IMPLEMENT_DYNAMIC(Dlg_Login, CDialogEx)

Dlg_Login::Dlg_Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dlg_Login::IDD, pParent)
	, m_Account(_T(""))
	, m_Password(_T(""))
{

}

Dlg_Login::~Dlg_Login()
{
}

void Dlg_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Account);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(Dlg_Login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg_Login::OnBnClickedButton1)
	ON_MESSAGE(WM_RECEIVED_MSG, &Dlg_Login::OnReceivedMsg)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Dlg_Login 消息处理程序


void Dlg_Login::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);

	//连接网络
	hostent *pipda=gethostbyname(pConfig->host);
	if(pipda==NULL)
	{
		GlobeVar::Error_Check(ERR_GETHOSTBYNAME);
	}
	char *ip=inet_ntoa(*((in_addr*)(pipda->h_addr_list[0])));
	pConfig->ServerIp=inet_addr((const char *)ip);
	CString strLog;
	strLog.Format("准备连入 %s:%d",ip,pConfig->port);
	m_List.AddString((LPCTSTR)strLog);

	if(!OnConnectA(GlobeVar::MainCallBackHandle,(unsigned char*)ip,pConfig->port,0))
	{
		GlobeVar::Error_Check(ERR_NORESPOND);
	}
	StatusLogText(strLog);
}


BOOL Dlg_Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->m_Account="2799044801";
	this->m_Password="abcd1234";
	this->UpdateData(FALSE);

	if(!StartTheSystem(m_iPortNr,
		m_iMaxNumberOfConnections,
		m_iNrOfIOWorkers,
		m_iNrOfLogicalWorkers,
		m_iMaxNrOfFreeBuff,
		m_iMaxNrOfFreeContext,
		m_iSendInOrder,
		m_bReadInOrder,
		m_iNrOfPendlingReads))
	{
		GlobeVar::Error_Check(ERR_NORESPOND);
	}
		
	//取的congfig
	SI_Error rc = mSimpleIniA.LoadFile("NetConfig.ini");
    if (rc < 0) 
	{
		StatusLogText("NetConfig.ini 加载失败");
		return false;
	}

	std::string str=mSimpleIniA.GetValue("MobileTcpServer","ip");
	memcpy(pConfig->host,str.c_str(),str.size());
	pConfig->port=mSimpleIniA.GetLongValue("MobileTcpServer","port");
	pConfig->net_type=NET_TCP;                   //设置网络类型

////	CEcdh _ecdh;
////	_ecdh.ecdh_init();
////	if(!_ecdh.ecdh_generate_publicKey())
////	{
////		GlobeVar::Error_Check(ERR_ECDH_ERROR);
////	}
////	
////#ifdef TEST_ECDH
////	memcpy(pConfig->stKey,ST_KEY,sizeof(ST_KEY));
////	memcpy(pConfig->ecdh_key,ECDH_KEY,sizeof(ECDH_KEY));
////#else
////	memcpy(pConfig->stKey,_ecdh.stKey,sizeof(_ecdh.stKey));
////	//手机对计算出来的key求了一次MD5
////	CMd5 mMd5;
////	mMd5.GetMd5(pConfig->ecdh_key,sizeof(pConfig->ecdh_key),_ecdh.key,sizeof(_ecdh.key));
////#endif

	StatusLogText("Dlg_Login ecdh初始化完毕");
	DataLogBytes("ecdh stKey",(unsigned char*)pConfig->stKey,sizeof(pConfig->stKey));
	DataLogBytes("ecdh ecdh_key",(unsigned char*)pConfig->ecdh_key,sizeof(pConfig->ecdh_key));

	m_List.AddString("网络初始化成功!");

	GlobeVar::pDlgLogin = &this->m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Dlg_Login::SetIocpParam(int		_iPortNr,
	int		_iMaxNumberOfConnections,
	int		_iNrOfIOWorkers,
	int		_iNrOfLogicalWorkers,
	int		_iMaxNrOfFreeBuff,
	int		_iMaxNrOfFreeContext,
	BOOL	_iSendInOrder,
	BOOL	_bReadInOrder,
	int		_iNrOfPendlingReads)
{
	m_iMaxNumberOfConnections=_iMaxNumberOfConnections;
	m_iMaxNrOfFreeBuff=_iMaxNrOfFreeBuff;
	m_iMaxNrOfFreeContext=_iMaxNrOfFreeContext;
	m_iNrOfIOWorkers=_iNrOfIOWorkers;
	m_iNrOfLogicalWorkers=_iNrOfLogicalWorkers;
	m_iPortNr=_iPortNr;
	m_bReadInOrder=_bReadInOrder;
	m_iSendInOrder=_iSendInOrder;
	m_iNrOfPendlingReads=_iNrOfPendlingReads;
}


afx_msg LRESULT Dlg_Login::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	m_ReceiveMsgLock.Lock();
	switch(wParam)
	{
	case 0:
		{
			//新客户端连接服务器成功
			unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
			m_List.AddString("新客户端链接成功");
			pConfig->m_iCurrentClientID=*piID;
			delete piID;
			//开始进行验证
			char _account[SIZE_ACCOUNT]={0};
			memcpy(_account,m_Account.GetBuffer(),m_Account.GetLength());
			pConfig->qq_id=strtoul(_account,0,10);
			memcpy(pConfig->qq_pwd,m_Password.GetBuffer(),m_Password.GetLength());

			CPackReq _login_packet;   //数据包类型
			_login_packet.SetPacketType(TYPE_MSF);
			_login_packet.SetSeq(mSeqSerial.GetNexSeq());
			_login_packet.pConfig=pConfig;
			_login_packet.PackData();            //封包
			m_List.AddString("发送ping数据包...");
			SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());

			m_ReceiveMsgLock.Unlock();
			return 0;
		}break;
	case 1:
		{
			//接受数据
			break;
		}break;
	case 2:
		{
			//客户端断开
			unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
			m_List.AddString("客户端断开成功");
			pConfig->m_iCurrentClientID=*piID;
			delete piID;
			m_ReceiveMsgLock.Unlock();
			return 0;
		}break;
	default:
		{
			GlobeVar::Error_Check(ERR_COMMON);
			m_ReceiveMsgLock.Unlock();
			return 0;
		}break;
	}
	ByteBuffer *pRecv=(ByteBuffer*)(lParam);
	CCommonUnPack *packet= new CCommonUnPack();
	packet->Wrapping(*pRecv);
	packet->pConfig=pConfig;
	pRecv=NULL;

	GlobeVar::Error_Check(packet->UnPackData());
	//分析数据
	if(packet->Analysis()!=RESULT_SUCCESS)
	{
		m_List.AddString("数据包错误...");
		m_ReceiveMsgLock.Unlock();
		return 0;
	}
	//记录收到数据包
	RecvPacketRecords(packet);

	unsigned int dwResult=packet->DispatchCmd();
	switch(packet->GetPackType())
	{
	case TYPE_MSF:
		{
			GlobeVar::Error_Check(dwResult);

			CPackReq _login_packet1;
			_login_packet1.SetPacketType(PhSigLcId_Check);
			_login_packet1.SetSeq(mSeqSerial.GetNexSeq());
			_login_packet1.pConfig=pConfig;
			_login_packet1.PackData();
			
			CPackReq _login_packet2;
			_login_packet2.SetPacketType(ConfigService_ClientReq);
			_login_packet2.SetSeq(mSeqSerial.GetNexSeq());
			_login_packet2.pConfig=pConfig;
			_login_packet2.PackData();
			//合并数据包
			_login_packet2.pack.rpos(0);
			_login_packet1.Merge(_login_packet2.pack);
			//发送数据包
			SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet1.pack.contents(), _login_packet1.pack.size());
		}break;
	//case PhSigLcId_Check:
	case ConfigService_ClientReq:
		{
			GlobeVar::Error_Check(dwResult);

			CPackReq *p=new CPackReq();
			p->SetPacketType(HeartBeat_Alive);
			CSeqSerial mSeqSerial;
			p->SetSeq(mSeqSerial.GetNexSeq());
			p->pConfig=pConfig;
			p->PackData();
			SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)p->pack.contents(), p->pack.size());
			delete p;

			p=new CPackReq();
			p->SetPacketType(CliLogSvc_UploadReq);
			p->SetSeq(mSeqSerial.GetNexSeq());
			p->pConfig=pConfig;
			p->PackData();
			SendPacket(pConfig->m_iCurrentClientID, (unsigned char*)p->pack.contents(), p->pack.size());
			delete p;

			p=new CPackReq();
			p->SetPacketType(wtlogin_login);
			p->SetSeq(mSeqSerial.GetNexSeq());
			p->pConfig=pConfig;
			p->PackData();
			SendPacket(pConfig->m_iCurrentClientID, (unsigned char*)p->pack.contents(), p->pack.size());
			delete p;
		}break;
	case wtlogin_login:
		{
			if(dwResult!=RESULT_SUCCESS)
			{
				switch(dwResult)
				{
				case ERR_LOGIN_PASSWORD:
					{
						GlobeVar::Error_Check(dwResult);
						OnDisconnect(pConfig->m_iCurrentClientID);
					}break;
				case ERR_LOGIN_CHECK:
					{
						CIdentifyCodeDlg mIndetifyCodeDlg(this);
						mIndetifyCodeDlg.SetImgStream((unsigned char*)pConfig->mCodePngData.verifyimage.contents(),pConfig->mCodePngData.verifyimage.size());
						CString strRet=NULL;
						mIndetifyCodeDlg.SetRetCode(&strRet);
						INT_PTR ret=mIndetifyCodeDlg.DoModal();
						if(ret!=IDOK)
						{
							OnDisconnect(pConfig->m_iCurrentClientID);
							break;
						}
						pConfig->mCodePngData.sIndetifyCode=strRet;

						CPackReq pack;
						pack.SetPacketType(wtlogin_login);
						pack.SetSeq(mSeqSerial.GetNexSeq());
						pConfig->mCodePngData.isNeedCode=true;
						pack.pConfig=pConfig;
						pack.PackData();
						SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)pack.pack.contents(), pack.pack.size());
					}break;
				default:
					{
						GlobeVar::Error_Check(ERR_LOGIN_FAILED);
						OnDisconnect(pConfig->m_iCurrentClientID);
					}break;
				}
				break;
			}else
			{
				CPackReq *p=new CPackReq();
				p->SetPacketType(wtlogin_trans_emp);
				CSeqSerial mSeqSerial;
				p->SetSeq(mSeqSerial.GetNexSeq());
				p->pConfig=pConfig;
				p->PackData();
				SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)p->pack.contents(), p->pack.size());
				delete p;

				int nLen = MultiByteToWideChar(CP_UTF8, 0, (LPTSTR)(&pConfig->UserName[1]), pConfig->UserName[0], NULL, 0);  
				WCHAR* lpszW = new WCHAR[nLen];  
				int nRtn = MultiByteToWideChar(CP_UTF8, 0, (LPTSTR)(&pConfig->UserName[1]), pConfig->UserName[0], lpszW, nLen);  
				int32 MBLen = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, NULL, 0, NULL, NULL);  
				memset(pConfig->UserName,0,sizeof(pConfig->UserName));
				pConfig->UserName[0]=MBLen;
				nRtn = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, (LPTSTR)(&pConfig->UserName[1]), MBLen, NULL, NULL);
				delete lpszW;
				lpszW=NULL;

				//登陆成功，开始上线操作
				CString strLog;
				strLog.Format("%s登陆成功...",&pConfig->UserName[1]);
				m_List.AddString((LPCTSTR)strLog);
				m_List.AddString("开始执行上线操作");
			}

		}break;
	case wtlogin_trans_emp:
		{
			GlobeVar::Error_Check(dwResult);

			m_List.AddString("上线成功,完成登陆...");
			//首先通知主窗口登陆完成消息
			::SendMessage(::AfxGetMainWnd()->m_hWnd,WM_LOGINSUCCESSED,NULL,NULL);
			SendMessage(WM_CLOSE);
		}break;
	default:
		{
			GlobeVar::Error_Check(dwResult);
		}break;
	}
	delete packet;packet=NULL;
	m_ReceiveMsgLock.Unlock();
	return 0;
}


void Dlg_Login::RecvPacketRecords(CCommonUnPack* p)
{
	CString type;
	type.Format("%s",p->pConfig->strServiceCmd.c_str());
	unsigned int pos=p->pack.rpos();
	p->pack.rpos(0);
	DataLogBytes(type,(unsigned char*)p->pack.contents(),p->pack.size()-p->pack.rpos());
	p->pack.rpos(pos);
	StatusLogText(p->pConfig->strServiceCmd.c_str());
}


void Dlg_Login::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(pConfig->mStatus==BeOffine)
	{
		EndTheSystem();
	}
	CDialogEx::OnClose();
}
