// ConvPosFile.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ConvPosFile.h"
#include "ConvPosFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CConvPosFileApp

BEGIN_MESSAGE_MAP(CConvPosFileApp, CWinApp)
	//{{AFX_MSG_MAP(CConvPosFileApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvPosFileApp construction

CConvPosFileApp::CConvPosFileApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CConvPosFileApp object

CConvPosFileApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CConvPosFileApp initialization

BOOL CConvPosFileApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//命令行参数处理
	CString ss,str;
	ss.Format(TEXT("%s"),AfxGetApp()->m_lpCmdLine);
	if (ss.GetLength())
	{
		ss.TrimLeft('\'');
		ss.TrimLeft('\"');
		ss.TrimRight('\'');
		ss.TrimRight('\"');
		if (ss.Right(4).CompareNoCase(TEXT(".pos")))
		{
// 			DWORD dwwn;
// 			COORD coord = {1,2};
// 			WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE),TEXT("参数格式错误，请输入pos文件名称！"),10,coord, & dwwn);
			str.Format(TEXT("%s\n参数格式错误，请输入pos文件名称！"),ss);
			AfxMessageBox(str);
			return FALSE;
		}
		if (ss.GetAt(1)!=TEXT(':'))
		{
			GetCurrentDirectory(246,str.GetBuffer(246));
			str.ReleaseBuffer();
// 			AfxMessageBox(str);
			if (ss.GetAt(0)!=TEXT('\\'))
			{
				str += TEXT("\\");
			}
			str += ss;
		}
		else
		{
			str = ss;
		}
		ConvPos2Txt(str);
		ss.Format(str.Left(str.Find(TEXT("."),0)));
		ss+=TEXT(".txt");
		ConvTxt2Excel(ss);
		return FALSE;
	} 

	CConvPosFileDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
