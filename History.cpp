// History.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory ��ܤ��

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


// CHistory �T���B�z�`��
