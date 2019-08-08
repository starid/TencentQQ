#pragma once
#include "afxwin.h"
#include"IOCPSettingsDlg.h"
#include"GlobeVar.h"
#include"..\Packet\ConfigData.h"
#include"..\Packet\CommonUnPack.h"


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
	afx_msg void OnBnClickedButton2();
public:
	CSimpleIni m_Ini;
	// 用户账户
	CString m_Account;
	// 用户密码
	CString m_Password;
	// 用于显示登陆过程信息
	CListBox m_List;
	IOCPSettingsDlg m_ConfigDlg;
	CConfigData *pConfig;
private:
	//收到数据包的记录
	void RecvPacketRecords(CCommonUnPack*);
protected:
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);
};
