
// HM_MachineDoc.h : CHM_MachineDoc 類別的介面
//


#pragma once


class CHM_MachineDoc : public CDocument
{
protected: // 僅從序列化建立
	CHM_MachineDoc();
	DECLARE_DYNCREATE(CHM_MachineDoc)

// 屬性
public:
    CObArray m_WorkArray, m_StandArray, m_OtherArray;
// 作業
public:
    virtual void DeleteContents();
// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 程式碼實作
public:
	virtual ~CHM_MachineDoc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 為搜尋處理常式設定搜尋內容的 Helper 函式
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
