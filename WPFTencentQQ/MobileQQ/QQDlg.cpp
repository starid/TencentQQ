
// QQDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"
#include "afxdialogex.h"
#include"Dlg_Login.h"
#include"UserMsg.h"
#include "../UtilLib/err_code.h"
#include"UserMsg.h"
#include"MyLog.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/ResponeBindMobile.h"
#include"../CCodecWarpper/ResponeUploadAddressBookV2.h"
#include"../CCodecWarpper/RespondQueryQQBindingStat.h"
#include"../CCodecWarpper/ResponeVerifySmscode.h"
#include"../CCodecWarpper/ResponeQueryQQMobileContactsV3.h"
#include"../CCodecWarpper/ResponeUploadAddressBook.h"
#include"../CCodecWarpper/ResponeUpdateAddressBook.h"
#include"../CCodecWarpper/SummaryCardRespSearch.h"
#include"../CCodecWarpper/RespGetEncounterV2.h"
#include"SeqSerial.h"

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
	ON_COMMAND(ID_32784, &COffineQQDlg::On32784)
	ON_MESSAGE(WM_LOGINSUCCESSED, &COffineQQDlg::OnLoginsuccessed)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_TRAY_NOTIFICATION, &COffineQQDlg::OnTrayNotification)
	ON_COMMAND(ID_32793, &COffineQQDlg::On32793)
	ON_COMMAND(ID_32794, &COffineQQDlg::On32794)
	ON_COMMAND(ID_32799, &COffineQQDlg::OnNetSet)
	ON_COMMAND(ID_32800, &COffineQQDlg::OnMachineSet)
	ON_COMMAND(ID_32801, &COffineQQDlg::On32801)
	ON_COMMAND(ID_32802, &COffineQQDlg::On32802)
	ON_COMMAND(ID_32803, &COffineQQDlg::On32803)
	ON_COMMAND(ID_32804, &COffineQQDlg::On32804)
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
	pMobileQuery=NULL;
	pMBLBindSet=NULL;
	pNickNameQuery=NULL;
	pSearchDlg=NULL;
	//设置本地中文字符集
	_wsetlocale(LC_ALL,L"chs");

	//初始化ini类参数
	mSimpleIniA.SetUnicode(false);
	mSimpleIniA.SetMultiKey(true);
	mSimpleIniA.SetMultiLine(true);
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

	GlobeVar::pMainWnd = &this->m_hWnd;
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
	SI_Error rc = mSimpleIniA.LoadFile("configure.ini");
    if (rc < 0) return false;

	//初始化MainFrame UI界面
	int x=0,y=0,height=0,width=0;
	height=mSimpleIniA.GetLongValue("MainFrame","height");
	width=mSimpleIniA.GetLongValue("MainFrame","width");
	RECT rect={0};
	this->GetWindowRect(&rect);
	this->MoveWindow(rect.left,rect.top,width,height,TRUE);

	//好友列表
	x=mSimpleIniA.GetLongValue("mStatic4","x");
	y=mSimpleIniA.GetLongValue("mStatic4","y");
	height=mSimpleIniA.GetLongValue("mStatic4","height");
	width=mSimpleIniA.GetLongValue("mStatic4","width");
	mStatic4.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mTreeCtrl","x");
	y=mSimpleIniA.GetLongValue("mTreeCtrl","y");
	height=mSimpleIniA.GetLongValue("mTreeCtrl","height");
	width=mSimpleIniA.GetLongValue("mTreeCtrl","width");
	mTreeCtrl.MoveWindow(x,y,width,height);

	mTreeCtrl.SetItemHeight(26);
	mTreeCtrl.SetImageList();
	mTreeCtrl.SetStyle(TVS_HASBUTTONS,0);	
	
	//消息列表
	x=mSimpleIniA.GetLongValue("mStatic1","x");
	y=mSimpleIniA.GetLongValue("mStatic1","y");
	height=mSimpleIniA.GetLongValue("mStatic1","height");
	width=mSimpleIniA.GetLongValue("mStatic1","width");
	mStatic1.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList1","x");
	y=mSimpleIniA.GetLongValue("mList1","y");
	height=mSimpleIniA.GetLongValue("mList1","height");
	width=mSimpleIniA.GetLongValue("mList1","width");
	mList1.MoveWindow(x,y,width,height);

	//个人消息
	x=mSimpleIniA.GetLongValue("mStatic2","x");
	y=mSimpleIniA.GetLongValue("mStatic2","y");
	height=mSimpleIniA.GetLongValue("mStatic2","height");
	width=mSimpleIniA.GetLongValue("mStatic2","width");
	mStatic2.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList2","x");
	y=mSimpleIniA.GetLongValue("mList2","y");
	height=mSimpleIniA.GetLongValue("mList2","height");
	width=mSimpleIniA.GetLongValue("mList2","width");
	mList2.MoveWindow(x,y,width,height);
	this->mList2.Clear();
	char  _column2[][20]={"序号","发送方","发送时间","消息内容"};
	this->mList2.SetHeaders(_column2,sizeof(_column2)/sizeof(*_column2));

	//群组消息
	x=mSimpleIniA.GetLongValue("mStatic3","x");
	y=mSimpleIniA.GetLongValue("mStatic3","y");
	height=mSimpleIniA.GetLongValue("mStatic3","height");
	width=mSimpleIniA.GetLongValue("mStatic3","width");
	mStatic3.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList3","x");
	y=mSimpleIniA.GetLongValue("mList3","y");
	height=mSimpleIniA.GetLongValue("mList3","height");
	width=mSimpleIniA.GetLongValue("mList3","width");
	mList3.MoveWindow(x,y,width,height);
	this->mList3.Clear();
	char  _column3[][20]={"序号","群号","发送方","发送时间","消息内容"};
	this->mList3.SetHeaders(_column3,sizeof(_column3)/sizeof(*_column3));

	//发送消息
	x=mSimpleIniA.GetLongValue("mStatic5","x");
	y=mSimpleIniA.GetLongValue("mStatic5","y");
	height=mSimpleIniA.GetLongValue("mStatic5","height");
	width=mSimpleIniA.GetLongValue("mStatic5","width");
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
	
	//this->SetUinStatus(BeOffine); //设置状态
	return TRUE;
}

