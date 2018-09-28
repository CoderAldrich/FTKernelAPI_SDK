#if !defined(AFX_DLGSELFILES_H__A54E7EE3_6BC5_4529_80D7_B87F3EFAD20C__INCLUDED_)
#define AFX_DLGSELFILES_H__A54E7EE3_6BC5_4529_80D7_B87F3EFAD20C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelFiles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelFiles dialog

class CDlgSelFiles : public CDialog
{
// Construction
public:
	CDlgSelFiles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelFiles)
	enum { IDD = IDD_DLG_TORRENT_FILES };
	CListCtrl	m_wndFiles;
	//}}AFX_DATA

	void SetInfo( LPCTSTR lpszTorrentFileName, LPCTSTR lpszPassword = NULL )
	{
		ASSERT( NULL != lpszTorrentFileName );
		m_strTorrentName = lpszTorrentFileName;

		if ( NULL != lpszPassword )
		{
			m_strPassword = lpszPassword;
		}
	}

	CByteArray m_arryFilePriority;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelFiles)
	afx_msg void OnSelAll();
	afx_msg void OnInvertSel();
	afx_msg void OnDeSelAll();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void InitializeHeaderControl();
    void InitializeListControl();

protected:

    CString m_strTorrentName;
	CString m_strPassword;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELFILES_H__A54E7EE3_6BC5_4529_80D7_B87F3EFAD20C__INCLUDED_)
