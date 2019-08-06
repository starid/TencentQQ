
// QQDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"
#include "afxdialogex.h"
#include"Dlg_Login.h"
#include"UserMsg.h"
#include"..\Packet\CommReq.h"
#include"..\Packet\CommonUnPack.h"
#include"..\Packet\CommHead.h"
#include "../UtilLib/err_code.h"
#include"UserMsg.h"
#include"MyLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// COffineQQDlg 对话框


COffineQQDlg::COffineQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COffineQQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COffineQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, mStatic1);
	DDX_Control(pDX, IDC_LIST1, mList1);
	DDX_Control(pDX, IDC_STATIC2, mStatic2);
	DDX_Control(pDX, IDC_STATIC3, mStatic3);
	DDX_Control(pDX, IDC_LIST2, mList2);
	DDX_Control(pDX, IDC_LIST3, mList3);
	DDX_Control(pDX, IDC_STATIC4, mStatic4);
	DDX_Control(pDX, IDC_STATIC5, mStatic5);
	DDX_Control(pDX, IDC_TREE1, mTreeCtrl);
}

BEGIN_MESSAGE_MAP(COffineQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &COffineQQDlg::OnLogin)
	ON_MESSAGE(WM_RECEIVED_MSG, &COffineQQDlg::OnReceivedMsg)
	ON_MESSAGE(WM_TRANSMIT_MSG, &COffineQQDlg::OnTransmitMsg)
	ON_COMMAND(ID_32772, &COffineQQDlg::OnOffineLine)
	ON_COMMAND(ID_32779, &COffineQQDlg::On32779)
	ON_COMMAND(ID_32780, &COffineQQDlg::On32780)
	ON_COMMAND(ID_32781, &COffineQQDlg::On32781)
	ON_COMMAND(ID_32782, &COffineQQDlg::On32782)
	ON_COMMAND(ID_32784, &COffineQQDlg::On32784)
	ON_COMMAND(ID_32783, &COffineQQDlg::On32783)
	ON_MESSAGE(WM_LOGINSUCCESSED, &COffineQQDlg::OnLoginsuccessed)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_TRAY_NOTIFICATION, &COffineQQDlg::OnTrayNotification)
	ON_COMMAND(ID_32793, &COffineQQDlg::On32793)
END_MESSAGE_MAP()


// COffineQQDlg 消息处理程序

BOOL COffineQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

		//设置本地中文字符集
	_wsetlocale(LC_ALL,L"chs");

	//安装异常链
	if(!this->SetDumpFunc())
	{
		//设置对话框日志
		return FALSE;
	}
	StatusLogText("COffineQQDlg 异常链设置完毕。。。");
	if(!this->SetDlgUI())
	{
		//设置对话框日志
		return FALSE;
	}
	StatusLogText("COffineQQDlg 对话栏设置完毕。。。");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COffineQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COffineQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COffineQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//用于设置Dump线程
