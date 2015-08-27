// ConvPosFileDlg.h : header file
//

#if !defined(AFX_CONVPOSFILEDLG_H__6665AF53_112B_4D25_BFFC_98C01A801F7A__INCLUDED_)
#define AFX_CONVPOSFILEDLG_H__6665AF53_112B_4D25_BFFC_98C01A801F7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

BOOL ConvPos2Txt(CString sPath);
BOOL ConvTxt2Excel(CString sPath);

/////////////////////////////////////////////////////////////////////////////
// CConvPosFileDlg dialog

class CConvPosFileDlg : public CDialog
{
// Construction
public:
	CConvPosFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CConvPosFileDlg)
	enum { IDD = IDD_CONVPOSFILE_DIALOG };
	CString	m_strPosFilePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvPosFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

//data member
public:

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CConvPosFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConvert();
	virtual void OnCancel();
	afx_msg void OnBtnSelfile();
	afx_msg void OnBtnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVPOSFILEDLG_H__6665AF53_112B_4D25_BFFC_98C01A801F7A__INCLUDED_)
