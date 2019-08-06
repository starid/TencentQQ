#pragma once
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"


// CSearchDlg 对话框

class CSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchDlg)

public:
	CSearchDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
		afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CConfigData *pConfig;
public:
	afx_msg void OnBnClickedButton1();
};
