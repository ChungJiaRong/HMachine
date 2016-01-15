#pragma once
#include "atltypes.h"
#include "afxcmn.h"
#include "afxwin.h"


//CCompiler¹ï¸Ü¤è¶ô

class CCompiler : public CPropertyPage
{
	DECLARE_DYNAMIC(CCompiler)

public:
	CCompiler();
	virtual ~CCompiler();

//¹ï¸Ü¤è¶ô¸ê®Æ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPILER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Žx?

	DECLARE_MESSAGE_MAP()
//ÄÝ©Ê
public:
	CRect  m_InitRect;
	CListCtrl m_ListCtrlPos, m_ListCtrlWork;
	CStringArray m_WorkData,m_PosData;
	int m_ListWKCount,m_ListPSCount;
//¤èªk
public:
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	afx_msg void OnBnClickedFileNew();
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnBnClickedFileSave();
	afx_msg void OnBnClickedFileSaveAs();
	
	afx_msg void OnBnClickedBtncomworkw();
	afx_msg void OnBnClickedBtncomstandchk1();
	afx_msg void OnBnClickedBtncomstandchk2();
	afx_msg void OnBnClickedBtncomoriginw();
	afx_msg void OnBnClickedBtncomyup();
	afx_msg void OnBnClickedBtncomydown();
	afx_msg void OnBnClickedBtncomxdown();
	afx_msg void OnBnClickedBtncomxup();

	afx_msg void OnBnClickedBtncomworkfinish();
	afx_msg void OnEnChangeEditcomname();
	afx_msg void OnRclickListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnListmodify();
	afx_msg void OnListinsert();
	afx_msg void OnListdelete();
	afx_msg void OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEditChange(UINT uId);

    void ChangeSize(CWnd* pWnd, int cx, int cy);
    void InitVariable();
    void EditTextVertical(CEdit *m_EditCtrl);
    void WorkListRefresh(BOOL ScrollBarRefresh);
};
