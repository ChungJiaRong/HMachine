#pragma once
#include "BtnST.h"

// CIOState 對話方塊

class CIOState : public CPropertyPage
{
	DECLARE_DYNAMIC(CIOState)

public:
	CIOState();
	virtual ~CIOState();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IOSTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
//屬性
public:
    CRect m_InitRect;
    UINT m_ConCtrlCount;
    CStringArray m_EditInName,m_EditOutName;
    int m_InputState[12];
    int m_OutputState[12];
    int m_OldIBuffer[12];
    int m_OldOBuffer[12];
    CButtonST* CreateB;
    CEdit* CreateD;
    BOOL m_bBtnEnable;
    CFont* MyFont;
    CToolTipCtrl m_tooltip;
//方法
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    void AddControl();
    void ChangeSize(CWnd * pWnd, int cx, int cy);
    void EditTextVertical(CEdit * m_EditCtrl);
    void WriteIOData();
    void ReadIOData();
    void MyUpdateData(BOOL InputState, int* IStateData, BOOL OutputState, int* OStateData, BOOL GetIOEditName = FALSE, BOOL IOEditName = FALSE);
    afx_msg void OnPaint();
    afx_msg void OnBnClickedBtniorefresh();
    afx_msg void OnBnClickedBtnioopenrefresh();
    afx_msg void OnBnClickedBtniocompiler();
    afx_msg void OnBnClickedBtnsetfinish();
    afx_msg void OnStateClick(UINT uId);
    afx_msg void OnOutputClick(UINT uId);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};
