// VI_Dll.h : VI_Dll DLL 的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"		// 主要符號


// CVI_DllApp
// 這個類別的實作請參閱 VI_Dll.cpp
//

//即時影像，傳入放置model1視窗(Ex:GetDlgItem(IDC_STATIC1))
extern "C" _declspec(dllexport) void VI_ModelDefine(CWnd* IDC_ModelOneWindow);
//更改框框
extern "C" _declspec(dllexport) void VI_ChangeRec(CWnd* IDC_ModelOneWindow,int x,int y);
//獲取model1並儲存，傳入放置model2視窗
extern "C" _declspec(dllexport) void VI_GetModel1(CWnd* IDC_ModelOneWindow);
//獲取model2並儲存
extern "C" _declspec(dllexport) void VI_GetModel2(CWnd* IDC_ModelTwoWindow);
//model1比對
extern "C" _declspec(dllexport) void VI_FindModel1(double &OffSetX,double &OffSetY,double &Angle,CWnd* IDC_ShowWindow);
//model2比對
extern "C" _declspec(dllexport) void VI_FindModel2(double &OffSetX2,double &OffSetY2,double &Angle2,CWnd* IDC_ShowWindow);
//停止
extern "C" _declspec(dllexport) void VI_Free();
//切換視窗
extern "C" _declspec(dllexport) void VI_ChangeWindow(CWnd* IDC_ShowWindow);

class CVI_DllApp : public CWinApp
{
public:
	CVI_DllApp();


// 覆寫
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