//登陆按钮
void COffineQQDlg::OnLogin()
{
	if(Config.mStatus!=BeOffine)
	{
		AfxMessageBox("请先注销已登录账号");
		return;
	}
	Dlg_Login login_dlg;
	login_dlg.SetIocpParam(m_ConfigDlg.m_iPortNr,
		m_ConfigDlg.m_iMaxNumberOfConnections,
		m_ConfigDlg.m_iNrOfIOWorkers,
		m_ConfigDlg.m_iNrOfLogicalWorkers,
		m_ConfigDlg.m_iMaxNrOfFreeBuff,
		m_ConfigDlg.m_iMaxNrOfFreeContext,
		m_ConfigDlg.m_iSendInOrder,
		m_ConfigDlg.m_bReadInOrder,
		m_ConfigDlg.m_iNrPendlingReads);
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
			GlobeVar::Error_Check(ERR_COMMON);
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

	//分析数据
	if(packet->Analysis()!=RESULT_SUCCESS)
	{
		mList1.AddString("数据包错误...");
		return 0;
	}

	//记录收到数据包
	RecvPacketRecords(packet);

	//查看数据包是否需要丢弃
	if(ret==ERR_PACKET_ABANDON)
	{
		//丢弃数据指针+1
		AddAbandon();
		return 0;
	}
	GlobeVar::Error_Check(ret);

	switch(packet->GetPackType())
	{
	case GrayUinPro_Check:
		{
			packet->DispatchCmd();
			//CPackReq *p=new CPackReq();
			//Config.strServiceCmd=STR_friendlist_GetTroopListReqV2;
			//p->SetPacketType(friendlist_GetTroopListReqV2);
			//Config.isNeedCode=false;
			//Config.isSidUsed=true;
			//p->pConfig=&Config;
			//p->PackData();
			//SendPacket(Config.m_iCurrentClientID,&(p->pack));
			//delete p;
		}break;
	case friendlist_GetTroopListReqV2:
		{
			packet->DispatchCmd();
			//CPackReq *p=new CPackReq();
			//pConfig->strServiceCmd=STR_friendlist_GetTroopListReqV2;
			//p->SetPacketType(friendlist_GetTroopListReqV2);
			//pConfig->isNeedCode=false;
			//p->pConfig=pConfig;
			//p->PackData();
			//SendPacket(pConfig->m_iCurrentClientID,&(p->pack));
			//delete p;
		}break;
	case OidbSvc_0x7a2_0:
		{
			packet->DispatchCmd();
			//发送StatSvc_register
			CPackReq *p=new CPackReq();
			p->SetPacketType(StatSvc_register);
			Config.mRegisterCmd=CmdOnLine;
			p->pConfig=&Config;
			p->PackData();
			SendPacket(Config.m_iCurrentClientID,(unsigned char*)p->pack.contents(), p->pack.size());
			delete p;
		}break;
	case StatSvc_register:
		{
			packet->DispatchCmd();
			if(Config.mRegisterCmd==BeOnLine)
			{
				//上线成功
				if(!this->SetHeartPacket())
				{
					GlobeVar::Error_Check(ERR_COMMON);
				}
			}else if(Config.mRegisterCmd==BeOffine)
			{
				////激活心跳线程结束事件对象
				SetEvent(gHeartThread[1]);
				////销毁IOCP
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
				//mFolderList.Clear();
				mList2.Clear();//清除好友消息列表
			}
		}break;
	case account_RequestBindMobile:
		{
			CResponeBindMobile *pResponeBindMobile=new CResponeBindMobile();
			packet->DispatchCmd(pResponeBindMobile);
			mSeqSerial.SeqRun(packet->GetSeq(),this,pResponeBindMobile);

			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pResponeBindMobile);
			}
		}break;
	case account_RequestCancelBindMobile:
		{
			packet->DispatchCmd();
			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,2,NULL);
			}
		}break;
	case account_RequestUploadAddressBookV2:
		{
			CResponeUploadAddressBookV2 *pResponeUploadAddressBookV2=new CResponeUploadAddressBookV2();
			packet->DispatchCmd(pResponeUploadAddressBookV2);
			if(pNickNameQuery!=NULL&&pNickNameQuery->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pNickNameQuery->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pResponeUploadAddressBookV2);
			}
		}break;
	case account_RequestQueryQQBindingStat:
		{
			CRespondQueryQQBindingStat *pRespondQueryQQBindingStat=new CRespondQueryQQBindingStat();
			packet->DispatchCmd(pRespondQueryQQBindingStat);
			mSeqSerial.SeqRun(packet->GetSeq(),this,pRespondQueryQQBindingStat);
		}break;
	case account_RequestVerifyBindingSmscode:
		{
			CResponeVerifySmscode *pResponeVerifySmscode=new CResponeVerifySmscode();
			packet->DispatchCmd(pResponeVerifySmscode);
			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,1,(LPARAM)pResponeVerifySmscode);
			}
		}break;
	case account_RequestQueryQQMobileContactsV3:
		{
			CResponeQueryQQMobileContactsV3 *pResponeQueryQQMobileContactsV3=new CResponeQueryQQMobileContactsV3();
			packet->DispatchCmd(pResponeQueryQQMobileContactsV3);
			if(pMobileQuery!=NULL&&pMobileQuery->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pMobileQuery->m_hWnd,WM_RECEIVED_MSG,1,(LPARAM)pResponeQueryQQMobileContactsV3);
			}
		}break;
	case account_RequestUploadAddressBook:
		{
			CResponeUploadAddressBook *pResponeUploadAddressBook=new CResponeUploadAddressBook();
			packet->DispatchCmd(pResponeUploadAddressBook);
		}break;
	case account_RequestUpdateAddressBook:
		{
			CResponeUpdateAddressBook *pResponeUpdateAddressBook=new CResponeUpdateAddressBook();
			packet->DispatchCmd(pResponeUpdateAddressBook);
		}break;
	case SummaryCard_ReqSearch:
		{
			CSummaryCardRespSearch *pSummaryCardRespSearch=new CSummaryCardRespSearch();
			packet->DispatchCmd(pSummaryCardRespSearch);
			if(pSearchDlg!=NULL&&pSearchDlg->m_hWnd!=NULL)
			{
				//发送消息
				::PostMessageA(pSearchDlg->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pSummaryCardRespSearch);
			}
		}break;
	case EncounterSvc_ReqGetEncounter:
		{
			CRespGetEncounterV2 *pRespGetEncounterV2=new CRespGetEncounterV2();
			packet->DispatchCmd(pRespGetEncounterV2);
			mSeqSerial.SeqRun(packet->GetSeq(),this,NULL);
		}break;
	case TYPE_HULUE:
		{
		}break;
	}
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

