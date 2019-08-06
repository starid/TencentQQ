// IdentifyCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ.h"
#include "IdentifyCodeDlg.h"
#include "afxdialogex.h"
#include "UserMsg.h"


// CIdentifyCodeDlg 对话框

IMPLEMENT_DYNAMIC(CIdentifyCodeDlg, CDialogEx)

CIdentifyCodeDlg::CIdentifyCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIdentifyCodeDlg::IDD, pParent)
{

}

CIdentifyCodeDlg::~CIdentifyCodeDlg()
{
}

void CIdentifyCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mCode);
	DDX_Control(pDX, IDC_CODE, mCodePic);
}


BEGIN_MESSAGE_MAP(CIdentifyCodeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CIdentifyCodeDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_CODE, &CIdentifyCodeDlg::OnStnClickedCode)
END_MESSAGE_MAP()


// CIdentifyCodeDlg 消息处理程序


BOOL CIdentifyCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	mCode.SetLimitText(4);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CIdentifyCodeDlg::SetImgStream(unsigned char *dst,unsigned int size)
{
	COleStreamFile osf;
    osf.CreateMemoryStream(NULL);
    osf.Write(dst, size);
    osf.SeekToBegin();
	mImage.Load(osf.GetStream());

	//mImage.Load("D:\\程序\\TencentQQ\\Debug\\png.png");
}

void CIdentifyCodeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	CRect rect;
	mCodePic.GetClientRect(&rect);
	mImage.Draw(mCodePic.GetDC()->GetSafeHdc(), rect.left,rect.top);

}


void CIdentifyCodeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	mCode.GetWindowTextA(*pRetCString);
	if(pRetCString->Trim().GetLength()==0)
	{
		AfxMessageBox("请输入验证码");
	}else
		CDialogEx::OnOK();
}

//更新验证码
void CIdentifyCodeDlg::OnStnClickedCode()
{
	//点击验证码图片，更新验证码图片，暂不支持
}
