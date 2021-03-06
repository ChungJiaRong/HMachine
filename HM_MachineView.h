
// HM_MachineView.h : CHM_MachineView 類別的介面
//

#pragma once
#include "Main.h"
#include "Compiler.h"
#include "Parameter.h"
#include "IOState.h"

class CHM_MachineView : public CView
{
protected: // 僅從序列化建立
	CHM_MachineView();
	DECLARE_DYNCREATE(CHM_MachineView)

// 屬性
public:
	CHM_MachineDoc* GetDocument() const;
	CTabCtrl* m_TabCtrl;
	CTypedPtrArray<CObArray, CDialog*> m_DlgArray;
	BOOL m_MainDataUP;
//作業
public:
	void  CreatePages();
	afx_msg void OnTabSelChanging(NMHDR* pnmhdr, LRESULT* pResult);
	afx_msg void OnTabSelChange(NMHDR* pnmhdr, LRESULT* pResult);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBtnaccount();
	afx_msg void OnBtninprocess();
	afx_msg void OnBtnobjmenagement();
	afx_msg void OnBtnhistory();

    afx_msg BOOL HandleKeyDownMsg(MSG* pMsg);
// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 程式碼實作
public:
	virtual ~CHM_MachineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#ifndef _DEBUG  // HM_MachineView.cpp 中的偵錯版本
inline CHM_MachineDoc* CHM_MachineView::GetDocument() const
   { return reinterpret_cast<CHM_MachineDoc*>(m_pDocument); }
#endif

