// Wait.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Wait.h"
#include "afxdialogex.h"


// CWait 對話方塊

IMPLEMENT_DYNAMIC(CWait, CDialogEx)

CWait::CWait(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WAITING, pParent)
{
}
CWait::~CWait()
{
}
void CWait::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CWait, CDialogEx)
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CWait 訊息處理常式
BOOL CWait::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetTimer(1, 1, NULL);
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//主視窗透明化
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CWait::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
    if (!MO_ReadIsDriving(7))
    {
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視窗恢復透明化
        CDialogEx::OnOK();
    }
#endif // MOVE  
    CDialogEx::OnTimer(nIDEvent);
}
void CWait::OnOK()
{
}
void CWait::OnCancel()
{
    //CDialogEx::OnCancel();
}
