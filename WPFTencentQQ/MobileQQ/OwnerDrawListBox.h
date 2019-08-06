#if !defined(AFX_OWNERDRAWLISTBOX_H__1AFDF05D_179F_4269_887D_B47D0D7A11FD__INCLUDED_)
#define AFX_OWNERDRAWLISTBOX_H__1AFDF05D_179F_4269_887D_B47D0D7A11FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OwnerDrawListBox.h : header file
//

#include "resource.h"		// Ö÷·ûºÅ

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox window

class COwnerDrawListBox : public CListBox
{
// Construction
public:
	COwnerDrawListBox();
	
	int AddString(LPCTSTR lpszItem, int iImg);
	int InsertString(int iIndex, LPCTSTR lpszItem, int iImg);
	void SetItemImage(int iIndex, int iImg);
private:
	int InsertString(int iIndex, LPCTSTR lpszItem);
	int AddString(LPCTSTR lpszItem);
// Attributes
public:
// Operations
public:

protected:
	CImageList* m_pImageList;

	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COwnerDrawListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(COwnerDrawListBox)
	//afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32789();
	afx_msg void On32790();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNERDRAWLISTBOX_H__1AFDF05D_179F_4269_887D_B47D0D7A11FD__INCLUDED_)
