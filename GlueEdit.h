#pragma once


// CGlueEdit 對話方塊

class CGlueEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CGlueEdit)

public:
	CGlueEdit(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CGlueEdit();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLUEEDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
};