BOOL COffineQQDlg::SetDumpFunc(void)
{
	SetUnhandledExceptionFilter(GPTUnhandledExceptionFilter);

	g_DumpThread=CreateThread(NULL,0,ThreadProc,NULL,CREATE_SUSPENDED,NULL);
	if(g_DumpThread==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

//用于设置主对话框的UI
BOOL COffineQQDlg::SetDlgUI(void)
{
	//初始化MainFrame UI界面
	int x=0,y=0,height=0,width=0;
	height=m_Ini.GetIntKey("configure.ini","MainFrame","height");
	width=m_Ini.GetIntKey("configure.ini","MainFrame","width");
	RECT rect={0};
	this->GetWindowRect(&rect);
	this->MoveWindow(rect.left,rect.top,width,height,TRUE);

	//好友列表
	x=m_Ini.GetIntKey("configure.ini","mStatic4","x");
	y=m_Ini.GetIntKey("configure.ini","mStatic4","y");
	height=m_Ini.GetIntKey("configure.ini","mStatic4","height");
	width=m_Ini.GetIntKey("configure.ini","mStatic4","width");
	mStatic4.MoveWindow(x,y,width,height);

	x=m_Ini.GetIntKey("configure.ini","mTreeCtrl","x");
	y=m_Ini.GetIntKey("configure.ini","mTreeCtrl","y");
	height=m_Ini.GetIntKey("configure.ini","mTreeCtrl","height");
	width=m_Ini.GetIntKey("configure.ini","mTreeCtrl","width");
	mTreeCtrl.MoveWindow(x,y,width,height);

	mTreeCtrl.SetItemHeight(26);
	mTreeCtrl.SetImageList();
	mTreeCtrl.SetStyle(TVS_HASBUTTONS,0);	
	
	//消息列表
	x=m_Ini.GetIntKey("configure.ini","mStatic1","x");
	y=m_Ini.GetIntKey("configure.ini","mStatic1","y");
	height=m_Ini.GetIntKey("configure.ini","mStatic1","height");
	width=m_Ini.GetIntKey("configure.ini","mStatic1","width");
	mStatic1.MoveWindow(x,y,width,height);

	x=m_Ini.GetIntKey("configure.ini","mList1","x");
	y=m_Ini.GetIntKey("configure.ini","mList1","y");
	height=m_Ini.GetIntKey("configure.ini","mList1","height");
	width=m_Ini.GetIntKey("configure.ini","mList1","width");
	mList1.MoveWindow(x,y,width,height);

	//个人消息
	x=m_Ini.GetIntKey("configure.ini","mStatic2","x");
	y=m_Ini.GetIntKey("configure.ini","mStatic2","y");
	height=m_Ini.GetIntKey("configure.ini","mStatic2","height");
	width=m_Ini.GetIntKey("configure.ini","mStatic2","width");
	mStatic2.MoveWindow(x,y,width,height);

	x=m_Ini.GetIntKey("configure.ini","mList2","x");
	y=m_Ini.GetIntKey("configure.ini","mList2","y");
	height=m_Ini.GetIntKey("configure.ini","mList2","height");
	width=m_Ini.GetIntKey("configure.ini","mList2","width");
	mList2.MoveWindow(x,y,width,height);
	this->mList2.Clear();
	char  _column2[][20]={"序号","发送方","发送时间","消息内容"};
	this->mList2.SetHeaders(_column2,sizeof(_column2)/sizeof(*_column2));

	//群组消息
	x=m_Ini.GetIntKey("configure.ini","mStatic3","x");
	y=m_Ini.GetIntKey("configure.ini","mStatic3","y");
	height=m_Ini.GetIntKey("configure.ini","mStatic3","height");
	width=m_Ini.GetIntKey("configure.ini","mStatic3","width");
	mStatic3.MoveWindow(x,y,width,height);

	x=m_Ini.GetIntKey("configure.ini","mList3","x");
	y=m_Ini.GetIntKey("configure.ini","mList3","y");
	height=m_Ini.GetIntKey("configure.ini","mList3","height");
	width=m_Ini.GetIntKey("configure.ini","mList3","width");
	mList3.MoveWindow(x,y,width,height);
	this->mList3.Clear();
	char  _column3[][20]={"序号","群号","发送方","发送时间","消息内容"};
	this->mList3.SetHeaders(_column3,sizeof(_column3)/sizeof(*_column3));

	//发送消息
	x=m_Ini.GetIntKey("configure.ini","mStatic5","x");
	y=m_Ini.GetIntKey("configure.ini","mStatic5","y");
	height=m_Ini.GetIntKey("configure.ini","mStatic5","height");
	width=m_Ini.GetIntKey("configure.ini","mStatic5","width");
	mStatic5.MoveWindow(x,y,width,height);

	//创建状态栏
	this->m_Status.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,CRect(0,0,0,0), this, IDC_STATUSBARCTRL);
	this->m_Status.SetUI();

	//设置默认状态
	this->m_Send=0;
	this->m_Recv=0;
	this->m_Abandon=0;
	this->m_Status.Updata(m_Send,m_Recv,m_Abandon);
	this->m_Status.SetProcessBar(0);
	
	this->SetUinStatus(BeOffine); //设置状态
	return TRUE;
}

void COffineQQDlg::OnLogin()
{
	if(Config.mStatus!=BeOffine)
	{
		AfxMessageBox("请先注销已登录账号");
		return;
	}
	Dlg_Login login_dlg;
	login_dlg.pConfig=&Config;
	login_dlg.DoModal();
}

afx_msg LRESULT COffineQQDlg::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 1:
		{
			//接受数据
			break;
		}break;
	case 2:
		{
			//客户端断开
			unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
			mList1.AddString("客户端断开成功");
			delete piID;
			return 0;
		}break;
	default:
		{
			Error_Check(ERR_COMMON);
			return 0;
		}break;
	}

	//接收数据指针+1
	AddRecv();

	ByteBuffer *pRecv=(ByteBuffer*)(lParam);
	CCommonUnPack *packet= new CCommonUnPack();
	packet->Wrapping(*pRecv);
	packet->pConfig=&Config;
	delete pRecv;
	pRecv=NULL;
	unsigned int ret=packet->UnPackData();

	//记录收到数据包(丢弃前)
	RecvPacketRecords(packet);

	//查看数据包是否需要丢弃
	if(ret==ERR_PACKET_ABANDON)
	{
		//丢弃数据指针+1
		AddAbandon();
		return 0;
	}
	Error_Check(ret);

	//处理数据
	switch(packet->GetPackType())
	{
		case TypeFFFF:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("收到0xFFFF未知消息");
			}break;
		case Type001D:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("001D消息");
			}break;
		case Type01BB:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("01BB消息");
			}break;
		case Type0134:
			{
				//分析数据
				Error_Check(packet->Analysis(&mFolderList));
				mList1.AddString("0134消息");

				//发送0002数据包
				if(mFolderList.mList2.size()!=0)
				{
					for(int i=0;i<mFolderList.mList2.size();i++)
					{
						CCommReq *p=new CCommReq();
						p->pAttach=&mFolderList.mList2[i].dwClusterId;
						p->SetPacketType(Type0002);
						p->pConfig=&Config;
						p->PackData();
						DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
						delete p;p=NULL;
					}
				}

			}break;
		case Type0002:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("0002消息");
			}break;
		case Type00EC:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("00EC消息");

				//发送了2分00B9未知消息包（无返回异常）
				//p=new CCommReq();
				//p->SetPacketType(CODE_00B901);
				//p->pConfig=&Config;
				//p->PackData();
				//DlgSend(ClientID,p->pack);
				//delete p;p=NULL;

				//p=new CCommReq();
				//p->SetPacketType(CODE_00B902);
				//p->pConfig=&Config;
				//p->PackData();
				//DlgSend(ClientID,p->pack);
				//delete p;p=NULL;

				//00D1消息（无返回异常）
				CCommReq *p=new CCommReq();
				p->SetPacketType(Type00D1);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				/****001D系列消息********/
				//p=new CCommReq();
				//p->SetPacketType(CODE_001D03);
				//p->pConfig=&Config;
				//p->PackData();
				//DlgSend(ClientID,p->pack);
				//delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type001D);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type001D);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type001D);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//p=new CCommReq();
				//p->SetPacketType(CODE_001D07);
				//p->pConfig=&Config;
				//p->PackData();
				//DlgSend(ClientID,p->pack);
				//delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type001D);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type001D);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;
				/****001D系列消息********/

				//0001好友分组消息
				p=new CCommReq();
				p->SetPacketType(Type0001);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//0195消息
				p=new CCommReq();
				p->SetPacketType(Type0195);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

			}break;
		case Type00B9:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("00B9消息");
			}break;
		case Type00D1:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("00D1消息");
			}break;
		case Type0001:
			{
				//分析数据
				Error_Check(packet->Analysis(&mFolderList));
				mList1.AddString("0001好友分组消息");

				//0027消息
				CCommReq *p=new CCommReq();
				p->SetPacketType(Type0027);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//019b消息
				p=new CCommReq();
				p->SetPacketType(Type019B);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//01A5消息
				p=new CCommReq();
				p->SetPacketType(Type01A5);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//0362未知消息
				//0371未知消息

				//01AE消息
				p=new CCommReq();
				p->SetPacketType(Type01AE);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//07FF消息
				p=new CCommReq();
				p->SetPacketType(Type07FF);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//00D4消息
				p=new CCommReq();
				p->SetPacketType(Type00D4);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type00D4);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				p=new CCommReq();
				p->SetPacketType(Type00D4);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//005C取个资料
				p=new CCommReq();
				p->SetPacketType(Type005C);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//003E获取备注
				p=new CCommReq();
				p->SetPacketType(Type003E);
				p->pConfig=&Config;
				p->PackData();
				DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
				delete p;p=NULL;

				//GetCookie操作
				//开启心跳线程
				if(!this->SetHeartPacket())
				{
					Error_Check(ERR_COMMON);
				}

			}break;
		case Type0058:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("0058心跳返回");
			}break;
		case Type00CE:
			{
				//分析数据
				TextMsg msg;
				Error_Check(packet->Analysis(&msg));
				InsertRecvMsg(msg);
				mList1.AddString("00CE好友消息");
			}break;
		case Type0017:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("0017群消息");
			}break;
		case Type0027:
			{
				//分析好友列表
				Error_Check(packet->Analysis(&mFolderList));
				//可用于数据加载
				InitFriendsList(mFolderList);
				mList1.AddString("0027消息");
			}break;
		case Type0195:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("0195消息");
			}break;
		case Type019B:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("019B消息");
			}break;
		case Type01A5:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("01A5消息");
			}break;
		case Type01AE:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("01AE消息");
			}break;
		case Type07FF:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("07FF消息");
			}break;
		case Type00D4:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("00D4消息");
			}break;
		case Type005C:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("005C消息");
			}break;
		case Type003E:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("003E消息");
			}break;
		case Type000D:
			{
				//分析数据
				Error_Check(packet->Analysis());
				mList1.AddString("000D消息");
			}break;
		case Type00CD:
			{
				Error_Check(packet->Analysis());
				mList1.AddString("00CD消息");
			}break;
		default:
			{
				Error_Check(packet->Analysis());
			}break;
	}
	delete packet;packet=NULL;
	return 0;
}

