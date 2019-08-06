#include "StdAfx.h"
#include "OwnerDrawTreeCtrl.h"
#include "resource.h"		// 主符号


COwnerDrawTreeCtrl::COwnerDrawTreeCtrl(void)
{
	m_pImageList = new CImageList();  
	m_pImageList->Create(16,16,ILC_COLOR32,0,0);
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));//在线
	m_pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));//不在线
}


COwnerDrawTreeCtrl::~COwnerDrawTreeCtrl(void)
{
	if(m_pImageList!=NULL)
	{
		m_pImageList->DeleteImageList();
		delete m_pImageList;
	}
}

void COwnerDrawTreeCtrl::SetImageList()
{
	CTreeCtrl::SetImageList(m_pImageList,TVSIL_NORMAL);

	SetButtonImage(TEXT("Res\\TreeCtrl\\Button.png"));
	SetHovenImage(TEXT("Res\\TreeCtrl\\LIST_ITEM_SELECT.png"),CRect(2,2,2,2));
	SetPressImage(TEXT("Res\\TreeCtrl\\LIST_ITEM_DOWN.png"),CRect(2,2,2,2));
	SetScrollImage(this,TEXT("Res\\Scroll\\SKIN_SCROLL.bmp"));
	m_colNormalText = RGB(1,55,102);

}

void COwnerDrawTreeCtrl::SetStyle(DWORD dwAddStyle, DWORD dwRemoveStyle )
{
	DWORD dwStyle = GetStyle();

	ModifyStyle(0,dwAddStyle|dwStyle);
	ModifyStyle(dwRemoveStyle,0);
}