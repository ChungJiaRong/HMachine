
// HM_Machine.cpp : 定義應用程式的類別行為。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "HM_Machine.h"
#include "MainFrm.h"

#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "Login.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHM_MachineApp

BEGIN_MESSAGE_MAP(CHM_MachineApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CHM_MachineApp::OnAppAbout)
    // 依據文件命令的標準檔案
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
    
END_MESSAGE_MAP()


// CHM_MachineApp 建構

CHM_MachineApp::CHM_MachineApp()
{
    // 支援重新啟動管理員
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    // 如果應用程式是使用 Common Language Runtime 支援 (/clr) 建置的: 
    //     1) 要使重新啟動管理員支援正常運作需要這個額外設定。
    //     2) 在專案中必須將參考加入至 System.Windows.Forms 才能進行建置。
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

    // TODO: 以唯一的 ID 字串取代下面的應用程式 ID 字串; 建議的
    // 字串格式為 CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("HM_Machine.AppID.NoVersion"));

    // TODO: 在此加入建構程式碼，
    // 將所有重要的初始設定加入 InitInstance 中
    
}

// 僅有的一個 CHM_MachineApp 物件

CHM_MachineApp theApp;


// CHM_MachineApp 初始設定

BOOL CHM_MachineApp::InitInstance()
{
    hMutex = CreateMutex(NULL, false, _T("HM_MachineApp"));//創建互斥
    if (GetLastError() == ERROR_ALREADY_EXISTS)//防止程序重複開啟
    {
        CloseHandle(hMutex);//結束時釋放句柄
        hMutex = NULL;
        return FALSE;
    }
    else
    {
        // 假如應用程式資訊清單指定使用 ComCtl32.dll 6 (含) 以後版本，
        // 來啟動視覺化樣式，在 Windows XP 上，則需要 InitCommonControls()。
        // 否則任何視窗的建立都將失敗。
        INITCOMMONCONTROLSEX InitCtrls;
        InitCtrls.dwSize = sizeof(InitCtrls);
        // 設定要包含所有您想要用於應用程式中的
        // 通用控制項類別。
        InitCtrls.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx(&InitCtrls);

        CWinApp::InitInstance();

        // 初始化 OLE 程式庫
        if (!AfxOleInit())
        {
            AfxMessageBox(IDP_OLE_INIT_FAILED);
            return FALSE;
        }

        AfxEnableControlContainer();

        EnableTaskbarInteraction(FALSE);

        // 需要有 AfxInitRichEdit2() 才能使用 RichEdit 控制項	
        // AfxInitRichEdit2();

        // 標準初始設定
        // 如果您不使用這些功能並且想減少
        // 最後完成的可執行檔大小，您可以
        // 從下列程式碼移除不需要的初始化常式，
        // 變更儲存設定值的登錄機碼
        // TODO: 您應該適度修改此字串
        // (例如，公司名稱或組織名稱)
        SetRegistryKey(_T("本機 AppWizard 所產生的應用程式"));
        LoadStdProfileSettings(4);  // 載入標準 INI 檔選項 (包含 MRU)


                                    // 登錄應用程式的文件範本。文件範本負責在文件、
                                    // 框架視窗與檢視間進行連接
        /*Log.txt開啟*/
        CString m_path = GetModulePath()+_T("Log.txt");
        if ((LogFile.Open(m_path, CFile::modeCreate | CFile::modeNoTruncate
            | CFile::modeWrite | CFile::typeUnicode | CFile::shareDenyNone)) == 0)
        {
            AfxMessageBox(_T("Log開啟失敗"));
        }
        /*History.txt開啟*/
        m_path = GetModulePath()+_T("History.txt");
        if ((HistoryFile.Open(m_path, CFile::modeCreate | CFile::modeNoTruncate
            | CFile::modeWrite | CFile::typeUnicode | CFile::shareDenyNone)) == 0)
        {
            AfxMessageBox(_T("History開啟失敗"));
        }
        else
        {
            HistoryFile.SeekToEnd();
        }
        /*框架*/
        CSkinManager::GetInstance()->SetSkinPath(GetModulePath() + _T("Skins\\Default\\"));//載入skin路徑
        CSingleDocTemplate* pDocTemplate;
        pDocTemplate = new CSingleDocTemplate(
            IDR_MAINFRAME,
            RUNTIME_CLASS(CHM_MachineDoc),
            RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架視窗
            RUNTIME_CLASS(CHM_MachineView));
        if (!pDocTemplate)
            return FALSE;
        AddDocTemplate(pDocTemplate);
        // 剖析標準 Shell 命令、DDE、檔案開啟舊檔的命令列
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);
        // 啟用 DDE 執行開啟
        EnableShellOpen();
        RegisterShellFileTypes(TRUE);
        // 在命令列中指定的分派命令。如果已使用 
        // /RegServer、/Register、/Unregserver 或 /Unregister 啟動應用程式，將傳回 FALSE。
        if (!ProcessShellCommand(cmdInfo))
            return FALSE;
        // 僅初始化一個視窗，所以顯示並更新該視窗
        // 只有在 SDI 應用程式中有後置字元時，才呼叫 DragAcceptFiles
        // 這會發生於 ProcessShellCommand 之後
        // 啟用拖放開啟
        LoginApp();
        //m_pMainWnd->ShowWindow(SW_SHOW);//顯示主視窗
        //m_pMainWnd->UpdateWindow();//更新主視窗
        m_pMainWnd->DragAcceptFiles();
    } 
    return TRUE;
}

