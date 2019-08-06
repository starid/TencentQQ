#pragma once
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"
#include "mylistctrl.h"

// CCNearByDlg 对话框

class CCNearByDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCNearByDlg)

public:
	CCNearByDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCNearByDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CConfigData *pConfig;
	MyListCtrl mList1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
