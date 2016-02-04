#pragma once
#include "afxcmn.h"
#include "afxwin.h"
struct Speed {
    LONG Init;
    LONG Add;
    LONG End;
};
struct Limit {
    BOOL Hard;
    BOOL Soft;
    CPoint Pos;
    CPoint Nedg;
    LONG PosZ, NedgZ;
};
// CParameter 對話方塊

class CParameter : public CPropertyPage
{
	DECLARE_DYNAMIC(CParameter)

public:
	CParameter();   // 標準建構函式
	virtual ~CParameter();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
//屬性
public:
    CRect m_InitRect;
    CImageList m_OnOffImageList;
    LONG OSpeed, OLSpeed, RSpeed ,R2Speed,A2Speed;
    int ARSpeedType;
    Limit Limit;
    Speed HSpeed, MSpeed, LSpeed , WSpeed;
    CListCtrl m_ListCtrlParame;
    int m_ListCount;
//方法
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBnClickedBtnparsetfinish();
    afx_msg void OnPaint();
    afx_msg void OnBnClickedBtnpareditpar();
    afx_msg void OnBnClickedBtnparinit();
    afx_msg void OnSelendokCmbpartype();
    afx_msg void OnStnClickedChkparhlimit();
    afx_msg void OnStnClickedChkparslimit();
    void ChangeSize(CWnd * pWnd, int cx, int cy);
    void InitParameter();
    void WriteParamData();
    void ReadParamData();
    void RefreshData();
    void SetParameter();
    void SetListItemText(CListCtrl &m_ListCtrl, UINT Item, UINT Count, ...);
    void EditTextVertical(CEdit * m_EditCtrl);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
