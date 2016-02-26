#pragma once
#include "atltypes.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MoveButton.h"
#include "GlueEdit.h"

//CCompiler對話方塊

class CCompiler : public CPropertyPage
{
	DECLARE_DYNAMIC(CCompiler)

public:
	CCompiler();
	virtual ~CCompiler();

//對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPILER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
//屬性
public:
	CRect  m_InitRect;
	CListCtrl m_ListCtrlPos, m_ListCtrlWork, m_ListCtrlZ;;
	CStringArray m_WorkData,m_PosData,m_ZData;
    CMoveButton m_Yup, m_Ydown, m_Xup, m_Xdown, m_Zup, m_Zdown;
	int m_ListWKCount,m_ListPSCount;
    UINT m_GlueTime;
//方法
public:
    afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedFileNew();
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnBnClickedFileSave();
	afx_msg void OnBnClickedFileSaveAs();

	afx_msg void OnBnClickedBtncomworkw();
	afx_msg void OnBnClickedBtncomstandchk1();
	afx_msg void OnBnClickedBtncomstandchk2();
	afx_msg void OnBnClickedBtncomoriginw();
    afx_msg void OnBnClickedBtncommovexyz();
    afx_msg void OnBnClickedBtncomwait();
    afx_msg void OnBnClickedBtncomzdowncheck();
    afx_msg void OnBnClickedBtncomzupcheck();
	afx_msg void OnBnClickedBtncomworkfinish();
    afx_msg void OnBnClickedBtncomdispensing();

	afx_msg void OnEnChangeEditcomname();
	afx_msg void OnListmodify();
	afx_msg void OnListinsert();
	afx_msg void OnListdelete();
	afx_msg void OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEditChange(UINT uId);

    void ChangeSize(CWnd* pWnd, int cx, int cy);
    void InitVariable();
    void EditTextVertical(CEdit *m_EditCtrl);
    void WorkListRefresh(BOOL ScrollBarRefresh);   
    void MoveXYZ(int MoveX, int MoveY, int MoveZ);
    afx_msg void OnBnClickedRadcomapply();
    afx_msg void OnBnClickedRadcomspot();
};
