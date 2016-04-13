#pragma once


// CDxfset 對話方塊

class CDxfset : public CDialogEx
{
	DECLARE_DYNAMIC(CDxfset)

public:
	CDxfset(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CDxfset();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DXFSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
    virtual void OnOK();
public:
    virtual BOOL OnInitDialog();
};
