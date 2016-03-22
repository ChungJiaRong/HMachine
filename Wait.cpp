// Wait.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Wait.h"
#include "afxdialogex.h"


// CWait ��ܤ��

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

// CWait �T���B�z�`��
BOOL CWait::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetTimer(1, 1, NULL);
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//�D�����z����
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX �ݩʭ����Ǧ^ FALSE
}
void CWait::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
    if (!MO_ReadIsDriving(7))
    {
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D������_�z����
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
