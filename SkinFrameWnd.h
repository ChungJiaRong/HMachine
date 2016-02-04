#pragma once


// CSkinFrameWnd 框架

class CSkinFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CSkinFrameWnd)
protected:
	CSkinFrameWnd();           // 動態建立所使用的保護建構函式
	virtual ~CSkinFrameWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnNcPaint();
    afx_msg BOOL OnNcActivate(BOOL bActive);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
    int m_nFrameWidth, m_nTitleHeight;
    Image* m_pBkImage;
    CRgn m_Rgn;
    vector<Image*> m_WindowBtnImage;
};


