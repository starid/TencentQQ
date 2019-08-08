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
#include"..\Packet\LoginReq.h"
#include"..\Packet\CommonUnPack.h"
#include"..\Packet\CommHead.h"
#include"UserMsg.h"
#include"protocol_type.h"
#include"MyLog.h"


#define TEST_ECDH


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
	ON_BN_CLICKED(IDC_BUTTON2, &Dlg_Login::OnBnClickedButton2)
END_MESSAGE_MAP()


// Dlg_Login 消息处理程序


void Dlg_Login::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);

	char _account[SIZE_ACCOUNT]={0};
	memcpy(_account,m_Account.GetBuffer(),m_Account.GetLength());
	pConfig->qq_id=strtoul(_account,0,10);
	memcpy(pConfig->qq_pwd,m_Password.GetBuffer(),m_Password.GetLength());

	CLoginReq _login_packet;   //数据包类型
	_login_packet.SetPacketType(Type0825);
	_login_packet.pConfig=pConfig;
	_login_packet.PackData();            //封包

	m_List.AddString("发送ping数据包...");
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());
}


BOOL Dlg_Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	this->m_Account="2799044801";
	this->m_Password="test123";
	this->UpdateData(FALSE);

	Error_Check(StartTheSystem(m_ConfigDlg.m_iPortNr,
		m_ConfigDlg.m_iMaxNumberOfConnections,
		m_ConfigDlg.m_iNrOfIOWorkers,
		m_ConfigDlg.m_iNrOfLogicalWorkers,
		m_ConfigDlg.m_iMaxNrOfFreeBuff,
		m_ConfigDlg.m_iMaxNrOfFreeContext,
		m_ConfigDlg.m_iSendInOrder,
		m_ConfigDlg.m_bReadInOrder,
		m_ConfigDlg.m_iNrPendlingReads));//启动iocp系统
		
	//取的congfig
	m_Ini.GetStrKey("NetConfig.ini","udpserver","url",pConfig->host);
	pConfig->port=m_Ini.GetIntKey("NetConfig.ini","udpserver","port");
	pConfig->net_type=NET_UDP;                   //设置网络类型
	pConfig->isTurnIp=FALSE;

	CEcdh _ecdh;
	_ecdh.ecdh_init();
	if(!_ecdh.ecdh_generate_publicKey())
	{
		Error_Check(ERR_ECDH_ERROR);
	}
	
#ifdef TEST_ECDH
	memcpy(pConfig->stKey,ST_KEY,sizeof(ST_KEY));
	memcpy(pConfig->ecdh_key,ECDH_KEY,sizeof(ECDH_KEY));
#else
	memcpy(pConfig->stKey,_ecdh.stKey,sizeof(_ecdh.stKey));
	memcpy(pConfig->ecdh_key,_ecdh.key,sizeof(_ecdh.key));
#endif

	CTeaCrypt::initkey(pConfig->key0825,TEA_KEY_LEN);
	CTeaCrypt::initkey(pConfig->key0836,TEA_KEY_LEN);
	CTeaCrypt::initkey(pConfig->key0104,TEA_KEY_LEN);
	CTeaCrypt::initkey(pConfig->key00BA,TEA_KEY_LEN);

	StatusLogText("Dlg_Login ecdh初始化完毕");
	DataLogBytes("ecdh stKey",(unsigned char*)pConfig->stKey,sizeof(pConfig->stKey));
	DataLogBytes("ecdh ecdh_key",(unsigned char*)pConfig->ecdh_key,sizeof(pConfig->ecdh_key));
	DataLogBytes("key0825",(unsigned char*)pConfig->key0825,sizeof(pConfig->key0825));
	DataLogBytes("key0836",(unsigned char*)pConfig->key0836,sizeof(pConfig->key0836));
	DataLogBytes("key0104",(unsigned char*)pConfig->key0104,sizeof(pConfig->key0104));
	DataLogBytes("key00BA",(unsigned char*)pConfig->key00BA,sizeof(pConfig->key00BA));

	hostent *pipda=gethostbyname(pConfig->host);
	if(pipda==NULL)
	{
		Error_Check(ERR_GETHOSTBYNAME);
	}
	char *ip=inet_ntoa(*((in_addr*)(pipda->h_addr_list[0])));
	pConfig->ServerIp=inet_addr((const char *)ip);
	CString strLog;
	strLog.Format("准备连入 %s:%d",ip,pConfig->port);
	m_List.AddString((LPCTSTR)strLog);

	Error_Check(OnConnectA(ip,pConfig->port));         //连入

	StatusLogText(strLog);

	m_List.AddString("网络初始化成功!");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