/*
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
*/


void COffineQQDlg::RecvPacketRecords(CCommonUnPack* p)
{
	CString type;
	type.Format("%s",p->pConfig->strServiceCmd.c_str());
	DataLogBytes(type,(unsigned char*)p->pack.contents(),p->pack.size()-p->pack.rpos());
	StatusLogText(p->pConfig->strServiceCmd.c_str());
}

/*
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
*/

void COffineQQDlg::InitSendPacket()
{
	//设置当前消息通知窗口
	ChangeNotifyWnd(m_hWnd,WM_RECEIVED_MSG);
	//发送OidbSvc.0x7a2_0
	CPackReq *p=new CPackReq();
	p->SetPacketType(OidbSvc_0x7a2_0);
	p->SetSeq(mSeqSerial.GetNexSeq());
	p->pConfig=&Config;
	p->PackData();
	SendPacket(Config.m_iCurrentClientID, (unsigned char*)p->pack.contents(), p->pack.size());
	delete p;
	//发送GrayUinPro_Check
	//p=new CPackReq();
	//Config.strServiceCmd=STR_GrayUinPro_Check;
	//p->SetPacketType(GrayUinPro_Check);
	//Config.isNeedCode=false;
	//Config.isSidUsed=false;
	//p->pConfig=&Config;
	//p->PackData();
	//SendPacket(Config.m_iCurrentClientID,&(p->pack));
	//delete p;
	
	//初始查询绑定状态
	CPackReq mPack;
	mPack.SetPacketType(account_RequestQueryQQBindingStat);
	mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::initial_RequestQueryQQBindingStat));
	mPack.pConfig=&Config;
	mPack.PackData();
	SendPacket(Config.m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

BOOL COffineQQDlg::SetHeartPacket()
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	gHeartThread[0]=CreateWaitableTimer(NULL, FALSE, NULL);
	SetWaitableTimer(gHeartThread[0], &li, 300*1000, NULL, NULL, FALSE);		//5分钟

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
	CPackReq p;
	p.SetPacketType(StatSvc_register);
	pThis->Config.mRegisterCmd=CmdHeartBeat;
	p.pConfig=&pThis->Config;
	p.PackData();

	//组装heartBeat包
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

//设置状态
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
	case BeInvisible:
		{
			strStatus=BeInvisibleTip;
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
	/*CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);*/
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
	
	/*CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);*/
}

/*注销*/
void COffineQQDlg::OnOffineLine()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(StatSvc_register);
	mPack.SetSeq(mSeqSerial.GetNexSeq());
	Config.mRegisterCmd=CmdOffLine;
	mPack.pConfig=&Config;
	mPack.PackData();
	SendPacket(Config.m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

/*登陆成功*/
afx_msg LRESULT COffineQQDlg::OnLoginsuccessed(WPARAM wParam, LPARAM lParam)
{
	//初次登陆成功
	AfxMessageBox("登陆成功");
	//显示用户账号信息以及状态
	SetUinStatus(BeOnLine);
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

//绑定设置
void COffineQQDlg::On32794()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	pMBLBindSet=new CMBLBindSet;
	pMBLBindSet->pConfig=&Config;
	pMBLBindSet->DoModal();
	delete pMBLBindSet;
	pMBLBindSet=NULL;
}

//网络设置
void COffineQQDlg::OnNetSet()
{
	// TODO: 在此添加命令处理程序代码
	m_ConfigDlg.DoModal();
}

//硬件配置
void COffineQQDlg::OnMachineSet()
{
	// TODO: 在此添加命令处理程序代码
	m_MachineDlg.pConfig=&Config;
	m_MachineDlg.DoModal();
}

//绑定查询
void COffineQQDlg::On32801()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	pMobileQuery=new CMobileNo();
	pMobileQuery->pConfig=&Config;
	pMobileQuery->DoModal();
	delete pMobileQuery;
	pMobileQuery=NULL;
}

//昵称查询
void COffineQQDlg::On32802()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	pNickNameQuery=new CNickNameQuery();
	pNickNameQuery->pConfig=&Config;
	pNickNameQuery->DoModal();
	delete pNickNameQuery;
	pNickNameQuery=NULL;
}

//搜索号码
void COffineQQDlg::On32803()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("请先登录账号");
		return;
	}
	pSearchDlg=new CSearchDlg();
	pSearchDlg->pConfig=&Config;
	pSearchDlg->DoModal();
	delete pSearchDlg;
	pSearchDlg=NULL;
}

//附近人功能
void COffineQQDlg::On32804()
{
	// TODO: 在此添加命令处理程序代码
	//if(Config.mStatus==BeOffine)
	//{
	//	AfxMessageBox("请先登录账号");
	//	return;
	//}
	pCNearByDlg=new CCNearByDlg();
	pCNearByDlg->pConfig=&Config;
	pCNearByDlg->DoModal();
	delete pCNearByDlg;
	pCNearByDlg=NULL;
}
