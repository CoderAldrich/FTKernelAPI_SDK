#if !defined(AFX_DLGADDEXTANNOUNCE_H__C97F76C4_636F_4966_9175_9D1F1F962F21__INCLUDED_)
#define AFX_DLGADDEXTANNOUNCE_H__C97F76C4_636F_4966_9175_9D1F1F962F21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddExtAnnounce.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddExtAnnounce dialog

class CDlgAddExtAnnounce : public CDialog
{
// Construction
public:
	CDlgAddExtAnnounce(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddExtAnnounce)
	enum { IDD = IDD_DLG_ADD_ANNOUNCE };
	CString	m_strExtAnnounce;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddExtAnnounce)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddExtAnnounce)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDEXTANNOUNCE_H__C97F76C4_636F_4966_9175_9D1F1F962F21__INCLUDED_)
