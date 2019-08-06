#pragma once
#include "afxwin.h"
#include"GlobeVar.h"
#include"../CCodecWarpper/ConfigData.h"
#include"../CCodecWarpper/CommonUnPack.h"
#include"../UtilLib/SimpleIni.h"
#include"SeqSerial.h"


// Dlg_Login 对话框

class Dlg_Login : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_Login)

public:
	Dlg_Login(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_Login();

// 对话框数据
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
public:
	//ini配置类
	CSimpleIniA mSimpleIniA;
	// 用户账户
	CString m_Account;
	// 用户密码
	CString m_Password;
	// 用于显示登陆过程信息
	CListBox m_List;
	CConfigData *pConfig;
	CCriticalSection m_ReceiveMsgLock;
	//数据包序号
	CSeqSerial mSeqSerial;
private://iocp param
	int		m_iMaxNumberOfConnections;
	int		m_iMaxNrOfFreeBuff;
	int		m_iMaxNrOfFreeContext;
	int		m_iNrOfIOWorkers;
	int		m_iNrOfLogicalWorkers;
	int		m_iPortNr;
	BOOL	m_bReadInOrder;
	BOOL	m_iSendInOrder;
	int		m_iNrOfPendlingReads;
public:
	void SetIocpParam(int,int,int,int,int,int,BOOL,BOOL,int);
private:
	//收到数据包的记录
	void RecvPacketRecords(CCommonUnPack*);
protected:
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClose();
};