int CHM_MachineApp::ExitInstance()
{
    // TODO: 處理其他您已經加入的資源
    CSkinManager::UnLoadSkin();
    CloseHandle(hMutex);//結束時釋放句柄
    hMutex = NULL;
    AfxOleTerm(FALSE);
    return CWinApp::ExitInstance();
}

// CHM_MachineApp 訊息處理常式

void CHM_MachineApp::LoginApp() 
{
    CLogin LoginDlg;
    if (IDOK == LoginDlg.DoModal())
    {
#ifdef MOVE
        if (!MO_Open(1))
        {
            AfxMessageBox(_T("開啟驅動失敗!"));
            LoginApp();
        }
        else {
            MO_SetHardLim(7, 1);
            MO_SetDecOK(1);//開啟減速有效 
            MO_MoveToHome(20000, 1000, 7, 0);//原點復歸
            CWait Waitdialog;
            if (Waitdialog.DoModal())
            {
                CMainFrame *pMain = (CMainFrame*)m_pMainWnd;//獲取已建立的View指針
                CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
                pView->CreatePages();//創建分頁
                m_pMainWnd->ShowWindow(SW_SHOW);//顯示主視窗
                m_pMainWnd->UpdateWindow();//更新主視窗
            }    
        }
#endif //MOVE
#ifndef MOVE
        CMainFrame *pMain = (CMainFrame*)m_pMainWnd;//獲取已建立的View指針
        CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
        pView->CreatePages();//創建分頁
        m_pMainWnd->ShowWindow(SW_SHOW);//顯示主視窗
        m_pMainWnd->UpdateWindow();//更新主視窗     
#endif 
        AfxGetMainWnd()->SetLayeredWindowAttributes(0, (255 * 100) / 100, LWA_ALPHA);//主視窗恢復透明化
        WriteHistory(HistoryFile, UserID, _T("帳戶資訊"),_T("登入"));
    }
    else {
        LogFile.Close();
        HistoryFile.Close();
        AfxGetMainWnd()->PostMessage(WM_CLOSE);//正常退出  
        //PostQuitMessage(0);
        //exit(0);
    }
}

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
    DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 執行對話方塊的應用程式命令
void CHM_MachineApp::OnAppAbout()
{
    CAboutDlg dlg;
    dlg.DoModal();
}



// CHM_MachineApp 訊息處理常式

