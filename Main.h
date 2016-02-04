#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#define WM_WORKLIST WM_USER + 1
struct WorkPoint {
    HWND hwnd;
    int WorkCount;
    CStringArray* Work;
    CString StandPos1, StandPos2;
    CString m_ZDataDown, m_ZDataUp;
};
static CWinThread* g_pThreadRun;
static BOOL g_ThreadClose = FALSE;
//CMain對話方塊
class CMain : public CPropertyPage
{
	DECLARE_DYNAMIC(CMain)

public:
	CMain();
	virtual ~CMain();

//對話框資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
//屬性
public:
	CRect  m_InitRect;
    CStringArray m_MainWorkData;
    int m_MainListWKCount;
	CString m_MainPosData1,m_MainPosData2,m_MainZDataDown,m_MainZDataUp;
	CListCtrl m_ListCtrlWork;
//方法
public:
	void ChangeSize(CWnd* pWnd, int cx, int cy);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnmaingoorigin();
	afx_msg void OnBnClickedBtnmaintimeout();
	afx_msg void OnBnClickedBtnmainstop();
	afx_msg void OnBnClickedBtnmainstart();
	afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg LRESULT OnListRefresh(WPARAM wParam, LPARAM lParam);   
    static CString CStringToXY(CString Data, int Choose);
    static UINT Run(LPVOID pParam);
};
