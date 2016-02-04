// SkinFrameWnd.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "SkinFrameWnd.h"


// CSkinFrameWnd
IMPLEMENT_DYNCREATE(CSkinFrameWnd, CFrameWnd)
CSkinFrameWnd::CSkinFrameWnd()
{
    m_nTitleHeight = 25;
    m_nFrameWidth = 2;
    m_pBkImage = CSkinManager::GetInstance()->GetSkinItem(_T("dialog\\DialogBkg.png"));
}
CSkinFrameWnd::~CSkinFrameWnd()
{
}
BEGIN_MESSAGE_MAP(CSkinFrameWnd, CFrameWnd)
    ON_WM_NCPAINT()
    ON_WM_NCACTIVATE()
    ON_WM_NCCALCSIZE()
    ON_WM_NCCREATE()
    ON_WM_ACTIVATE()
    ON_WM_SIZE()
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()
// CSkinFrameWnd 訊息處理常式
void CSkinFrameWnd::OnNcPaint()
{
    // TODO: 在此加入您的訊息處理常式程式碼
    // 不要呼叫圖片訊息的 CFrameWndEx::OnNcPaint()
    CWindowDC dc(this);
    if (m_pBkImage == NULL)
    {
        return;
    }
    CDC MemDC; //記憶體DC
               //獲取位置
    CRect rcWindow;
    GetWindowRect(&rcWindow);
    rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

    CRect rcClient;
    GetClientRect(&rcClient);

    //剪除掉客戶區
    rcClient.OffsetRect(m_nFrameWidth, m_nTitleHeight);
    dc.ExcludeClipRect(rcClient.left, rcClient.top,
        rcClient.right, rcClient.bottom);

    MemDC.CreateCompatibleDC(&dc);

    CBitmap bmp;
    bmp.CreateCompatibleBitmap(&dc, rcWindow.Width(), rcWindow.Height());
    MemDC.SelectObject(&bmp);
    MemDC.SetBkMode(TRANSPARENT);

    Gdiplus::Graphics graphics(MemDC.GetSafeHdc());
    RectF destRect;

    //繪製底部和邊框
    destRect.X = 0;
    destRect.Y = rcWindow.Height() - m_nFrameWidth;
    destRect.Width = rcWindow.Width();
    destRect.Height = m_nFrameWidth;
    graphics.DrawImage(m_pBkImage, destRect, m_nTitleHeight, m_pBkImage->GetHeight() - m_nFrameWidth, m_nFrameWidth, m_nFrameWidth, UnitPixel);

    destRect.X = rcWindow.right - m_nTitleHeight;
    destRect.Y = rcWindow.bottom - m_nTitleHeight;
    destRect.Width = m_nTitleHeight;
    destRect.Height = m_nTitleHeight;
    graphics.DrawImage(m_pBkImage, destRect, m_pBkImage->GetWidth() - m_nTitleHeight, m_pBkImage->GetHeight() - m_nTitleHeight, m_nTitleHeight, m_nTitleHeight, UnitPixel);

    destRect.X = 0;
    destRect.Y = rcWindow.Height() - m_nTitleHeight;
    destRect.Width = m_nTitleHeight;
    destRect.Height = m_nTitleHeight;
    graphics.DrawImage(m_pBkImage, destRect, 0, m_pBkImage->GetHeight() - m_nTitleHeight, m_nTitleHeight, m_nTitleHeight, UnitPixel);

    //左邊框
    destRect.X = 0;
    destRect.Y = m_nTitleHeight;
    destRect.Width = m_nFrameWidth;
    destRect.Height = rcWindow.Height() - 2 * m_nTitleHeight;
    graphics.DrawImage(m_pBkImage, destRect, 0, m_nTitleHeight, m_nFrameWidth, m_nFrameWidth, UnitPixel);


    //右邊框
    destRect.X = rcWindow.Width() - m_nFrameWidth;
    destRect.Y = m_nTitleHeight;
    destRect.Width = m_nFrameWidth;
    destRect.Height = rcWindow.Height() - 2 * m_nTitleHeight;
    graphics.DrawImage(m_pBkImage, destRect, m_pBkImage->GetWidth() - m_nFrameWidth, m_nTitleHeight, m_nFrameWidth, m_nFrameWidth, UnitPixel);

    //繪製標題欄
    destRect.X = 0;
    destRect.Y = 0;
    destRect.Width = rcWindow.Width();
    destRect.Height = m_nTitleHeight;
    graphics.DrawImage(m_pBkImage, destRect, 50, 0, 5, m_nTitleHeight, UnitPixel);
    graphics.DrawImage(m_pBkImage, 0, 0, 0, 0, 50, m_nTitleHeight, UnitPixel);
    graphics.DrawImage(m_pBkImage, rcWindow.Width() - 50, 0, m_pBkImage->GetWidth() - 50, 0, 50, m_nTitleHeight, UnitPixel);

    ///*標題列圖標*/
    int xPos = 5;
    int yPos = 5;
    HICON hIcon = (HICON)GetClassLongPtr(m_hWnd, GCLP_HICONSM);
    //HICON hIcon = GetIcon(FALSE);
    if (hIcon)
    {
        DrawIconEx(MemDC, xPos, yPos - 2, hIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, 0, DI_NORMAL);

        xPos += GetSystemMetrics(SM_CXSMICON);
        xPos += 10;
    }

    /*標題列文字*/
    CString strText;
    GetWindowText(strText);
    if (!strText.IsEmpty())
    {
        LOGFONT lfFont;
        memset(&lfFont, 0, sizeof(lfFont));
        lfFont.lfHeight = -12;
        lfFont.lfWeight |= FW_BOLD;
        lstrcpy(lfFont.lfFaceName, _T(" 宋体"));
        Gdiplus::Font font(dc.GetSafeHdc(), &lfFont);

        StringFormat stringFormat;
        stringFormat.SetFormatFlags(StringFormatFlagsNoWrap);
        stringFormat.SetAlignment(StringAlignmentNear);
        stringFormat.SetLineAlignment(StringAlignmentNear);
        CStringW strTitle(strText);
        SolidBrush brush((ARGB)Color::White);
        PointF point;

        point.X = (Gdiplus::REAL)xPos;
        point.Y = (Gdiplus::REAL)yPos;
        graphics.DrawString(strTitle, strTitle.GetLength(), &font, point, &stringFormat, &brush);
    }
    dc.BitBlt(0, 0, rcWindow.Width(), rcWindow.Height(), &MemDC, 0, 0, SRCCOPY);
    dc.SelectClipRgn(NULL);
}
BOOL CSkinFrameWnd::OnNcActivate(BOOL bActive)
{
    // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
    OnNcPaint();
    return TRUE;
    //return CFrameWndEx::OnNcActivate(bActive);
}
void CSkinFrameWnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
    // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
    if (bCalcValidRects)
    {
        CRect& rc = (CRect&)lpncsp->rgrc[0];//get the client rectangle   
        rc.top += m_nTitleHeight;
        rc.left += m_nFrameWidth;
        rc.bottom -= m_nFrameWidth;
        rc.right -= m_nFrameWidth;
    }
    //CFrameWndEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}
