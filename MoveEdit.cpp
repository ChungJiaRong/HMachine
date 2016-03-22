// MoveEdit.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "MoveEdit.h"

// CMoveEdit

IMPLEMENT_DYNAMIC(CMoveEdit, CEdit)

CMoveEdit::CMoveEdit()
{
}
CMoveEdit::~CMoveEdit()
{
}
BEGIN_MESSAGE_MAP(CMoveEdit, CEdit)
    ON_WM_RBUTTONDOWN()
    ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()
// CMoveEdit 訊息處理常式
void CMoveEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
#ifdef MOVE
    CString StrBuff;
    switch (GetDlgCtrlID())
    {
    case IDC_EDITCOMABSVX:
        StrBuff.Format(_T("%d"), MO_ReadLogicPosition(0));
        SetWindowText(StrBuff);
        break;
    case IDC_EDITCOMABSVY:
        StrBuff.Format(_T("%d"), MO_ReadLogicPosition(1));
        SetWindowText(StrBuff);
        break;
    case IDC_EDITCOMABSVZ:
        StrBuff.Format(_T("%d"), MO_ReadLogicPosition(2));
        SetWindowText(StrBuff);
        break;
    default:
        break;
    }
#endif // MOVE
    CEdit::OnRButtonDown(nFlags, point);
}
/*用來取消菜單*/
void CMoveEdit::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
    
}
