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
    // TODO:  �b���[�J�B�~����l��
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    if (pCompiler->m_GlueTime != 0)
    {
        SetDlgItemInt(IDC_EDITGLTIME, pCompiler->m_GlueTime);
    }
    return TRUE;
}
void CGlueEdit::OnBnClickedOk()
{
    // TODO: �b���[�J����i���B�z�`���{���X
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    pCompiler->m_GlueTime = GetDlgItemInt(IDC_EDITGLTIME);
    CDialogEx::OnOK();
}



