
// QQDlg.h : 头文件
//

#pragma once
#include <locale.h>
#include"GlobeVar.h"
#include"..\Packet\ConfigData.h"
#include"MFCStatus.h"
#include "afxwin.h"
#include"MyListCtrl.h"
#include"OwnerDrawTreeCtrl.h"
#include"..\Packet\FolderList.h"
#include"..\Packet\ClassModel.h"
#include"..\Packet\CommonUnPack.h"


// COffineQQDlg 对话框
class COffineQQDlg : public CDialogEx
{
// 构造
public:
	COffineQQDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	Ini m_Ini;
	CConfigData Config;
	unsigned int m_Send;
	unsigned int m_Recv;
	unsigned int m_Abandon;
	HANDLE gHeartThread[2];
	FolderList mFolderList;	//好友列表
private:
	BOOL SetDumpFunc(void);
	BOOL SetDlgUI(void);
	static DWORD _stdcall HeartThreadProc( LPVOID lpParam );

	void InitSendPacket();
	void DlgSend(unsigned int ClientID,ByteBuffer &b){SendPacket(ClientID,&b);AddSend();};
	//状态的改变
	void AddSend(){m_Send++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void AddRecv(){m_Recv++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void AddAbandon(){m_Abandon++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void SetUinStatus(UinStatus status);
	inline void UpdateUinStatus();
	//收到数据包的记录
	void RecvPacketRecords(CCommonUnPack*);
	//心跳数据包的设置
	BOOL SetHeartPacket();
	//初始化好友列表
	void InitFriendsList(FolderList&);
	//加入一条个人消息
	void InsertRecvMsg(TextMsg);
public:
	afx_msg void OnLogin();
	afx_msg void OnOffineLine();
	afx_msg void On32779();
	afx_msg void On32780();
	afx_msg void On32781();
	afx_msg void On32782();
	afx_msg void On32784();
	afx_msg void On32783();
	afx_msg void OnClose();
	afx_msg void On32793();
public:
	// 显示消息列表
	CStatic mStatic1;
	// 消息列表
	CListBox mList1;
	CStatic mStatic2;
	CStatic mStatic3;
	MyListCtrl mList2;     //个人消息列表
	MyListCtrl mList3;    //群组消息列表
	// 显示好友分组
	CStatic mStatic4;
	CStatic mStatic5;
	// 标记了好友列表
	COwnerDrawTreeCtrl mTreeCtrl;
	//状态栏
	MFCStatus m_Status;
protected:
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam); //处理服务器传来的数据包消息
	afx_msg LRESULT OnTransmitMsg(WPARAM wParam, LPARAM lParam); //处理其他动作消息
	afx_msg LRESULT OnLoginsuccessed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
public:
	BOOL TrayMessage(HWND,DWORD,HICON,PSTR);
};
