#include "StdAfx.h"
#include "SeqSerial.h"
#include "QQDlg.h"
#include"GlobeVar.h"
#include"../CCodecWarpper/PackReq.h"

unsigned int CSeqSerial::SeqSerial=0;
std::map<unsigned int,FPSeqMessageCallBack>  CSeqSerial::funcs_of_maps;


unsigned int CSeqSerial::GetNexSeq(FPSeqMessageCallBack mFunc)
{
	unsigned int i=++SeqSerial;
	if(i>100000)
		SeqSerial=rand() % 40001 + 60000;
	if(mFunc!=NULL)
	{
		if(funcs_of_maps.find(SeqSerial)==funcs_of_maps.end())
		{
			funcs_of_maps.insert(std::pair<unsigned int,FPSeqMessageCallBack>(SeqSerial,mFunc));
		}
	}
	return SeqSerial;
}

void CSeqSerial::SeqRun(unsigned int mSeq,LPVOID lParam1, LPVOID lParam2)
{
	if(funcs_of_maps.find(mSeq)!=funcs_of_maps.end())
	{
		funcs_of_maps[mSeq](lParam1,lParam2);
		//删除当前回调函数
		funcs_of_maps.erase(mSeq);
	}else
	{
		default_func(NULL,NULL);
	}
}


void CSeqSerial::default_func(LPVOID lParam1, LPVOID lParam2)
{
	int i=0;
}

void CSeqSerial::initial_RequestQueryQQBindingStat(LPVOID lParam1, LPVOID lParam2)
{
	COffineQQDlg *pMainDlg=static_cast<COffineQQDlg *>(lParam1);
	CRespondQueryQQBindingStat *pResp=static_cast<CRespondQueryQQBindingStat *>(lParam2);
	if(pMainDlg==NULL||pResp==NULL) return;
	GlobeVar::mRespondQueryQQBindingStat=*pResp;
	delete pResp;
	pResp=NULL;
}

void CSeqSerial::CMobileNo_RequestQueryQQBindingStat(LPVOID lParam1, LPVOID lParam2)
{
	COffineQQDlg *pMainDlg=static_cast<COffineQQDlg *>(lParam1);
	if(pMainDlg->pMobileQuery!=NULL&&pMainDlg->pMobileQuery->m_hWnd!=NULL)
	{
		//发送消息
		::PostMessageA(pMainDlg->pMobileQuery->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)lParam2);
	}
}

void CSeqSerial::CMobileNo_RequestBindMobile(LPVOID lParam1, LPVOID lParam2)
{
	CMobileNo *pMainDlg=static_cast<COffineQQDlg *>(lParam1)->pMobileQuery;
	if(pMainDlg!=NULL&&pMainDlg->m_hWnd!=NULL)
	{
		//发送消息,需等待消息完成
		SendMessageA(pMainDlg->m_hWnd,WM_RECEIVED_MSG,2,(LPARAM)lParam2);
		//继续请求下一个
		pMainDlg->mBindMobile.dwCurSel++;
		if(pMainDlg->mBindMobile.dwCurSel<pMainDlg->mBindMobile.mBindInfos.size())
		{
			//继续请求
			std::string strmobileNo=pMainDlg->mBindMobile.mBindInfos[pMainDlg->mBindMobile.dwCurSel].strMobileNo;
			std::string strnationCode=pMainDlg->mBindMobile.mBindInfos[pMainDlg->mBindMobile.dwCurSel].strNationCode;
			CPackReq mPack;
			mPack.SetPacketType(account_RequestBindMobile);
			mPack.SetSeq(pMainDlg->mSeqSerial.GetNexSeq(CSeqSerial::CMobileNo_RequestBindMobile));
			//取第一个数据
			pMainDlg->pConfig->mRequestBindMobile.mobileNo.value(strmobileNo);
			pMainDlg->pConfig->mRequestBindMobile.nationCode.value(strnationCode);
			mPack.pConfig=pMainDlg->pConfig;
			mPack.PackData();
			SendPacket(pMainDlg->pConfig->m_iCurrentClientID,&(mPack.pack));
		}
	}
}