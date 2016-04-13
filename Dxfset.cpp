// Dxfset.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Dxfset.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"


// CDxfset ��ܤ��
IMPLEMENT_DYNAMIC(CDxfset, CDialogEx)
CDxfset::CDxfset(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DXFSET, pParent)
{
}
CDxfset::~CDxfset()
{
}
void CDxfset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CDxfset, CDialogEx)
END_MESSAGE_MAP()

// CDxfset �T���B�z�`��
BOOL CDxfset::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//�D�����z����
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    SetDlgItemInt(IDC_EDITCOMDXFRATE, pCompiler->m_DxfRate);
    SetDlgItemText(IDC_EDITCOMDXFZDOWN, pCompiler->m_DxfZdown);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX �ݩʭ����Ǧ^ FALSE
}
void CDxfset::OnOK()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    pCompiler->m_DxfRate = GetDlgItemInt(IDC_EDITCOMDXFRATE);
    GetDlgItemText(IDC_EDITCOMDXFZDOWN, pCompiler->m_DxfZdown);
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//�D����_���z����
    CDialogEx::OnOK();
}



