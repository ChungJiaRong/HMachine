#include "stdafx.h"
#include "HM_Database.h"
//添加檔案版本號
IMPLEMENT_SERIAL(CHM_Database, CObject, 1)

CHM_Database::CHM_Database()
{
}
CHM_Database::CHM_Database(CString m_ptOrigin, CString m_ptEnd, CString m_Action , CString m_MoveType ,CString m_ptGlueheight) {
    this->m_ptOrigin = m_ptOrigin;
    this->m_ptEnd = m_ptEnd;
    this->m_Action = m_Action;
    this->m_MoveType = m_MoveType;
    this->m_ptGlueheight = m_ptGlueheight;
}

CHM_Database::CHM_Database(CString m_Stand) {
    this->m_Stand = m_Stand;
}
CHM_Database::~CHM_Database()
{
}
void CHM_Database::Serialize(CArchive& ar) {
    if (ar.IsStoring()) {
        ar << m_ptOrigin << m_ptEnd<< m_Action << m_MoveType << m_Stand;
    }
    else {
        ar >> m_ptOrigin >> m_ptEnd>> m_Action >> m_MoveType >> m_Stand;
    }
}
void CHM_Database::WKArrayCopy(CStringArray* pCStrA, UINT Count)
{
    pCStrA->InsertAt(Count * 4, m_ptEnd);
    pCStrA->InsertAt(Count * 4 + 1, m_Action);
    pCStrA->InsertAt(Count * 4 + 2, m_MoveType);
    pCStrA->InsertAt(Count * 4 + 3, m_ptGlueheight);
}
void CHM_Database::PSArrayCopy(CStringArray* pCStrA, UINT Count)
{
    pCStrA->SetAt(Count, m_Stand);
}



