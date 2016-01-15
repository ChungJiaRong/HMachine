#pragma once
#include "afxcmn.h"
#include "afxwin.h"
//#define ALL_STAR
#ifdef ALL_STAR 
    #include "MFCDLLtest.h"
#endif
#ifdef ALL_STAR1 
#include<mil.h>
#endif


#define WM_WORKLIST WM_USER + 1
struct WorkPoint {
    HWND hwnd;
    int WorkCount;
    CStringArray* Work;
};
static CWinThread* g_pThreadRun; 
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

	DECLARE_MESSAGE_MAP()
//屬性
public:
	CRect  m_InitRect;
    CStringArray m_MainWorkData;
    int m_MainListWKCount;
	CString m_MainPosData1,m_MainPosData2;
	CListCtrl m_ListCtrlWork;
#ifdef ALL_STAR1
    MIL_ID	MilApplication,
        MilSystem,
        MilDisplay,
        MilDigitizer,
        MilImage,
        MilOverlayImage;  
#endif
//方法
public:
    
	void ChangeSize(CWnd* pWnd, int cx, int cy);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnmaingoorigin();
	afx_msg void OnBnClickedBtnmaintimeout();
	afx_msg void OnBnClickedBtnmainstop();
	afx_msg void OnBnClickedBtnmainstart();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
    static CString CStringToXY(CString Data, int Choose);
    static UINT Run(LPVOID pParam);
    afx_msg LRESULT OnListRefresh(WPARAM wParam, LPARAM lParam);   
};
