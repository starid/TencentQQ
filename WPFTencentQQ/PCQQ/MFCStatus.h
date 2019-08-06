#pragma once


// MFCStatus

class MFCStatus : public CStatusBarCtrl
{
	DECLARE_DYNAMIC(MFCStatus)

public:
	MFCStatus();
	virtual ~MFCStatus();
	CProgressCtrl m_progres;
public:
	void SetUI();
	void SetProcessBar(UINT pos){this->m_progres.SetPos(pos);};
	void Updata(int send,int recv,int abandon);
	void UpdataUinStatus(UINT id,CString strName,CString mStatus);
protected:
	DECLARE_MESSAGE_MAP()
};


