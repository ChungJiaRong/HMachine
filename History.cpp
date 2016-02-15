// History.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory 對話方塊

IMPLEMENT_DYNAMIC(CHistory, CDialogEx)

CHistory::CHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTORY, pParent)
{

}

CHistory::~CHistory()
{
}

void CHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistory, CDialogEx)
END_MESSAGE_MAP()


// CHistory 訊息處理常式
