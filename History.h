#pragma once


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
    CStringArray m_AccoutName;
    void ReadAccountData();
    void ReadHistory(CListCtrl &setlist, CFile &read_file, CString myfilepath);
};
