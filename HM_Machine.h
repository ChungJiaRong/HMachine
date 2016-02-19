
// HM_Machine.h : HM_Machine 應用程式的主標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號

// CHM_MachineApp:
// 請參閱實作此類別的 HM_Machine.cpp
//

class CHM_MachineApp : public CWinApp
{
public:
	CHM_MachineApp();
// 覆寫
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
//屬性
    CString UserID, UserPwd,Post;
    HANDLE hMutex;
    CFile LogFile,HistoryFile;
//方法
public:
	afx_msg void OnAppAbout();
    void LoginApp();
	DECLARE_MESSAGE_MAP()
	
};

extern CHM_MachineApp theApp;
