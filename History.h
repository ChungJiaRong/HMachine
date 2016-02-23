#pragma once
#include "afxdtctl.h"


// CHistory 對話方塊

class CHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CHistory)

public:
	CHistory(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CHistory();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CListCtrl m_HistoryList;
    CDateTimeCtrl m_DateTimeStart;
    CDateTimeCtrl m_DateTimeEnd;
    void ReadAccountData();
    void SearchReadHistoty(CFile *read_file, CString myfilepath, CListCtrl *setlist, CTime Begin, CTime End, CString read_account, CString read_action);
    void ReadAllHistory(CListCtrl &setlist, CFile &read_file, CString myfilepath);
    afx_msg void OnSelchangeComboBox();
    afx_msg void OnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnhiscsearchall();
};
