#if !defined(AFX_DLGMAKETORRENT_H__40C4FD68_96C7_4FD9_8455_90B27BB34FB1__INCLUDED_)
#define AFX_DLGMAKETORRENT_H__40C4FD68_96C7_4FD9_8455_90B27BB34FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMakeTorrent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMakeTorrent dialog

class CDlgMakeTorrent : public CDialog
{
// Construction
public:
	CDlgMakeTorrent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMakeTorrent)
	enum { IDD = IDD_MAKE_TORRENT };
	CComboBox	m_wndCodePage;
	int		m_nFileOrDir;
	CString	m_strMainTracker;
	CString	m_strOtherTracker;
	CString	m_strNotes;
	CString	m_strTorrentName;
	BOOL	m_bEncrypt;
	CString	m_strPassword;
	CString	m_strSrcPathFile;
	int		m_nPieceSize;
	//}}AFX_DATA

	static CString m_strMainAnnounce;
	static CString m_strOtherAnnounces;
	static CString m_strComments;
	static CString m_strDestTorrentName;
	static CString m_strEncryptPwd;
	static CString m_strSourceFilePath;
	static int m_nSelPieceSize;
	static BOOL m_bIsFile;
    static UINT m_nCodePage;
	static BOOL m_bMakeSHA1;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMakeTorrent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMakeTorrent)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelFileOrDir();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelTorrentFileName();
	afx_msg void OnStartMakeTorrent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

    static BOOL CALLBACK EnumCodePageProc( LPTSTR lpCodePageString );
    int SelectCodePage( CComboBox &wndComboBox, UINT nCodePage );

protected:

    static CStringArray m_arryCodePages;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAKETORRENT_H__40C4FD68_96C7_4FD9_8455_90B27BB34FB1__INCLUDED_)
