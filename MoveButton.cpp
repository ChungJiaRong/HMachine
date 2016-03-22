// MoveButton.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "MoveButton.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"

// CMoveButton

IMPLEMENT_DYNAMIC(CMoveButton, CButton)

CMoveButton::CMoveButton()
{
    MoveX = 0;
    MoveY = 0;
    MoveZ = 0;
}
CMoveButton::~CMoveButton()
{
}

BEGIN_MESSAGE_MAP(CMoveButton, CButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_TIMER()
END_MESSAGE_MAP()

// CMoveButton 訊息處理常式
/*按鈕按下*/
void CMoveButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetTimer(1, 1, NULL);   
    CButton::OnLButtonDown(nFlags, point);
}
/*按鈕放開*/
void CMoveButton::OnLButtonUp(UINT nFlags, CPoint point)
{
#ifdef MOVE
    MO_DecSTOP();
#endif // MOVE
    KillTimer(1);
    CButton::OnLButtonUp(nFlags, point);
}
/*計數執行次數*/
void CMoveButton::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
    switch (pCompiler->GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
    {
    case IDC_RADCOMHS:
        MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
        break;
    case IDC_RADCOMMS:
        MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
        break;
    case IDC_RADCOMLS:
        MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
        break;
    default:
        MessageBox(_T("程式出現錯誤!"));
        break;
    }
#endif // MOVE
    WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("滑鼠"), _T("按下"));
    CButton::OnTimer(nIDEvent);
}