afx_msg LRESULT COffineQQDlg::OnTransmitMsg(WPARAM wParam, LPARAM lParam)
{
	ActionCommand *pAction=(ActionCommand*)wParam;
	switch(pAction->sCmd)
	{
	case ACTION_SEND_MSG:
		{
			CString str;
			str.Format("发送消息->%d",pAction->sSubCmd);
			mList1.AddString(str);

			//CCommReq* p=new CCommReq();
			//p->SetPacketType(CODE_00CD01);
			//p->pConfig=&Config;
			//p->PackData();
			//DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
			//delete p;p=NULL;
		}break;
	case ACTION_QUERY_USERDATA:
		{
			CString str;
			str.Format("查询资料->%d",pAction->sSubCmd);
			mList1.AddString(str);
		}break;
	default:
		{
			//AppendLog("COffineQQDlg::OnTransmitMsg error");
		}break;
	}

	return 0;
}

void COffineQQDlg::InitFriendsList(FolderList& mFriends)
{
	//先初始化好友分组
	for (int i =0; i < mFriends.mList1.size(); i ++) 
	{
		CString strSet;
		strSet.Format("%s",mFriends.mList1[i].strClusterName.c_str());
		HTREEITEM Root=mTreeCtrl.InsertItem(strSet.GetBuffer(0),-1,-1);
		//加载好友
		for(int j=0;j<mFriends.mList1[i].Friends.size();j++)
		{
			CString strFriend;
			strFriend.Format("%d",mFriends.mList1[i].Friends[j].dwUin);
			mTreeCtrl.InsertItem(strFriend,Root,TVI_LAST);
		}

	//		//父节点
	//HTREEITEM Root=mTreeCtrl.InsertItem(TEXT("gym游戏中心"),0,0,TVI_ROOT,TVI_LAST);

	////mTreeCtrl.SetItemImage(Root,0,1);

	////斗地主游戏
	//HTREEITEM GameItem1=mTreeCtrl.InsertItem(TEXT("斗地主"),7,6,Root,TVI_LAST);
	//
	//	HTREEITEM Room_Item1_1=mTreeCtrl.InsertItem(TEXT("网通站点"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_1=mTreeCtrl.InsertItem(TEXT("初级房"),9,6,Room_Item1_1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_2=mTreeCtrl.InsertItem(TEXT("高级房"),9,6,Room_Item1_1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_3=mTreeCtrl.InsertItem(TEXT("VIP房"),9,6,Room_Item1_1,TVI_LAST);
	//
	//
	//	HTREEITEM Room_Item1_2=mTreeCtrl.InsertItem(TEXT("电信站点"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_2_1=mTreeCtrl.InsertItem(TEXT("没有合适的房间"),9,6,Room_Item1_2,TVI_LAST);

	//	HTREEITEM Room_Item1_3=mTreeCtrl.InsertItem(TEXT("其他站点"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_3_1=mTreeCtrl.InsertItem(TEXT("没有合适的房间"),9,6,Room_Item1_3,TVI_LAST);


	////虎虎生威游戏
	//HTREEITEM GameItem2=mTreeCtrl.InsertItem(TEXT("虎虎生威"),7,6,Root,TVI_LAST);

	//	HTREEITEM Room_Item2_1=mTreeCtrl.InsertItem(TEXT("没有合适的站点"),8,6,GameItem2,TVI_LAST);

	////百人牌九游戏
	//HTREEITEM GameItem3=mTreeCtrl.InsertItem(TEXT("百人牌九"),7,6,Root,TVI_LAST);

	//	HTREEITEM Room_Item3_1=mTreeCtrl.InsertItem(TEXT("没有合适的站点"),8,6,GameItem3,TVI_LAST);

	////展开所有节点
	////ExpandAllItem(&m_TreeCtrl,m_TreeCtrl.GetRootItem());

	}
}

