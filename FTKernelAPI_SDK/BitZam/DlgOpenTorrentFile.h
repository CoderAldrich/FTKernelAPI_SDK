#if !defined(AFX_DLGOPENTORRENTFILE_H__2A1BA057_C0E1_41E4_94EB_93AE4CD1DA61__INCLUDED_)
#define AFX_DLGOPENTORRENTFILE_H__2A1BA057_C0E1_41E4_94EB_93AE4CD1DA61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOpenTorrentFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOpenTorrentFile dialog

class CDlgOpenTorrentFile : public CDialog
{
// Construction
public:
	CDlgOpenTorrentFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOpenTorrentFile)
	enum { IDD = IDD_DLG_OPEN_TORRENT };
	CString	m_strPassword;
	CString	m_strDestPath;
	//}}AFX_DATA

	void SetEncrypt( BOOL bEncrypt )
	{
		m_bEncrypt = bEncrypt;
	};


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOpenTorrentFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOpenTorrentFile)
	afx_msg void OnSelDestPath();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	BOOL m_bEncrypt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPENTORRENTFILE_H__2A1BA057_C0E1_41E4_94EB_93AE4CD1DA61__INCLUDED_)
