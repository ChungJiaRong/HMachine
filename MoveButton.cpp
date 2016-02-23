// MoveButton.cpp : ��@��
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

// CMoveButton �T���B�z�`��
/*���s���U*/
void CMoveButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
    
    SetTimer(1, 100, NULL);   
    CButton::OnLButtonDown(nFlags, point);
}
/*���s��}*/
void CMoveButton::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
#ifdef MOVE
    MO_DecSTOP();
#endif // MOVE
    KillTimer(1);
    CButton::OnLButtonUp(nFlags, point);
}
/*�p�ư��榸��*/
void CMoveButton::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//����w�إߪ�View���w
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
    CCompiler* pCompiler = (CCompiler*)pView->m_DlgArray.GetAt(1);
#ifdef MOVE
    if (MoveX || MoveY)
    {
        switch (pCompiler->GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
        {
        case IDC_RADCOMHS:
            MO_Do2DLineMove(MoveX, MoveY, pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
            break;
        case IDC_RADCOMMS:
            MO_Do2DLineMove(MoveX, MoveY, pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
            break;
        case IDC_RADCOMLS:
            MO_Do2DLineMove(MoveX, MoveY, pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
            break;
        default:
            break;
        }
    }
    if (MoveZ)
    {
        switch (pCompiler->GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
        {
        case IDC_RADCOMHS:
            MO_DoZLineMove(MoveZ, pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
            break;
        case IDC_RADCOMMS:
            MO_DoZLineMove(MoveZ, pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
            break;
        case IDC_RADCOMLS:
            MO_DoZLineMove(MoveZ, pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
            break;
        default:
            break;
        }
    }
#endif // MOVE 
    WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("�ƹ�"), _T("���U"));
    CButton::OnTimer(nIDEvent);
}
