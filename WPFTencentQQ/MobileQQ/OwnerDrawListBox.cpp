// OwnerDrawListBox.cpp : implementation file
//

#include "stdafx.h"
#include "OwnerDrawListBox.h"
#include"UserMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox

COwnerDrawListBox::COwnerDrawListBox()
{
	m_pImageList = new CImageList();  
	m_pImageList->Create(16, 16, ILC_MASK, 0, 0); // 必不可少  
	
	m_pImageList->Add(AfxGetApp()->LoadIcon(""));         //0在线
	m_pImageList->Add(AfxGetApp()->LoadIcon(""));		//1不在线
}

COwnerDrawListBox::~COwnerDrawListBox()
{
	if(m_pImageList!=NULL)
		delete m_pImageList;
}


BEGIN_MESSAGE_MAP(COwnerDrawListBox, CListBox)
//{{AFX_MSG_MAP(COwnerDrawListBox)
ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32789, &COwnerDrawListBox::On32789)
	ON_COMMAND(ID_32790, &COwnerDrawListBox::On32790)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox message handlers

void COwnerDrawListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// Changes the Width and the Height of item in the list box	
	lpMeasureItemStruct->itemHeight = 20;
}

void COwnerDrawListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
		// TODO: Add your code to draw the specified item

	CDC* pDC    = CDC::FromHandle(lpDrawItemStruct->hDC);

	if ((int)lpDrawItemStruct->itemID < 0)
	{
		// If there are no elements in the List Box 
		// based on whether the list box has Focus or not 
		// draw the Focus Rect or Erase it,
		if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && 
			(lpDrawItemStruct->itemState & ODS_FOCUS))
		{
			pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
		}
		else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) &&	
			!(lpDrawItemStruct->itemState & ODS_FOCUS)) 
		{
			pDC->DrawFocusRect(&lpDrawItemStruct->rcItem); 
		}
		return;
	}

    CRect  rcItem(lpDrawItemStruct->rcItem); // To draw the focus rect.
    CRect  rClient(rcItem); // Rect to highlight the Item
    CRect  rText(rcItem); // Rect To display the Text
    CPoint Pt( rcItem.left , rcItem.top ); // Point To draw the Image

	// if the Image list exists for the list box
	// adjust the Rect sizes to accomodate the Image for each item.
	if(m_pImageList)
	{
		rClient.left += 16;		//略过图像
		rText.left += 26;		//略过图像并保持10距离
		//rText.top += 2;
	}
	else
	{
		rText.top += 2;
	}


	COLORREF crText;
	CString strText;

	// Image information in the item data.
	int iImg = (int)lpDrawItemStruct->itemData;

	// If item selected, draw the highlight rectangle.
	// Or if item deselected, draw the rectangle using the window color.
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		 (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush br(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(&rClient, &br);
	}
	else if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && 
		(lpDrawItemStruct->itemAction & ODA_SELECT)) 
	{
		CBrush br(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&rClient, &br);
	}

	// If the item has focus, draw the focus rect.
	// If the item does not have focus, erase the focus rect.
	if ((lpDrawItemStruct->itemAction & ODA_FOCUS) && 
		(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		pDC->DrawFocusRect(&rcItem); 
	}
	else if ((lpDrawItemStruct->itemAction & ODA_FOCUS) &&	
		!(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		pDC->DrawFocusRect(&rcItem); 
	}

	// To draw the Text set the background mode to Transparent.
	int iBkMode = pDC->SetBkMode(TRANSPARENT);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		crText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	else if (lpDrawItemStruct->itemState & ODS_DISABLED)
		crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
	else
		crText = pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));

	// Get the item text.
	GetText(lpDrawItemStruct->itemID, strText);

	// Setup the text format.
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;
	

	// if the ImageList is Existing and there is an associated Image
	// for the Item, draw the Image.
	if(m_pImageList && (iImg != -1 ) )
		m_pImageList->Draw(pDC,iImg,Pt,ILD_NORMAL);
	
	//Draw the Text
	pDC->DrawText(strText, -1, &rText, nFormat | DT_CALCRECT);
	pDC->DrawText(strText, -1, &rText, nFormat);

	pDC->SetTextColor(crText); 
	pDC->SetBkMode(iBkMode);
}

void COwnerDrawListBox::OnRButtonDown(UINT nFlags, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nCount = GetCount();
    //实现右键点击选中目标
	for (int i =0; i<nCount; i++)
    {
		CRect rc;
		GetItemRect(i, &rc);
		if(rc.PtInRect(pt))
		{
			SetCurSel(i);
			CMenu temp,*ptr=NULL;
            temp.LoadMenu(IDR_MENU2);
            ptr = temp.GetSubMenu(0);
			if(ptr==NULL) return;
            ClientToScreen(&pt);
            ptr->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
			temp.DestroyMenu();
           break;
        }
	}
	CListBox::OnRButtonDown(nFlags, pt);
}

void COwnerDrawListBox::On32789()
{
	// TODO: 在此添加命令处理程序代码
	ActionCommand mCmd={0};
	mCmd.sCmd=ACTION_SEND_MSG;
	mCmd.sSubCmd=GetCurSel();

	::SendMessage(::AfxGetMainWnd()->m_hWnd,WM_TRANSMIT_MSG,(WPARAM)&mCmd,NULL);
}

void COwnerDrawListBox::On32790()
{
	// TODO: 在此添加命令处理程序代码
	ActionCommand mCmd={0};
	mCmd.sSubCmd=ACTION_QUERY_USERDATA;
	mCmd.sSubCmd=GetCurSel();

	::SendMessage(::AfxGetMainWnd()->m_hWnd,WM_TRANSMIT_MSG,(WPARAM)&mCmd,NULL);
}

int COwnerDrawListBox::AddString(LPCTSTR lpszItem)
{
	int iRet = CListBox::AddString(lpszItem);
	if (iRet >= 0)
		SetItemData(iRet, -1);
	return iRet;
}

int COwnerDrawListBox::AddString(LPCTSTR lpszItem, int iImg)
{
	int iRet = CListBox::AddString(lpszItem);
	if (iRet >= 0)
		SetItemData(iRet, iImg);
	return iRet;
}

int COwnerDrawListBox::InsertString(int iIndex, LPCTSTR lpszItem)
{
	int iRet = CListBox::InsertString(iIndex,lpszItem);
	if (iRet >= 0)
		SetItemData(iRet, -1);
	return iRet;
}

int COwnerDrawListBox::InsertString(int iIndex, LPCTSTR lpszItem, int iImg)
{
	int iRet = CListBox::InsertString(iIndex,lpszItem);
	if (iRet >= 0)
		SetItemData(iRet, iImg);
	return iRet;
}

//用于更改图标时使用
void COwnerDrawListBox::SetItemImage(int iIndex, int iImg)
{
	SetItemData(iIndex, iImg);
	RedrawWindow();
}