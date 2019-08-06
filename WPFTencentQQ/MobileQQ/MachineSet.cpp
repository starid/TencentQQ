// MachineSet.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineSet.h"
#include "afxdialogex.h"
#include"protocol_type.h"


// CMachineSet 对话框

IMPLEMENT_DYNAMIC(CMachineSet, CDialogEx)

CMachineSet::CMachineSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMachineSet::IDD, pParent)
	, m_radiobtngroup1(0)
	, m_radiobtngroup2(0)
{

}

CMachineSet::~CMachineSet()
{
}

void CMachineSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mSetsName);
	DDX_Control(pDX, IDC_EDIT1, ctlDeviceName);
	DDX_Control(pDX, IDC_EDIT16, ctlSon);
	DDX_Control(pDX, IDC_EDIT2, ctlOstype);
	DDX_Control(pDX, IDC_EDIT8, ctlOsVersion);
	DDX_Control(pDX, IDC_EDIT9, ctlApn);
	DDX_Control(pDX, IDC_EDIT10, ctlBrand);
	DDX_Control(pDX, IDC_EDIT11, ctlMac);
	DDX_Control(pDX, IDC_EDIT12, ctlAndroidId);
	DDX_Control(pDX, IDC_EDIT13, ctlImei);
	DDX_Control(pDX, IDC_EDIT14, ctlImsi);
	DDX_Control(pDX, IDC_EDIT15, ctlBSSID);
	DDX_Control(pDX, IDC_EDIT17, ctlSSID);
	DDX_Control(pDX, IDC_EDIT3, ctlDeviceId);
	DDX_Radio(pDX, IDC_RADIO1, m_radiobtngroup1);
	DDX_Radio(pDX, IDC_RADIO3, m_radiobtngroup2);
}


