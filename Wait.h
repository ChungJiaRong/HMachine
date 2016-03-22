#pragma once


// CWait 對話方塊

class CWait : public CDialogEx
{
	DECLARE_DYNAMIC(CWait)
public:
	CWait(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CWait();
// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAITING };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
};
