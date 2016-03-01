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
//獲取model1並儲存，傳入放置model2視窗，Path放路徑(需用\\)，Name放名稱
extern "C" _declspec(dllexport) void VI_GetModel(CWnd* IDC_ModelOneWindow,CString Path,CString Name);
//model比對(Model放model,如有找到則把圖放進指標pic);
extern "C" _declspec(dllexport) bool VI_SearchModel(CWnd* IDC_ShowWindow,void* Model,void* Pic);
//model2比對(請使用上面的，測試)
extern "C" _declspec(dllexport)void VI_FindModel1(double &OffSetX,double &OffSetY,double &Angle,void* Pic,void* Model);
//停止
extern "C" _declspec(dllexport) void VI_FreeModel(void* Model);
//停止
extern "C" _declspec(dllexport) void VI_FreePic(void* Pic);
//停止
extern "C" _declspec(dllexport) void VI_FreeApp();
//切換視窗
extern "C" _declspec(dllexport) void VI_ChangeWindow(CWnd* IDC_ShowWindow);
//對位點拍圖給指標
extern "C" _declspec(dllexport) void VI_Getpicture(void* Model);
//獲取指標圖像(測試)
extern "C" _declspec(dllexport) void VI_Showpicture(void* Pic);
//獲取指標model
extern "C" _declspec(dllexport) void VI_Load(CString Path,CString Name,void* Model);
//獲取兩指標圖像比對回傳偏差值
extern "C" _declspec(dllexport)  void VI_FindModel(void *PicTemp,void *PicTemp1,void* Model,void* Model1,double &OffSetX,double &OffSetY,double &Angle);
class CVI_DllApp : public CWinApp
{
public:
	CVI_DllApp();


// 覆寫
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
