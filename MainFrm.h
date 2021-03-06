
// MainFrm.h : CMainFrame 類別的介面
//

#pragma once
#include "SkinFrameWnd.h"
class CMainFrame : public CSkinFrameWnd
{
	
protected: // 僅從序列化建立
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
// 屬性
public:
	CToolBar		  m_ToolBar;
	CImageList		  m_TBImageList, m_SBImageList;
	CStatusBar		  m_StatusBar;
	CProgressCtrl     m_ProgressCtrl;
	CTime			  m_SysTime;

// 作業
public:
	static void DelAllMenu(HMENU hMenu);
	void CreateToolBar();
	void CreateStatusBar();
	BOOL TBToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
// 覆寫
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
// 程式碼實作
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()   
};


