#pragma once


// CComRound 對話方塊

class CComRound : public CDialogEx
{
	DECLARE_DYNAMIC(CComRound)

public:
	CComRound(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CComRound();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMROUND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
    int ComboCheck;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
