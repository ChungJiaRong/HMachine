// ComRound.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "ComRound.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "HM_Database.h"


// CComRound ��ܤ��

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
// CComRound �T���B�z�`��

BOOL CComRound::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//�D�����z����
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
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
            ((CButton *)GetDlgItem(IDC_RADCOMARCBIG))->SetCheck(TRUE);//��j
        }
        else
        {
            ((CButton *)GetDlgItem(IDC_RADCOMARCSMALL))->SetCheck(TRUE);//��p
        }
        if (pCompiler->m_InverseChoose)
        {
            ((CButton *)GetDlgItem(IDC_RADCOMWISE))->SetCheck(TRUE);//��j
        }
        else
        {
            ((CButton *)GetDlgItem(IDC_RADCOMANTIWISE))->SetCheck(TRUE);//��p
        }
    } 
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX �ݩʭ����Ǧ^ FALSE
}
void CComRound::OnBnClickedOk()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    if (pCompiler->m_Combobox.GetSafeHwnd()) {
        ComboCheck = pCompiler->m_Combobox.GetCurSel();
    }
    if (GetDlgItemInt(IDC_EDITCOMROUNDR) == 0)
    {
        MessageBox(_T("�b�|���o��0"));
    }
    else if (((CButton*)pCompiler->GetDlgItem(IDC_RADCOMROUND))->GetCheck() || ComboCheck == 2)
    {
        pCompiler->m_RADIUS = GetDlgItemInt(IDC_EDITCOMROUNDR);
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D������_�z����
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
            MessageBox(_T("�п�ܤj���Τp��"));
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
            MessageBox(_T("�п�ܶ��ɰw�ΰf�ɰw"));
            return ;
        }
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D������_�z����
        CDialogEx::OnOK();
    }
}
void CComRound::OnCancel()
{
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D������_�z����
    CDialogEx::OnCancel();
}
