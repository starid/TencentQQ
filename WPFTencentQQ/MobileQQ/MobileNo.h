#pragma once
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"
#include "afxwin.h"
#include"SeqSerial.h"
#include"../CCodecWarpper/RequestBindMobile.h"

// CMobileNo 对话框

class CMobileNo : public CDialogEx
{
	DECLARE_DYNAMIC(CMobileNo)

public:
	CMobileNo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMobileNo();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	CConfigData *pConfig;
	CSeqSerial mSeqSerial;
	int m_Radio;
	BindMobile mBindMobile;
public:
	 afx_msg void OnBnClickedRadio1();
	 afx_msg void OnBnClickedRadio2();
	 afx_msg void OnBnClickedRadio4();
	 virtual BOOL OnInitDialog();
	 afx_msg void On32795();
	 afx_msg void On32796();
	 // 文本框输入号码
	 CEdit ctrPhoneNos;
	 afx_msg void OnBnClickedButton5();
	 afx_msg void OnBnClickedButton6();
	 CEdit mOutPutEdit;
	 void OutputEdit(CString str);
	 CEdit mStartEdt;
	 CEdit mEndEdt;
};
