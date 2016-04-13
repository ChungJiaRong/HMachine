#pragma once


// CPrint ��ܤ��

class CPrint : public CDialogEx
{
	DECLARE_DYNAMIC(CPrint)

public:
	CPrint(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CPrint();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
    std::vector<std::vector<CString> > Draw;
    CRect m_InitRect;
public:
    void ChangeSize(CWnd * pWnd, int cx, int cy);
    void MO_Draw(std::vector<std::vector<CString>>& csVecWorkPoint2Dim, CDC * pDC, float m_fScale);
    void MO_Change(std::vector<std::vector<CString>>& csVecWorkPoint2Dim);
    CString CStringToXY(CString Data, int Choose);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
};
