#pragma once
#include "afxwin.h"


// CIdentifyCodeDlg 对话框

class CIdentifyCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIdentifyCodeDlg)

public:
	CIdentifyCodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIdentifyCodeDlg();

// 对话框数据
	enum { IDD = IDD_IDENTIFYCODEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mCode;
	CImage mImage;
	virtual BOOL OnInitDialog();
	CStatic mCodePic;
	CString *pRetCString;
public:
	void SetImgStream(unsigned char *dst,unsigned int size);
	void SetRetCode(CString *str){pRetCString=str;};
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedCode();
};