void COffineQQDlg::RecvPacketRecords(CCommonUnPack* p)
{
	CString type;
	switch(p->GetPackType())
	{
		case TypeFFFF:
			{
				type.Format("0x%04x 服务器发送未知消息",static_cast<CCommHeadResp*>(p->pHead)->Hda.code);
			}break;
		default:
			{
				type.Format("0x%04x消息",p->GetPackType());
			}break;
	}
	DataLogBytes(type,(unsigned char*)p->pack.contents(),p->pack.size());
}

void COffineQQDlg::InsertRecvMsg(TextMsg msg)
{
	int num=mList2.GetItemCount();
	CString size;
	size.Format("%d",num+1);
	mList2.InsertItem(num,size);
	CString Uin;
	Uin.Format("%d",msg.Uin);
	mList2.SetItemText(num,1,Uin);
	CString time;
	time.Format("%d",msg.Time);
	mList2.SetItemText(num,2,time);
	CString strContent;
	strContent.Format("%s",msg.MsgContent.c_str());
	mList2.SetItemText(num,3,strContent);
}

void COffineQQDlg::InitSendPacket()
{
	//设置当前消息通知窗口
	ChangeNotifyWnd(m_hWnd,WM_RECEIVED_MSG);
	//开始发送其他一系列请求消息
	unsigned short mType=0;
	CCommReq *p=new CCommReq();
	mType=1;
	p->pAttach=&mType;
	p->SetPacketType(Type001D);		//0x12
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;
	
	p=new CCommReq();
	mType=2;
	p->pAttach=&mType;
	p->SetPacketType(Type001D);		//0x26
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;

	//发送01BB消息
	p=new CCommReq();
	mType=1;
	p->pAttach=&mType;
	p->SetPacketType(Type01BB);
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;

	p=new CCommReq();
	mType=2;
	p->pAttach=&mType;
	p->SetPacketType(Type01BB);
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;
	
	//发送0134消息
	p=new CCommReq();
	p->SetPacketType(Type0134);
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;

	/******此数据包导致下线**********/
	p=new CCommReq();
	p->SetPacketType(Type00EC);
	p->pConfig=&Config;
	p->PackData();
	DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
	delete p;p=NULL;
	/******此数据包导致下线**********/

	//以上消息已测试正常


	//019B消息（01 00 00 00 00 01 00 00）
	//01A5消息(01 00 00 00 18 01 00 00 )
	//0362未知消息
	//0126(最近联系列表)
	//003C数据包可能为返回了某人信息之类数据
	//0067可能为返回个人签名
	//005C可能为返回了某人开通的业务，如VIP等等
	//0002可能返回了群相关信息(可能依赖本身)
	//0027好友列表
}

