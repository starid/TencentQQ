#pragma once
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"
#include "afxwin.h"


// CNickNameQuery 对话框

class CNickNameQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CNickNameQuery)

public:
	CNickNameQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNickNameQuery();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CConfigData *pConfig;
	afx_msg void OnBnClickedButton1();
	// 文本框号码
	CEdit mEditPhoneNos;
};
