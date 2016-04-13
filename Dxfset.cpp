// Dxfset.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Dxfset.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"


// CDxfset 對話方塊
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

// CDxfset 訊息處理常式
BOOL CDxfset::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 70) / 100, LWA_ALPHA);//主視窗透明化
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    SetDlgItemInt(IDC_EDITCOMDXFRATE, pCompiler->m_DxfRate);
    SetDlgItemText(IDC_EDITCOMDXFZDOWN, pCompiler->m_DxfZdown);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CDxfset::OnOK()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    pCompiler->m_DxfRate = GetDlgItemInt(IDC_EDITCOMDXFRATE);
    GetDlgItemText(IDC_EDITCOMDXFZDOWN, pCompiler->m_DxfZdown);
    AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視恢復窗透明化
    CDialogEx::OnOK();
}



