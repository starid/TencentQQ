#pragma once
#include"GlobeVar.h"
class COwnerDrawTreeCtrl :
	public CSkinTreeCtrl
{
public:
	COwnerDrawTreeCtrl(void);
	virtual ~COwnerDrawTreeCtrl(void);
private:
	CImageList* m_pImageList;
public:
	void SetImageList();
	void SetStyle(DWORD dwAddStyle, DWORD dwRemoveStyle );
};

