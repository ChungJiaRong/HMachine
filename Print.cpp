// Print.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Print.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "HM_Database.h"


// CPrint 對話方塊

IMPLEMENT_DYNAMIC(CPrint, CDialogEx)

CPrint::CPrint(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PRINT, pParent)
{

}

CPrint::~CPrint()
{
}

void CPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPrint, CDialogEx)
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CPrint 訊息處理常式

BOOL CPrint::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    MO_Change(Draw);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CPrint::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
    CWnd *pWnd;
    for (int i = IDC_PICDRAW; i <= IDC_STARANK; i++)
    {
        pWnd = GetDlgItem(i);
        ChangeSize(pWnd, cx, cy);
    }
    pWnd = GetDlgItem(IDOK);
    ChangeSize(pWnd, cx, cy);
    GetClientRect(&m_InitRect);
}
/*改變控件大小*/
void CPrint::ChangeSize(CWnd* pWnd, int cx, int cy)
{
    if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建   
    {
        CRect Rect;   //获取控件变化前的大小    
        pWnd->GetWindowRect(&Rect);
        ScreenToClient(&Rect);//将控件大小转换为在对话框中的区域坐标 
                              //控件隨著視窗變大而變大-缺點位置會改變
        Rect.left = 1;
        Rect.right = cx;
        Rect.top = 1;
        Rect.bottom = Rect.bottom*cy / m_InitRect.Height();
        pWnd->MoveWindow(Rect);//设置控件大小
    }
}
void CPrint::MO_Draw(std::vector<std::vector<CString> > &csVecWorkPoint2Dim,CDC *pDC, float m_fScale)
{
    
    /*繪圖開始*/
    CString csBufXY, csX, csY;
    CPoint ptMov, ptCen;
    int iRadius;
    static int drawCnt = 0;

    while (drawCnt<csVecWorkPoint2Dim.size())
    {
        CString csBuf;//線段種類
        csBuf = csVecWorkPoint2Dim.at(drawCnt).at(5);
        /*CString csCnt;
        csCnt.Format(L"%d", drawCnt);//工作點的編號*/
        if (csBuf.Left(1) == L"圓")
        {
            CString csCenX, csCenY;
            float sRad, eRad;
            if (csVecWorkPoint2Dim.at(drawCnt).capacity() == 6)
            {
                sRad = 0;
                eRad = 360;

                csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(0);
                csX = csBufXY.Left(csBufXY.Find(L'，'));
                csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(5);
                int findFlag = 2, spot1st, spot2nd, spot3rd;
                spot1st = csBufXY.Find(L"，");
                spot2nd = csBufXY.Find(L"，", spot1st + 1);
                spot3rd = csBufXY.Find(L"，", spot2nd + 1);
                csCenX = csBufXY.Mid(spot1st + 1, spot2nd - spot1st - 1);
                csCenY = csBufXY.Mid(spot2nd + 1, spot3rd - spot2nd - 1);

                ptMov.x = (_ttoi(csCenX) * 2 - _ttoi(csX))*m_fScale;
                ptMov.y = _ttoi(csCenY)*m_fScale;
                ptCen.x = _ttoi(csCenX)*m_fScale;
                ptCen.y = _ttoi(csCenY)*m_fScale;
                iRadius = (_ttoi(csCenX) - _ttoi(csX))*m_fScale;
                CString csType = csVecWorkPoint2Dim.at(drawCnt).at(4);
                if (csType == L"塗膠")
                {
                    pDC->MoveTo(ptMov);
                    pDC->AngleArc(ptCen.x, ptCen.y, iRadius, sRad, eRad);
                }
                else
                {
                }
            }
            else//圓弧
            {
                sRad = _ttof(csVecWorkPoint2Dim.at(drawCnt).at(6));
                eRad = _ttof(csVecWorkPoint2Dim.at(drawCnt).at(7));

                int spot1st, spot2nd, spot3rd;
                /*analyze start point: x,y*/
                csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(0);
                spot1st = csBufXY.Find(L"，");
                spot2nd = csBufXY.Find(L"，", spot1st + 1);
                csX = csBufXY.Left(csBufXY.Find(L'，'));
                csY = csBufXY.Mid(spot1st + 1, spot2nd - spot1st - 1);

                /*analyze Arc center point: x,y*/
                csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(5);
                spot1st = csBufXY.Find(L"，");
                spot2nd = csBufXY.Find(L"，", spot1st + 1);
                spot3rd = csBufXY.Find(L"，", spot2nd + 1);
                csCenX = csBufXY.Mid(spot1st + 1, spot2nd - spot1st - 1);
                csCenY = csBufXY.Mid(spot2nd + 1, spot3rd - spot2nd - 1);

                ptMov.x = _ttoi(csX)*m_fScale;
                ptMov.y = _ttoi(csY)*m_fScale;
                ptCen.x = _ttoi(csCenX)*m_fScale;
                ptCen.y = _ttoi(csCenY)*m_fScale;
                iRadius = _ttof(csVecWorkPoint2Dim.at(drawCnt).at(8))*m_fScale;


                /*analyze end point: x,y,z*/
                CString csBufXYZ;
                int iEndX, iEndY, iZ;
                csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(2);
                spot1st = csBufXY.Find(L"，");
                spot2nd = csBufXY.Find(L"，", spot1st + 1);
                csX = csBufXY.Left(csBufXY.Find(L'，'));
                csY = csBufXY.Mid(spot1st + 1, spot2nd - spot1st - 1);
                iEndX = _ttoi(csX)*m_fScale;
                iEndY = _ttoi(csY)*m_fScale;
                iZ = _ttoi(csVecWorkPoint2Dim.at(drawCnt).at(3))*m_fScale;
                csBufXYZ.Format(L"%d，%d，%d", iEndX, iEndY, iZ);

                CString csType = csVecWorkPoint2Dim.at(drawCnt).at(4);
                if (csType == L"塗膠")
                {
                    pDC->MoveTo(ptMov);
                    pDC->AngleArc(ptCen.x, ptCen.y, iRadius, -sRad, eRad - sRad);
                }
                else
                {
                    ptMov.x = iEndX;
                    ptMov.y = iEndY;
                    CRect rect(ptMov.x - 2, ptMov.y + 2, ptMov.x + 2, ptMov.y - 2);
                    ptMov.x -= 2;
                    pDC->Arc(rect, ptMov, ptMov);
                }
            }
        }
        else if (csBuf == L"直線")
        {
            csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(0);
            csX = csBufXY.Left(csBufXY.Find(L'，'));
            csY = csBufXY.Mid(csBufXY.Find(L'，') + 1,
                csBufXY.ReverseFind(L'，') - csBufXY.Find(L'，') - 1);

            ptMov.x = _ttoi(csX)*m_fScale;
            ptMov.y = _ttoi(csY)*m_fScale;

            CString csType = csVecWorkPoint2Dim.at(drawCnt).at(4);
            if (csType == L"塗膠")
            {
                pDC->MoveTo(ptMov);
            }
            else {}

            csBufXY = csVecWorkPoint2Dim.at(drawCnt).at(2);
            csX = csBufXY.Left(csBufXY.Find(L'，'));
            csY = csBufXY.Mid(csBufXY.Find(L'，') + 1,
                csBufXY.ReverseFind(L'，') - csBufXY.Find(L'，') - 1);

            ptMov.x = _ttoi(csX)*m_fScale;
            ptMov.y = _ttoi(csY)*m_fScale;

            if (csType == L"塗膠")
            {
                pDC->LineTo(ptMov);
            }
            else
            {
                CRect rect(ptMov.x - 2, ptMov.y + 2, ptMov.x + 2, ptMov.y - 2);
                ptMov.x -= 2;
                pDC->Arc(rect, ptMov, ptMov);
            }
        }
        drawCnt++;
    }
    drawCnt = 0;
    
}
void CPrint::MO_Change(std::vector<std::vector<CString>>& csVecWorkPoint2Dim)
{  
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    int WorkCount = pView->GetDocument()->m_WorkArray.GetSize();
    csVecWorkPoint2Dim.clear();
    std::vector<CString> csVecListRow;
    for (int i = 0; i < WorkCount; i++) 
    {
        csVecListRow.push_back(CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptOrigin,3));
        csVecListRow.push_back(CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptOrigin,2));
        csVecListRow.push_back(CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptEnd,3));
        csVecListRow.push_back(CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptEnd,2));
        csVecListRow.push_back(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_Action);
        csVecListRow.push_back(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_MoveType);
        csVecWorkPoint2Dim.push_back(csVecListRow);
        csVecListRow.clear();
    }
}
CString CPrint::CStringToXY(CString Data, int Choose) {
    int iLength = Data.Find(_T('，'));
    int iLength2 = Data.Right(Data.GetLength() - iLength - 1).Find(_T('，'));
    if (Choose == 0)
    {
        return Data.Left(iLength);
    }
    else if (Choose == 1)
    {
        return Data.Right(Data.GetLength() - iLength - 1).Left(iLength2);
    }
    else if (Choose == 2)
    {
        return Data.Right(Data.GetLength() - iLength - 1).Right((Data.Right(Data.GetLength() - iLength - 1)).GetLength() - iLength2 - 1);//從右讀回來Data.GetLength()-iLength-1多個字元
    }
    else
    {
        return Data.Left(iLength + iLength2 + 2);
    }
}
void CPrint::OnPaint()
{
    CPaintDC dc(this);
    CRect src;
    CWnd *twnd = GetDlgItem(IDC_PICDRAW);
    twnd->GetWindowRect(&src);
    ScreenToClient(&src);
    CString a;
    a.Format(L"%d,%d,%d,%d", src.Height(), src.Width(), src.top, src.bottom);
    SetDlgItemText(IDC_STARANK,a);
    CDC *pDC = twnd->GetDC();
    MO_Draw(Draw, pDC, 1.00);
}