afx_msg LRESULT Dlg_Login::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			//新客户端连接
			unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
			m_List.AddString("新客户端链接成功");
			pConfig->m_iCurrentClientID=*piID;
			delete piID;
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
			return 0;
		}break;
	default:
		{
			Error_Check(ERR_COMMON);
			return 0;
		}break;
	}
	ByteBuffer *pRecv=(ByteBuffer*)(lParam);
	CCommonUnPack *packet= new CCommonUnPack();
	packet->Wrapping(*pRecv);
	packet->pConfig=pConfig;
	delete pRecv;
	pRecv=NULL;
	packet->UnPackData();

	//记录收到数据包
	RecvPacketRecords(packet);

	//分析数据
	if(packet->Analysis()!=RESULT_SUCCESS)
	{
		m_List.AddString("数据包错误...");
		return 0;
	}
	packet->pack.rpos(0);
	switch(packet->GetPackType())
	{
	case Type0825:
		{
			if(packet->pConfig->isTurnIp)
			{
				//需要转向,需要关闭IOCP，并且重新启动IOCP
				m_List.AddString("ping数据包发送失败...");
				OnDisconnect(pConfig->m_iCurrentClientID);
				packet->pConfig->restart();
				OnConnectA(packet->pConfig->m_iCurrentClientID,"",packet->pConfig->port,1);
				AfxMessageBox("网络暂时不通，请稍后再试");
				EndDialog(0);
				return 0;
			}
			m_List.AddString("开始发送登陆验证数据包...");
			CLoginReq _login_packet;
			_login_packet.SetPacketType(Type0836);
			pConfig->isNeedCode=false;
			_login_packet.pConfig=pConfig;
			_login_packet.PackData();
			//发送0836数据包
			SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());
		}break;
	case Type0836:
		{
			if(pConfig->LoginVerifyCode!=RESULT_NORMAL)
			{
				switch(pConfig->LoginVerifyCode)
				{
					case NEED_REINPUTPWD:
						{
							m_List.AddString("抱歉，请重新输入密码...");
							delete packet;packet=NULL;
							AfxMessageBox("抱歉，请重新输入密码!");
							//EndDialog(0);
							return 0;
						}break;
					case PWD_ERROR:
						{
							m_List.AddString("密码错误...");
							delete packet;packet=NULL;
							AfxMessageBox("密码错误");
							EndDialog(0);
							return 0;
						}break;
					case ID_ALREADY_RECOVERY:
						{
							m_List.AddString("号码已被回收...");
							delete packet;packet=NULL;
							AfxMessageBox("号码已被回收");
							EndDialog(0);
							return 0;
						}break;
					case NEED_CHECKCODE:
						{
							m_List.AddString("需要验证码...");

							//发送0104数据包
							CLoginReq *pPacket=new CLoginReq();
							pPacket->SetPacketType(Type0104);
							pPacket->pConfig=pConfig;
							pPacket->PackData();
							SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)pPacket->pack.contents(), pPacket->pack.size());
							delete pPacket;pPacket=NULL;
							
							//发送00ba数据包,请求另一部分验证码
							pPacket=new CLoginReq();
							pPacket->SetPacketType(Type00BA);
							pConfig->isNeedCode=false;		//第一次不需要验证码
							pPacket->pConfig=pConfig;
							pPacket->PackData();
							SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)pPacket->pack.contents(), pPacket->pack.size());

							delete pPacket;pPacket=NULL;
						}break;
					case NEED_DEVICE_UNLOCKED:
						{
							m_List.AddString("需要验证设备锁，暂不支持此登陆方式...");
							delete packet;packet=NULL;
							AfxMessageBox("需要验证设备锁");
							EndDialog(0);
							return 0;
						}break;
					case NEED_LOGINVERIFYAGAIN:
						{
							m_List.AddString("重新发送登陆验证数据包...");

							CLoginReq _login_packet;
							_login_packet.SetPacketType(Type0836);
							pConfig->isNeedCode=false;
							_login_packet.pConfig=pConfig;
							_login_packet.PackData();
							//发送0836数据包
							SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());

						}break;
					default:
						{
							m_List.AddString("登陆异常...");
							delete packet;packet=NULL;
							AfxMessageBox("登陆异常");
							EndDialog(0);
							return 0;
						}break;
				}
			}else
			{
				//将用户名UTF8转换成多字节数据
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


				CLoginReq _login_packet;
				_login_packet.SetPacketType(Type0828);
				pConfig->isNeedCode=false;
				_login_packet.pConfig=pConfig;
				_login_packet.PackData();
				//发送0836数据包
				SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());
			}
		}break;
	case Type0104:
		{
			m_List.AddString("验证码tip...");
		}break;
	case Type00BA:
		{
			//判断第一次还是第二次
			char i=packet->pack.read<char>();
			if(i==0x13)
			{	
				m_List.AddString("验证码1305...");
				
				//弹出验证码对话框
				CIdentifyCodeDlg mIndetifyCodeDlg(this);
				pConfig->mCodePngData.rpos(0);
				mIndetifyCodeDlg.SetImgStream((unsigned char*)pConfig->mCodePngData.contents(),pConfig->mCodePngData.size());
				CString strRet=NULL;
				mIndetifyCodeDlg.SetRetCode(&strRet);
				INT_PTR ret=mIndetifyCodeDlg.DoModal();
				if(ret!=IDOK)
					return 0;
				memcpy(pConfig->IndetifyCode,strRet.GetBuffer(0),SIZE_CODE);

				//发送验证码
				CLoginReq _login_packet;
				_login_packet.SetPacketType(Type00BA);
				pConfig->isNeedCode=true;
				_login_packet.pConfig=pConfig;
				_login_packet.PackData();
				SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)_login_packet.pack.contents(), _login_packet.pack.size());
			}else if(i==0x14)
			{
				//第二次带验证码
				packet->pack.mpos(0x2);
				if(packet->pack.read<char>()==0x0)
				{
					//验证码验证通过，发送0836
					m_List.AddString("验证码通过...");

					CLoginReq _login_packet;
					_login_packet.SetPacketType(Type0836);
					pConfig->isNeedCode=true;
					_login_packet.pConfig=pConfig;
					_login_packet.PackData();
					//发送0836数据包
					SendPacket(pConfig->m_iCurrentClientID,(unsigned char *)_login_packet.pack.contents(), _login_packet.pack.size());
				}else
				{
					m_List.AddString("验证码未通过，重新验证...");
					//验证码未通过，重新发送验证码窗口

					//发送00ba数据包,请求另一部分验证码
					CLoginReq Packet;
					Packet.SetPacketType(Type00BA);
					pConfig->isNeedCode=false;
					Packet.pConfig=pConfig;
					Packet.PackData();
					SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)Packet.pack.contents(), Packet.pack.size());
				}
			}
		}break;
	case Type0828:
		{
			if(pConfig->LoginVerifyCode!=RESULT_NORMAL)
			{
				AfxMessageBox("登陆失败");
			}else
			{
				m_List.AddString("上线成功,完成登陆...");
				//开始其他操作
				//尝试关闭iocp
				//EndTheSystem();
				//首先通知主窗口登陆完成消息
				SendMessage(WM_CLOSE);
				::SendMessage(::AfxGetMainWnd()->m_hWnd,WM_LOGINSUCCESSED,NULL,NULL);
			}
			
		}break;
	}

	delete packet;packet=NULL;
	return 0;
}

void Dlg_Login::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ConfigDlg.DoModal();
}

void Dlg_Login::RecvPacketRecords(CCommonUnPack* p)
{
	CString type;
	type.Format("0x%04x消息",p->GetPackType());
	DataLogBytes(type,(unsigned char*)p->pack.contents(),p->pack.size());
}