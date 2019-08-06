#pragma once
#include "afxwin.h"
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"
#include"../NetLib/NetLib.h"
#include"UserMsg.h"


// CMBLBindSet 对话框

class CMBLBindSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMBLBindSet)

public:
	CMBLBindSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMBLBindSet();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	// 手机号码
	CEdit mEditPhoneNo;
	// 验证码
	CEdit mEditCheckNo;
	CConfigData *pConfig;
	std::string strsessionSid;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
