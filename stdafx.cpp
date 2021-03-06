// stdafx.cpp : 僅包含標準 Include 檔的原始程式檔
// HM_Machine.pch 會成為先行編譯標頭檔
// stdafx.obj 會包含先行編譯類型資訊

#include "stdafx.h"
/*獲取路徑*/
CString GetModulePath()
{
    TCHAR s_buf[MAX_PATH];
    s_buf[0] = 0x0;
    DWORD n_result = ::GetModuleFileName(NULL, s_buf, sizeof(TCHAR) * MAX_PATH);
    TCHAR	s_drive[MAX_PATH];
    s_drive[0] = 0x0;
    TCHAR s_dir[MAX_PATH];
    s_dir[0] = 0x0;
    /*errno_t n_err_no =*/
    _tsplitpath(s_buf, s_drive, s_dir, NULL, NULL);
    //assert(n_err_no == 0);
    _tcscpy_s(s_buf, s_drive);
    _tcscat_s(s_buf, s_dir);
    return CString(s_buf);
}
/*寫入Log檔*/
void WriteLogFile(CFile &File,CString error_number,CString note)
{
    //**事先要先宣告CFile傳入 ＆ 宣告路徑給他OPEN**

    //獲取系統時間
    CString write_time;
    CTime tmd;
    tmd = CTime::GetCurrentTime();
    write_time = tmd.Format("%Y/%m/%d\n%X");

    //空格
    CString write_blank;
    write_blank = _T("\r\n");

    //工作資訊
    CString send;
    send += write_time;
    send += _T("\t");
    send += error_number;
    send += _T("\t");
    send += note;
    send += _T("\t");
    send += write_blank;

    File.SeekToEnd();
    File.Write(send, send.GetLength()*sizeof(TCHAR));
}
/*寫入歷史訊息*/
void WriteHistory(CFile &File, CString write_account, CString write_action, CString write_alarm)
{

    //獲取系統時間
    CString write_date;
    CString write_time;
    CTime tmd;
    tmd = CTime::GetCurrentTime();
    write_date = tmd.Format("%Y/%m/%d");
    write_time = tmd.Format("%X");

    CArchive ar(&File, CArchive::store);

    ar << write_date;
    ar << write_time;
    ar << write_account;
    ar << write_action;
    ar << write_alarm;

    ar.Close();
}

