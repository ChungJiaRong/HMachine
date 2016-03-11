#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "MoveButton.h"
#include "ComRound.h"
#include "GlueEdit.h"

//CCompiler對話方塊

class CCompiler : public CPropertyPage
{
	DECLARE_DYNAMIC(CCompiler)

public:
	CCompiler();
	virtual ~CCompiler();

//對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPILER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
//屬性
public:
	CRect  m_InitRect;
	CListCtrl m_ListCtrlPos, m_ListCtrlWork;
	CStringArray m_WorkData,m_PosData,m_OtherData;
	CMoveButton m_Yup, m_Ydown, m_Xup, m_Xdown, m_Zup, m_Zdown;
	int m_ListWKCount,m_ListPSCount,m_ListWKInster;
    BOOL m_InverseChoose, m_SizeChoose ,m_InsterLock ,m_ModifyLock,m_ModifyRound;
    int m_RADIUS ,m_OldListRow,m_OldListColumn;
	CToolTipCtrl m_tooltip;
    CComboBox m_Combobox;
    CStatic m_Static;
    std::vector<std::vector<CString>> m_DxfWorkData;
//方法
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
    void CreateCombo(NM_LISTVIEW * pEditCtrl, CComboBox * m_Combobox1);
	afx_msg void OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditChange(UINT uId);
	afx_msg void OnZActionChange(UINT uId);
	afx_msg void OnMoveTypeChange(UINT uId);

	int DataToWorkData();
	LONG RoundRCalculation(CString Data1, CString Data2);
	LONG CStringToXYZ(CString Data, int Choose);
    CPoint RoundCCalculation(int RADIUS, CPoint Origin, CPoint End, BOOL SizeChoose, BOOL InverseChoose);
	CString ArcDataCheck(CString strOrigin, CString strEnd);
    CString RoundDataCheck(CString RoundC);

	void ChangeSize(CWnd* pWnd, int cx, int cy);
	void InitVariable();
	void EditTextVertical(CEdit *m_EditCtrl);
	void WorkListRefresh(BOOL ScrollBarRefresh);   
	void MoveXYZ(int MoveX, int MoveY, int MoveZ);

    afx_msg void OnSelendokCmbcombrief();
    void CreateStatic(CStatic * m_Static);
    afx_msg void OnNMClickListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnloaddxf();
};