BOOL CSkinFrameWnd::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (!CFrameWnd::OnNcCreate(lpCreateStruct))
        return FALSE;

    // TODO:  在此加入特別建立的程式碼
    CRect rcWnd;
    GetWindowRect(&rcWnd);
    rcWnd.OffsetRect(-rcWnd.left, -rcWnd.top);

    CRect rcControl;
    rcControl.left = rcWnd.right - 35;
    rcControl.top = 5;
    rcControl.right = rcControl.left + 20;
    rcControl.bottom = rcControl.top + 20;
    return TRUE;
}
void CSkinFrameWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
    OnNcPaint();
    // TODO: 在此加入您的訊息處理常式程式碼
}
void CSkinFrameWnd::OnSize(UINT nType, int cx, int cy)
{
    CFrameWnd::OnSize(nType, cx, cy);

    // TODO: 在此加入您的訊息處理常式程式碼
    if (nType != SIZE_MINIMIZED && nType != SIZE_MAXHIDE)
    {
        if (m_Rgn.GetSafeHandle())
        {
            m_Rgn.DeleteObject();
        }
        CRect rc;
        GetWindowRect(&rc); //获得窗口矩形
        rc -= rc.TopLeft();
        m_Rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right + 1, rc.bottom + 1, 5, 5); //根据窗口矩形创建一个圆角矩形
        SetWindowRgn(m_Rgn, TRUE); //根据圆角矩形指定的区域改变窗口的形状
    }
    if (nType == SIZE_MAXIMIZED ||
        nType == SIZE_RESTORED)
    {
        OnNcPaint();
    }
}
void CSkinFrameWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    // TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
    lpMMI->ptMinTrackSize.x = 550;
    lpMMI->ptMinTrackSize.y = 320;
    lpMMI->ptMaxPosition.x = 0.5;
    lpMMI->ptMaxPosition.y = 0.5;
    CRect rcWorkArea;
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
    lpMMI->ptMaxSize.x = lpMMI->ptMaxTrackSize.x = rcWorkArea.Width() - 0.5;
    lpMMI->ptMaxSize.y = lpMMI->ptMaxTrackSize.y = rcWorkArea.Height() - 0.5;
    CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
LRESULT CSkinFrameWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
    if (message == 0x125)
    {
        OnNcPaint();
    }

    if (message == 0x00AE ||//WM_NCUAHDRAWCAPTION
        message == 0x00AF)//WM_NCUAHDRAWFRAME)
    {
        OnNcPaint();
        return 0;
    }
    return CFrameWnd::WindowProc(message, wParam, lParam);
}
