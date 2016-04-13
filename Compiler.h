#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "MoveButton.h"
#include "ComRound.h"
#include "GlueEdit.h"
#include "Dxfset.h"
#include "MoveEdit.h"
#include "Print.h"
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
	CMoveButton m_Yup, m_Ydown, m_Xup, m_Xdown, m_Zup, m_Zdown;
	CMoveEdit m_MoveX, m_MoveY, m_MoveZ;

	int m_ListWKCount,m_ListPSCount,m_ListWKInster;
	BOOL m_InsterLock ,m_ModifyLock;
	int m_OldListRow,m_OldListColumn;
	CToolTipCtrl m_tooltip;
	CComboBox m_Combobox;
	CStatic m_Static;
	std::vector<CString> m_WorkData;


    /*校正用*/
    void *ConversionModel1;
    LONG  ConversionModel1X, ConversionModel1Y;
    double ConversionX, ConversionY;

	/*兩點加半徑*/
	int m_RADIUS;
	BOOL m_InverseChoose, m_SizeChoose;//大小弧+正反轉
	/*Dxf使用*/
	int m_DxfRate;
	CString m_DxfZdown;
	
//方法
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnEnChangeEditcomname();
	afx_msg void OnBnClickedFileNew();
	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnBnClickedFileSave();
	afx_msg void OnBnClickedFileSaveAs();

	afx_msg void OnBnClickedBtncomwait();
	afx_msg void OnBnClickedBtncomoriginw();
	afx_msg void OnBnClickedBtncombetween();
	afx_msg void OnBnClickedBtncomend();
	afx_msg void OnBnClickedBtncomstandchk1();
	afx_msg void OnBnClickedBtncomstandchk2();
	afx_msg void OnBnClickedBtncommovexyz();
	afx_msg void OnBnClickedBtncomgui();
	afx_msg void OnBnClickedBtncompickup();
	afx_msg void OnBnClickedBtncomccdcheck();
	afx_msg void OnBnClickedBtncomccdmodify();
	afx_msg void OnBnClickedBtncomworkfinish();
	afx_msg void OnBnClickedBtncomdispensing();

	afx_msg void OnBnClickedBtncomprant();

	afx_msg void OnNMClickListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelendokCmbcombrief();
	afx_msg void OnListmodify();
	afx_msg void OnListinsert();
	afx_msg void OnListdelete();
  
	afx_msg void OnEditChange(UINT uId);
	afx_msg void OnZActionChange(UINT uId);
	afx_msg void OnMoveTypeChange(UINT uId);
	
	int DataToWorkData();
	LONG CStringToXYZ(CString Data, int Choose);
	CString CStringToXY(CString Data, int Choose);

	LONG RoundRCalculation(CString Data1, CString Data2);
	CPoint RoundCCalculation(int RADIUS, CPoint Origin, CPoint End, BOOL SizeChoose, BOOL InverseChoose);
	CString ArcDataCheck(CString strOrigin, CString strEnd);
	CString RoundDataCheck(CString RoundC);

	CString TRoundCCalculation(CString Origin, CString End, CString Between);

	void MoreEnableWindows(int BeginID, int EndID , BOOL Enable);
	void ChangeSize(CWnd* pWnd, int cx, int cy);
	void InitVariable();
	void EditTextVertical(CEdit *m_EditCtrl);
	void WorkListRefresh(BOOL ScrollBarRefresh);   
	void MoveXYZ(int MoveX, int MoveY, int MoveZ);
	void CreateStatic(CStatic * m_Static);
	void CreateCombo(NM_LISTVIEW * pEditCtrl, CComboBox * m_Combobox1);
    afx_msg void OnBnClickedBtncommoverxyz();
};
