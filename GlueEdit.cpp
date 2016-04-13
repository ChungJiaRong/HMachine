// GlueEdit.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "GlueEdit.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "Compiler.h"
#include "HM_Database.h"

// CGlueEdit ��ܤ��

IMPLEMENT_DYNAMIC(CGlueEdit, CDialogEx)
CGlueEdit::CGlueEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GLUEEDIT, pParent)
{
}
CGlueEdit::~CGlueEdit()
{
}
void CGlueEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CGlueEdit, CDialogEx)
    ON_BN_CLICKED(IDOK, &CGlueEdit::OnBnClickedOk)
END_MESSAGE_MAP()

// CGlueEdit �T���B�z�`��
BOOL CGlueEdit::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//�D�����z����
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    SetDlgItemText(IDC_EDITGLTIME,((CHM_Database*)pView->GetDocument()->m_OtherArray.GetAt(1))->m_Stand);
    return TRUE;
}
void CGlueEdit::OnBnClickedOk()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CString StrBuff;
    GetDlgItemText(IDC_EDITGLTIME, StrBuff);
    CHM_Database *pHM_Database = new CHM_Database(StrBuff);
    pView->GetDocument()->m_OtherArray.SetAt(1, pHM_Database);
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D������_�z����
    CDialogEx::OnOK();
}
void CGlueEdit::OnCancel()
{
    //CDialogEx::OnCancel();
}
