#pragma once


// CAccount 對話方塊

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CLogin();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
//屬性
public:
    CStringArray m_UserData;
//方法
public:
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