BOOL COffineQQDlg::SetHeartPacket()
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	gHeartThread[0]=CreateWaitableTimer(NULL, FALSE, NULL);
	SetWaitableTimer(gHeartThread[0], &li, 60*1000, NULL, NULL, FALSE);

	gHeartThread[1]=CreateEvent(NULL, TRUE, FALSE, NULL); //初始化为FALSE的人工重置事件，用于结束线程

	//如何终止此线程的问题
	HANDLE Thread=CreateThread(NULL,0,HeartThreadProc,this,0,NULL);
	if(Thread==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

DWORD _stdcall COffineQQDlg::HeartThreadProc( LPVOID lpParam )
{
	COffineQQDlg *pThis=static_cast<COffineQQDlg*>(lpParam);

	CCommReq p;
	p.SetPacketType(Type0058);
	p.pConfig=&pThis->Config;
	p.PackData();
	bool isLiving=true;
	while(isLiving)
	{
		DWORD dw=WaitForMultipleObjects(2,pThis->gHeartThread,FALSE,INFINITE);
		switch(dw)
		{
			case WAIT_FAILED:
				break;
			case WAIT_TIMEOUT:
				break;
			case WAIT_OBJECT_0 + 0:
				{
					pThis->DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
					pThis->mList1.AddString("发送心跳数据包");
				}break;
			case WAIT_OBJECT_0 + 1:
				{
					isLiving=false;
				}
				break;
		}
	}
	CloseHandle(pThis->gHeartThread[0]);
	CloseHandle(pThis->gHeartThread[1]);
	return 1;
}

/*设置状态*/
void COffineQQDlg::SetUinStatus(UinStatus status)
{
	CMenu *pMenu=GetMenu();
	pMenu->GetSubMenu(0)->CheckMenuItem(3,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(4,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_UNCHECKED);
	switch(status)
	{
	case BeOnLine:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(3,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeCallMe:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(4,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeLeave:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeBusy:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeNoTrouble:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeInvisible:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
		}break;
	default:
		{
		}break;
	}
	Config.mStatus=status;	
	UpdateUinStatus();
}

void COffineQQDlg::UpdateUinStatus()
{
	CString strStatus;
	switch(Config.mStatus)
	{
	case BeOffine:
		{
			strStatus=BeOffineTip;
		}break;
	case BeOnLine:
		{
			strStatus=BeOnLineTip;
		}break;
	case BeCallMe:
		{
			strStatus=BeCallMeTip;
		}break;
	case BeBusy:
		{
			strStatus=BeBusyTip;
		}break;
	case BeLeave:
		{
			strStatus=BeLeaveTip;
		}break;
	case BeInvisible:
		{
			strStatus=BeInvisibleTip;
		}break;
	case BeNoTrouble:
		{
			strStatus=BeNoTroubleTip;
		}break;
	case BeOther:
		{
			strStatus=BeOtherTip;
		}break;
	default:
		{
			return;
		}break;
	}
	this->m_Status.UpdataUinStatus(Config.qq_id,CString(&Config.UserName[1]),strStatus);
}

/*我在线上*/
void COffineQQDlg::On32779()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	SetUinStatus(BeOnLine);
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*Q我吧*/
void COffineQQDlg::On32780()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	// TODO: 在此添加命令处理程序代码
	SetUinStatus(BeCallMe);
	
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*离开*/
void COffineQQDlg::On32781()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	// TODO: 在此添加命令处理程序代码
	SetUinStatus(BeLeave);
	
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*忙碌*/
void COffineQQDlg::On32782()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	// TODO: 在此添加命令处理程序代码
	SetUinStatus(BeBusy);
	
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*请勿打扰*/
void COffineQQDlg::On32783()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	// TODO: 在此添加命令处理程序代码
	SetUinStatus(BeNoTrouble);
	
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*隐身*/
void COffineQQDlg::On32784()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	// TODO: 在此添加命令处理程序代码
	SetUinStatus(BeInvisible);
	
	CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
}

/*注销*/
void COffineQQDlg::OnOffineLine()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	
	// TODO: 在此添加命令处理程序代码
	CCommReq p;
	p.SetPacketType(Type0062);
	p.pConfig=&Config;
	p.PackData();

	//连发四次
	for(int i=0;i<4;i++)
	{
		DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
	}
	//激活心跳线程结束事件对象
	SetEvent(gHeartThread[1]);
	//销毁IOCP
	EndTheSystem();
	Config.restart();
	this->m_Send=0;
	this->m_Recv=0;
	this->m_Abandon=0;
	this->m_Status.Updata(m_Send,m_Recv,m_Abandon);
	this->m_Status.SetProcessBar(0);
	SetUinStatus(BeOffine);
	//清除数据列表
	this->mList1.ResetContent();   //清除消息列表
	this->mTreeCtrl.DeleteAllItems();  //清除好友列表
	mFolderList.Clear();
	mList2.Clear();//清除好友消息列表
}

/*登陆成功*/
afx_msg LRESULT COffineQQDlg::OnLoginsuccessed(WPARAM wParam, LPARAM lParam)
{
	//初次登陆成功
	AfxMessageBox("登陆成功");
	//显示用户账号信息以及状态
	SetUinStatus(BeCallMe);
	InitSendPacket();
	return 0;
}

//关闭程序
void COffineQQDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(Config.mStatus!=BeOffine)
	{
		//在线
		if(IDYES==MessageBox("确定关闭程序？点否转入托盘运行","关闭",MB_YESNO))
		{
			OnOffineLine();
			CDialogEx::OnClose();
		}else
		{
			TrayMessage(m_hWnd,NIM_ADD,NULL,"托盘程序");
			TrayMessage(m_hWnd,NIM_MODIFY,m_hIcon,"托盘程序");
			ShowWindow(SW_HIDE);
		}
	}else
	{
		CDialogEx::OnClose();
	}
}

