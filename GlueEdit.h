#pragma once


// CGlueEdit ��ܤ��

class CGlueEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CGlueEdit)

public:
	CGlueEdit(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CGlueEdit();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLUEEDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
};
