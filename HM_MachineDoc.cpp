
// HM_MachineDoc.cpp : CHM_MachineDoc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "HM_Machine.h"
#endif

#include "HM_MachineDoc.h"
#include "HM_MachineView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHM_MachineDoc

IMPLEMENT_DYNCREATE(CHM_MachineDoc, CDocument)

BEGIN_MESSAGE_MAP(CHM_MachineDoc, CDocument)
END_MESSAGE_MAP()


// CHM_MachineDoc 建構/解構

CHM_MachineDoc::CHM_MachineDoc()
{
	// TODO: 在此加入一次建構程式碼
    
}
CHM_MachineDoc::~CHM_MachineDoc()
{
}
BOOL CHM_MachineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此加入重新初始化程式碼
	// (SDI 文件會重用此文件)
	//SetTitle(_T("thax"));
	
	return TRUE;
}

// CHM_MachineDoc 序列化

void CHM_MachineDoc::Serialize(CArchive& ar)
{
	/*POSITION pos = GetFirstViewPosition();
	CHM_MachineView *pView = (CHM_MachineView*)GetNextView(pos);*/
	if (ar.IsStoring())
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
	}
	/*pView->m_objArray.Serialize(ar);
    pView->m_standArray.Serialize(ar);*/
    m_StandArray.Serialize(ar);
    m_WorkArray.Serialize(ar);
    m_OtherArray.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CHM_MachineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜尋處理常式的支援
void CHM_MachineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開

	// 範例:     strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHM_MachineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS
// CHM_MachineDoc 診斷
#ifdef _DEBUG
void CHM_MachineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHM_MachineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CHM_MachineDoc 命令

void CHM_MachineDoc::DeleteContents()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	/*POSITION pos = GetFirstViewPosition();
	CHM_MachineView *pView = (CHM_MachineView*)GetNextView(pos);*/
	int nCount=0;
	nCount = /*pView->GetDocument()->*/m_WorkArray.GetSize();
	for (int i = 0; i < nCount; i++) {//加上-1避免記憶體超出**************還需研究 nCount 是否加上-1
		delete m_WorkArray.GetAt(i);//釋放索引為i的內存
	}
    m_WorkArray.RemoveAll();
    nCount = m_StandArray.GetSize();
    for (int i = 0; i < nCount; i++) {//加上-1避免記憶體超出**************
        delete m_StandArray.GetAt(i);
    }
    m_StandArray.RemoveAll();
    nCount = m_OtherArray.GetSize();
    for (int i = 0; i < nCount; i++) {//加上-1避免記憶體超出**************
        delete m_OtherArray.GetAt(i);
    }
    m_OtherArray.RemoveAll();
	CDocument::DeleteContents();
}