BEGIN_MESSAGE_MAP(CMachineSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMachineSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &CMachineSet::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMachineSet::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, &CMachineSet::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMachineSet::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CMachineSet::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CMachineSet::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CMachineSet 消息处理程序

//保存配置
void CMachineSet::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strDeviceName;
	ctlDeviceName.GetWindowTextA(strDeviceName);
	CString strValue;
	ctlSon.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"sim operator name",strValue);
	ctlOstype.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"os type",strValue);
	ctlOsVersion.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"os version",strValue);
	ctlApn.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"apn",strValue);
	ctlBrand.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"brand",strValue);
	ctlMac.GetWindowTextA(strValue);
	if(strValue.GetLength()!=17)
	{
		int kk=strValue.GetLength();
		AfxMessageBox("mac 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"mac",strValue);
	ctlAndroidId.GetWindowTextA(strValue);
	if(strValue.GetLength()!=16)
	{
		AfxMessageBox("android id 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"android id",strValue);
	ctlImei.GetWindowTextA(strValue);
	if(strValue.GetLength()!=15)
	{
		AfxMessageBox("imei 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"imei",strValue);
	ctlImsi.GetWindowTextA(strValue);
	if(strValue.GetLength()!=15)
	{
		AfxMessageBox("imsi 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"imsi",strValue);
	ctlBSSID.GetWindowTextA(strValue);
	if(strValue.GetLength()!=17)
	{
		AfxMessageBox("bssid 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"bssid",strValue);
	ctlSSID.GetWindowTextA(strValue);
	mSimpleIniA.SetValue(strDeviceName,"ssid",strValue);

	ctlDeviceId.GetWindowTextA(strValue);
		if(strValue.GetLength()!=15)
	{
		AfxMessageBox("device id 长度有误");
		return;
	}
	mSimpleIniA.SetValue(strDeviceName,"device id",strValue);

	SI_Error rc=mSimpleIniA.SaveFile("MachineSetting.ini");
	if(rc<0)
	{
		AfxMessageBox("保存失败");
		return;
	}
	AfxMessageBox("保存成功");
}


//加载配置
void CMachineSet::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码

	std::string strDeviceId;
	switch(m_radiobtngroup1)
	{
	case 0:
		{
			CString strValue;
			ctlImei.GetWindowTextA(strValue);
			strDeviceId=strValue;
		}break;
	case 1:
		{
			CString strValue;
			ctlDeviceId.GetWindowTextA(strValue);
			strDeviceId=strValue;
		}break;
	}
	std::string strMac;
	switch(m_radiobtngroup2)
	{
	case 0:
		{
			CString strValue;
			ctlMac.GetWindowTextA(strValue);
			strMac=strValue;
		}break;
	case 1:
		{
			strMac="null";
		}break;
	}
	pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO.clear();
	pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO.append(strDeviceId);
	pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO.push_back('|');
	pConfig->mHardware.DEFAULT_DEVICE_ID_UNIQUENO.append(strMac);

	CString strValue;
	ctlImei.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_IMEI=strValue;
	ctlMac.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_WIFI_MAC=strValue;
	ctlDeviceId.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_DEVICE_ID=strValue;
	ctlImsi.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_IMSI=strValue;
	ctlOstype.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_OS_TYPE=strValue;
	ctlOsVersion.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_OS_VERSION=strValue;
	ctlSon.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_SIM_OPERATOR_NAME=strValue;
	ctlApn.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_APN=strValue;
	ctlBrand.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_BRAND=strValue;
	ctlAndroidId.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_ANDROID_ID=strValue;
	ctlBSSID.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_BSSID=strValue;
	ctlSSID.GetWindowTextA(strValue);
	pConfig->mHardware.DEFAULT_SSID=strValue;
	AfxMessageBox("载入成功");
	CDialog::OnOK();
}


BOOL CMachineSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//设置控件属性
	ctlMac.SetLimitText(17);
	ctlBSSID.SetLimitText(17);
	ctlAndroidId.SetLimitText(16);
	ctlImei.SetLimitText(15);
	ctlImsi.SetLimitText(15);
	ctlDeviceId.SetLimitText(15);
    if (!InitMachineSetting()) 
	{
		StatusLogText("MachineSetting.ini 加载失败");
		return false;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CMachineSet::InitMachineSetting()
{
	//加载配置
	SI_Error rc = mSimpleIniA.LoadFile("MachineSetting.ini");
	if(rc<0) return FALSE;
	CSimpleIniA::TNamesDepend sections;
    mSimpleIniA.GetAllSections(sections);

	mSetsName.Clear();
	CSimpleIniA::TNamesDepend::iterator iter;
	for(iter=sections.begin();iter!=sections.end();iter++)
	{
		mSetsName.AddString(iter->pItem);
	}
	mSetsName.SetCurSel(0);
	OnCbnSelchangeCombo1();
	return TRUE;
}

void CMachineSet::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSel=NULL;
	mSetsName.GetWindowTextA(strSel);
	if(strSel.GetLength()!=0)
	{
		ctlDeviceName.SetWindowTextA(strSel);
		ctlSon.SetWindowTextA(mSimpleIniA.GetValue(strSel,"sim operator name"));
		ctlOstype.SetWindowTextA(mSimpleIniA.GetValue(strSel,"os type"));
		ctlOsVersion.SetWindowTextA(mSimpleIniA.GetValue(strSel,"os version"));
		ctlApn.SetWindowTextA(mSimpleIniA.GetValue(strSel,"apn"));
		ctlBrand.SetWindowTextA(mSimpleIniA.GetValue(strSel,"brand"));
		ctlMac.SetWindowTextA(mSimpleIniA.GetValue(strSel,"mac"));
		ctlAndroidId.SetWindowTextA(mSimpleIniA.GetValue(strSel,"android id"));
		ctlImei.SetWindowTextA(mSimpleIniA.GetValue(strSel,"imei"));
		ctlImsi.SetWindowTextA(mSimpleIniA.GetValue(strSel,"imsi"));
		ctlBSSID.SetWindowTextA(mSimpleIniA.GetValue(strSel,"bssid"));
		ctlSSID.SetWindowTextA(mSimpleIniA.GetValue(strSel,"ssid"));
		ctlDeviceId.SetWindowTextA(mSimpleIniA.GetValue(strSel,"device id"));
	}
}


void CMachineSet::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch(m_radiobtngroup1)
	{
	case 0:
		{
		}break;
	case 1:
		{
		}break;
	}
}


void CMachineSet::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	switch(m_radiobtngroup2)
	{
	case 0:
		{
		}break;
	case 1:
		{
		}break;
	}
}
