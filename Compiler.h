#pragma once
#include "atltypes.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MoveButton.h"
#include "GlueEdit.h"

//CCompiler��ܤ��

class CCompiler : public CPropertyPage
{
	DECLARE_DYNAMIC(CCompiler)

public:
	CCompiler();
	virtual ~CCompiler();

//��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPILER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
//�ݩ�
public:
	CRect  m_InitRect;
	CListCtrl m_ListCtrlPos, m_ListCtrlWork;
	CStringArray m_WorkData,m_PosData,m_OtherData;
    CMoveButton m_Yup, m_Ydown, m_Xup, m_Xdown, m_Zup, m_Zdown;
	int m_ListWKCount,m_ListPSCount;
    CToolTipCtrl m_tooltip;
//��k
public:
    afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedFileNew();
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnBnClickedFileSave();
	afx_msg void OnBnClickedFileSaveAs();

	afx_msg void OnBnClickedBtncomworkw();
	afx_msg void OnBnClickedBtncomstandchk1();
	afx_msg void OnBnClickedBtncomstandchk2();
	afx_msg void OnBnClickedBtncomoriginw();
    afx_msg void OnBnClickedBtncommovexyz();
    afx_msg void OnBnClickedBtncomwait();
    afx_msg void OnBnClickedBtncomgui();
    afx_msg void OnBnClickedBtncompickup();
	afx_msg void OnBnClickedBtncomworkfinish();
    afx_msg void OnBnClickedBtncomdispensing();

	afx_msg void OnEnChangeEditcomname();
	afx_msg void OnListmodify();
	afx_msg void OnListinsert();
	afx_msg void OnListdelete();
	afx_msg void OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEditChange(UINT uId);
    afx_msg void OnZActionChange(UINT uId);
    afx_msg void OnMoveTypeChange(UINT uId);

    int DataToWorkData();
    LONG CycleRCalculation(CString Data1, CString Data2);
    LONG CStringToXYZ(CString Data, int Choose);

    void ChangeSize(CWnd* pWnd, int cx, int cy);
    void InitVariable();
    void EditTextVertical(CEdit *m_EditCtrl);
    void WorkListRefresh(BOOL ScrollBarRefresh);   
    void MoveXYZ(int MoveX, int MoveY, int MoveZ);
    
};
