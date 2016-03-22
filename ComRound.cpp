// ComRound.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "ComRound.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "HM_Database.h"


// CComRound 對話方塊

IMPLEMENT_DYNAMIC(CComRound, CDialogEx)

CComRound::CComRound(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMROUND, pParent)
{

}
CComRound::~CComRound()
{
}
void CComRound::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CComRound, CDialogEx)
    ON_BN_CLICKED(IDOK, &CComRound::OnBnClickedOk)
END_MESSAGE_MAP()
// CComRound 訊息處理常式

BOOL CComRound::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//主視窗透明化
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    SetDlgItemInt(IDC_EDITCOMROUNDR, pCompiler->m_RADIUS);
    ComboCheck = 0;
    if (pCompiler->m_Combobox.GetSafeHwnd()) {
        ComboCheck = pCompiler->m_Combobox.GetCurSel();
    }
    if (((CButton*)pCompiler->GetDlgItem(IDC_RADCOMROUND))->GetCheck() || ComboCheck == 2)
    {
        for (int i = IDC_RADCOMARCBIG; i <= IDC_RADCOMANTIWISE; i++)
        {
            GetDlgItem(i)->EnableWindow(FALSE);
        }
    }
    else
    {
        if (pCompiler->m_SizeChoose)
        {
            ((CButton *)GetDlgItem(IDC_RADCOMARCBIG))->SetCheck(TRUE);//選大
        }
        else
        {
            ((CButton *)GetDlgItem(IDC_RADCOMARCSMALL))->SetCheck(TRUE);//選小
        }
        if (pCompiler->m_InverseChoose)
        {
            ((CButton *)GetDlgItem(IDC_RADCOMWISE))->SetCheck(TRUE);//選大
        }
        else
        {
            ((CButton *)GetDlgItem(IDC_RADCOMANTIWISE))->SetCheck(TRUE);//選小
        }
    } 
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CComRound::OnBnClickedOk()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    if (pCompiler->m_Combobox.GetSafeHwnd()) {
        ComboCheck = pCompiler->m_Combobox.GetCurSel();
    }
    if (GetDlgItemInt(IDC_EDITCOMROUNDR) == 0)
    {
        MessageBox(_T("半徑不得為0"));
    }
    else if (((CButton*)pCompiler->GetDlgItem(IDC_RADCOMROUND))->GetCheck() || ComboCheck == 2)
    {
        pCompiler->m_RADIUS = GetDlgItemInt(IDC_EDITCOMROUNDR);
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視窗恢復透明化
        CDialogEx::OnOK();
    }
    else
    {  
        pCompiler->m_RADIUS = GetDlgItemInt(IDC_EDITCOMROUNDR);
        switch (GetCheckedRadioButton(IDC_RADCOMARCBIG, IDC_RADCOMARCSMALL))
        {
        case  IDC_RADCOMARCBIG:
            pCompiler->m_SizeChoose = TRUE;
            break;
        case  IDC_RADCOMARCSMALL:
            pCompiler->m_SizeChoose = FALSE;
            break;
        default:
            MessageBox(_T("請選擇大弧或小弧"));
            return ;
        }
        switch (GetCheckedRadioButton(IDC_RADCOMWISE, IDC_RADCOMANTIWISE))
        {
        case  IDC_RADCOMWISE:
            pCompiler->m_InverseChoose = TRUE;
            break;
        case  IDC_RADCOMANTIWISE:
            pCompiler->m_InverseChoose = FALSE;
            break;
        default:
            MessageBox(_T("請選擇順時針或逆時針"));
            return ;
        }
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視窗恢復透明化
        CDialogEx::OnOK();
    }
}
void CComRound::OnCancel()
{
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視窗恢復透明化
    CDialogEx::OnCancel();
}