//托盘设置
BOOL COffineQQDlg::TrayMessage(HWND hWnd,DWORD dwMessage,HICON hIcon,PSTR pszTip)
{
	BOOL bReturn;
	NOTIFYICONDATA NofityData;
	NofityData.cbSize=sizeof(NOTIFYICONDATA);
	NofityData.hWnd=hWnd;
	NofityData.uID=IDR_MAINFRAME;
	NofityData.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	NofityData.uCallbackMessage=WM_TRAY_NOTIFICATION;
	NofityData.hIcon=hIcon;
	lstrcpyn(NofityData.szTip,pszTip,sizeof(NofityData.szTip));
	bReturn=Shell_NotifyIcon(dwMessage,&NofityData);
	return bReturn;
}

//托盘消息处理
afx_msg LRESULT COffineQQDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case WM_RBUTTONUP:
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//得到鼠标位置 
			CMenu temp,*ptr=NULL;
            temp.LoadMenu(IDR_MENU3);
            ptr = temp.GetSubMenu(0);
			if(ptr==NULL) return 0;
			SetForegroundWindow();
			UINT uFlags = TPM_RIGHTBUTTON;
            if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
            {
                uFlags |= TPM_RIGHTALIGN;
            }
            else
            {
                uFlags |= TPM_LEFTALIGN;
            }
			ptr->TrackPopupMenuEx( uFlags, lpoint->x, lpoint->y, this, NULL);
			temp.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			ShowWindow(SW_SHOW);
			TrayMessage(m_hWnd,NIM_DELETE,NULL,"");
		}break;
	}

	return 0;
}

//托盘关闭程序
void COffineQQDlg::On32793()
{
	// TODO: 在此添加命令处理程序代码
	if(Config.mStatus!=BeOffine)
	{
		//在线
		if(IDYES==MessageBox("确定注销账号并关闭程序？","关闭",MB_YESNO))
		{
			OnOffineLine();
			Sleep(3000);
			//停留几秒发送消息结束
			DestroyWindow();
		}
	}
}
